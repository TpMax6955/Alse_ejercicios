#include "Principal.h"
#include <QString>
#include <QDateTime>
#include <QFileDialog>

Principal::Principal(Usuario user, QWidget *parent) : QWidget(parent), currentUser(user) {
    setupUI();
    connect(addMeasurementButton, &QPushButton::clicked, this, &Principal::onAddMeasurementClicked);
}

Principal::~Principal() {

}

void Principal::setupUI() {
    this->setWindowTitle("HealthSync - Panel Principal");
    this->resize(400, 300);

    QString imcTexto = QString::number(currentUser.calcularIMC(), 'f', 2);
    QString tmbTexto = QString::number(currentUser.calcularTMB(), 'f', 2);

    welcomeLabel = new QLabel("<b>¡Bienvenido, " + currentUser.getNombreUsuario() + "!</b>", this);
    imcLabel = new QLabel("Tu IMC actual: <b>" + imcTexto + "</b>", this);
    tmbLabel = new QLabel("Tu TMB actual: <b>" + tmbTexto + " kcal</b>", this);
   

    chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    cargarGrafica();

    addMeasurementButton = new QPushButton("Registrar Nueva Medición", this);
    logoutButton = new QPushButton("Cerrar Sesión", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    exportButton = new QPushButton("Exportar Historial (CSV)", this);
    connect(exportButton, &QPushButton::clicked, this, &Principal::onExportClicked);
    
    mainLayout->addWidget(welcomeLabel);
    mainLayout->addSpacing(15);
    
    mainLayout->addWidget(imcLabel);
    mainLayout->addWidget(tmbLabel);
    mainLayout->addSpacing(10);
 
    mainLayout->addWidget(chartView);
    
    mainLayout->addWidget(exportButton);

    mainLayout->addWidget(addMeasurementButton);
    mainLayout->addWidget(logoutButton);

    this->setLayout(mainLayout);

}

void Principal::onAddMeasurementClicked() {
    Calculo dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        double peso = dialog.getPeso();
        int sis = dialog.getPresionSis();
        int dia = dialog.getPresionDia();
        int glu = dialog.getGlucosa();

        DatabaseManager db("salud.db");

        if (db.registrarMedicion(currentUser.getId(), peso, sis, dia, glu)) {
            QMessageBox::information(this, "Éxito", "Medición guardada correctamente.");

            currentUser.setPeso(peso); // Actualizamos la memoria

            QString imcTexto = QString::number(currentUser.calcularIMC(), 'f', 2);
            QString tmbTexto = QString::number(currentUser.calcularTMB(), 'f', 2);

            imcLabel->setText("Tu IMC actual: <b>" + imcTexto + "</b>");
            tmbLabel->setText("Tu TMB actual: <b>" + tmbTexto + " kcal</b>");
            
            cargarGrafica();
        } else {
            QMessageBox::warning(this, "Error", "No se pudo guardar la medición.");
        }
    }
}

void Principal::cargarGrafica() {
    DatabaseManager db("salud.db");
    QVector<QPair<QString, double>> historial = db.obtenerHistorialPeso(currentUser.getId());

    QLineSeries *series = new QLineSeries();

    for (const auto& punto : historial) {
        QDateTime fecha = QDateTime::fromString(punto.first, "yyyy-MM-dd HH:mm:ss");
        series->append(fecha.toMSecsSinceEpoch(), punto.second);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Evolución de tu Peso");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("dd MMM");
    axisX->setTitleText("Fecha");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Peso (kg)");
    axisY->setLabelFormat("%.1f");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView->setChart(chart);
}

void Principal::onExportClicked() {
    QString rutaArchivo = QFileDialog::getSaveFileName(this, "Guardar Historial", "Historial_Salud.csv", "Archivos CSV (*.csv)");

    if (!rutaArchivo.isEmpty()) {
        DatabaseManager db("salud.db");
        if (db.exportarHistorialCSV(currentUser.getId(), rutaArchivo)) {
            QMessageBox::information(this, "Éxito", "El historial ha sido exportado correctamente.");
        } else {
            QMessageBox::warning(this, "Error", "Hubo un problema al exportar el archivo.");
        }
    }
}
