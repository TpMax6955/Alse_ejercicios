/**
 * @file Calculo.h
 * @brief Ventana emergente para registrar datos médicos diarios.
 */
#ifndef CALCULO_H
#define CALCULO_H

#include <QDialog>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

/**
 * @class Calculo
 * @brief Cuadro de diálogo para ingresar peso, presión y glucosa.
 */
class Calculo : public QDialog {
    Q_OBJECT 

public:
    /// @brief Constructor de la ventana emergente
    explicit Calculo(QWidget *parent = nullptr);
    ~Calculo();


    double getPeso() const;
    int getPresionSis() const;
    int getPresionDia() const;
    int getGlucosa() const;

private:

    QDoubleSpinBox *pesoInput;
    QSpinBox *presionSisInput;
    QSpinBox *presionDiaInput;
    QSpinBox *glucosaInput;

    QPushButton *btnGuardar;
    QPushButton *btnCancelar;

    void setupUI();
};

#endif
