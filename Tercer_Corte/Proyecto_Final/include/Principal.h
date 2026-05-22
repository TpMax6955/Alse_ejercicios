/**
 * @file Principal.h
 * @brief Definición de la ventana principal (Dashboard) de HealthSync.
 */
#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QtCharts> 
QT_CHARTS_USE_NAMESPACE
#include "Usuario.h"
#include "Calculo.h"
#include "DatabaseManager.h" 

/**
 * @class Principal
 * @brief Interfaz principal que muestra el resumen del usuario y opciones de salud.
 */
class Principal : public QWidget {
    Q_OBJECT 

public:
    /**
     * @brief Constructor de la ventana principal.
     * @param user Objeto Usuario con la sesión activa.
     * @param parent Widget padre de la ventana.
     */
    explicit Principal(Usuario user, QWidget *parent = nullptr);

    /**
     * @brief Destructor de la clase Principal.
     */
    ~Principal();

private slots:
    /**
     * @brief Abre el formulario para registrar una nueva medición.
     */
    void onAddMeasurementClicked(); 

    /**
     * @brief Procesa la exportación del historial a un archivo CSV.
     */
    void onExportClicked();

    /**
     * @brief Gestiona el cierre de sesión del usuario.
     */
    void on_btnCerrarSesion_clicked();

private:
    /**
     * @brief Datos del usuario de la sesión actual.
     */
    Usuario currentUser; 
    
    /**
     * @brief Etiqueta de bienvenida.
     */
    QLabel *welcomeLabel;

    /**
     * @brief Etiqueta que muestra el IMC.
     */
    QLabel *imcLabel;

    /**
     * @brief Etiqueta que muestra la TMB.
     */
    QLabel *tmbLabel;
    
    /**
     * @brief Contenedor visual para el gráfico de QtCharts.
     */
    QChartView *chartView; 

    /**
     * @brief Genera y actualiza la gráfica de evolución de peso.
     */
    void cargarGrafica();  

    /**
     * @brief Botón para registrar nueva medición.
     */
    QPushButton *addMeasurementButton;

    /**
     * @brief Botón para cerrar sesión.
     */
    QPushButton *logoutButton;

    /**
     * @brief Botón para exportar historial.
     */
    QPushButton *exportButton;
    
    /**
     * @brief Configura la interfaz gráfica y layouts.
     */
    void setupUI();
};

#endif