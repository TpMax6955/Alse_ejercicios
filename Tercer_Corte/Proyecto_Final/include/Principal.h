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
    explicit Principal(Usuario user, QWidget *parent = nullptr);
    ~Principal();

private slots:
    void onAddMeasurementClicked(); 
    void onExportClicked();

private:
    Usuario currentUser; 
    
    QLabel *welcomeLabel;
    QLabel *imcLabel;
    QLabel *tmbLabel;
    
    QChartView *chartView; 
    void cargarGrafica();  

    QPushButton *addMeasurementButton;
    QPushButton *logoutButton;
    QPushButton *exportButton;
    
    void setupUI();
};

#endif 
