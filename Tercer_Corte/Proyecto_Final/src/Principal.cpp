/**
 * @file Principal.cpp
 * @brief Implementación de la ventana principal (Dashboard) y sus funcionalidades interactivas.
 */

#include "Principal.h"
#include <QString>
#include <QDateTime>
#include <QFileDialog>
#include "Login.h"
#include <QMessageBox>

/**
 * @brief Constructor de la clase Principal. Construye el entorno de la sesión activa.
 * @param user Datos estructurados del usuario logueado actualmente.
 * @param parent Widget padre de la ventana.
 */
Principal::Principal(Usuario user, QWidget *parent) : QWidget(parent), currentUser(user) {
    setupUI();
    connect(addMeasurementButton, &QPushButton::clicked, this, &Principal::onAddMeasurementClicked);
    connect(logoutButton, &QPushButton::clicked, this, &Principal::on_btnCerrarSesion_clicked);
}

/**
 * @brief Destructor de la clase Principal.
 */
Principal::~Principal() {

}

/**
 * @brief Configura e inicializa todos los elementos visuales de la interfaz principal.
 */
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

/**
 * @brief Muestra el diálogo para registrar una nueva medición y actualiza la base de datos y la interfaz.
 */
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

            currentUser.setPeso(peso); 

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

/**
 * @brief Gestiona el evento de cerrar sesión confirmando la acción con el usuario.
 */
void Principal::on_btnCerrarSesion_clicked() {
    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::question(this, "Cerrar Sesión", 
                                      "¿Estás seguro de que deseas cerrar sesión?",
                                      QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::Yes) {
        this->hide();

        Login *ventanaLogin = new Login();
        ventanaLogin->show();

        this->deleteLater();
    }
}

/**
 * @brief Consulta el historial de peso en la base de datos y genera la gráfica evolutiva.
 */
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

/**
 * @brief Abre un cuadro de diálogo para exportar el historial médico a un archivo CSV.
 */
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