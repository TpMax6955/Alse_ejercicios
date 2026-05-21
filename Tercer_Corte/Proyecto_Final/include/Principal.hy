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
#include "Usuario.h"
#include "Calculo.h"
#include "DatabaseManager.h"
#include <QMessageBox>

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

private:

    Usuario currentUser;

    QLabel *welcomeLabel;
    QLabel *imcLabel;
    QLabel *tmbLabel;
    
    QPushButton *addMeasurementButton;
    QPushButton *logoutButton;

    void setupUI();
};

#endif 
