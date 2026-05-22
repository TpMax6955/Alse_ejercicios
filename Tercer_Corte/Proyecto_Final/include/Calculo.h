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
    /**
     * @brief Constructor de la ventana emergente.
     * @param parent Widget padre del diálogo.
     */
    explicit Calculo(QWidget *parent = nullptr);

    /**
     * @brief Destructor de la clase Calculo.
     */
    ~Calculo();


    /**
     * @brief Obtiene el valor del peso ingresado por el usuario.
     * @return El peso en kilogramos (kg) como decimal.
     */
    double getPeso() const;

    /**
     * @brief Obtiene el valor de la presión sistólica ingresada.
     * @return La presión sistólica en milímetros de mercurio (mmHg).
     */
    int getPresionSis() const;

    /**
     * @brief Obtiene el valor de la presión diastólica ingresada.
     * @return La presión diastólica en milímetros de mercurio (mmHg).
     */
    int getPresionDia() const;

    /**
     * @brief Obtiene el nivel de glucosa ingresado por el usuario.
     * @return El nivel de glucosa en mg/dL.
     */
    int getGlucosa() const;

private:

    /**
     * @brief Control numérico decimal para el ingreso del peso.
     */
    QDoubleSpinBox *pesoInput;

    /**
     * @brief Control numérico entero para el ingreso de la presión sistólica.
     */
    QSpinBox *presionSisInput;

    /**
     * @brief Control numérico entero para el ingreso de la presión diastólica.
     */
    QSpinBox *presionDiaInput;

    /**
     * @brief Control numérico entero para el ingreso de la glucosa.
     */
    QSpinBox *glucosaInput;

    /**
     * @brief Botón para confirmar y guardar la medición registrada.
     */
    QPushButton *btnGuardar;

    /**
     * @brief Botón para cancelar la operación y cerrar la ventana emergente.
     */
    QPushButton *btnCancelar;

    /**
     * @brief Inicializa y organiza los elementos visuales dentro de la ventana.
     */
    void setupUI();
};

#endif