/**
 * @file Calculo.cpp
 * @brief Implementación de la ventana de diálogo para registrar una nueva medición médica diaria.
 */

#include "Calculo.h"
#include <QFormLayout> 

/**
 * @brief Constructor de la clase Calculo. Inicializa la interfaz del diálogo.
 * @param parent Widget padre de la ventana.
 */
Calculo::Calculo(QWidget *parent) : QDialog(parent) {
    setupUI();
}

/**
 * @brief Destructor de la clase Calculo.
 */
Calculo::~Calculo() {

}

/**
 * @brief Configura y organiza los elementos visuales (widgets) de la ventana de registro de medición.
 */
void Calculo::setupUI() {
    this->setWindowTitle("Registrar Nueva Medición");
    this->resize(300, 250);

    pesoInput = new QDoubleSpinBox(this);
    pesoInput->setRange(20.0, 300.0); 
    pesoInput->setSuffix(" kg");

    presionSisInput = new QSpinBox(this);
    presionSisInput->setRange(50, 250);
    presionSisInput->setSuffix(" mmHg");

    presionDiaInput = new QSpinBox(this);
    presionDiaInput->setRange(30, 150);
    presionDiaInput->setSuffix(" mmHg");

    glucosaInput = new QSpinBox(this);
    glucosaInput->setRange(40, 500);
    glucosaInput->setSuffix(" mg/dL");

    btnGuardar = new QPushButton("Guardar", this);
    btnCancelar = new QPushButton("Cancelar", this);

    connect(btnGuardar, &QPushButton::clicked, this, &Calculo::accept);
    connect(btnCancelar, &QPushButton::clicked, this, &Calculo::reject);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Peso actual:", pesoInput);
    formLayout->addRow("Presión Sistólica:", presionSisInput);
    formLayout->addRow("Presión Diastólica:", presionDiaInput);
    formLayout->addRow("Nivel de Glucosa:", glucosaInput);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(btnCancelar);
    buttonLayout->addWidget(btnGuardar);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);

    this->setLayout(mainLayout);
}

/**
 * @brief Obtiene el valor del peso ingresado por el usuario.
 * @return El peso en kilogramos como valor numérico de punto flotante.
 */
double Calculo::getPeso() const { return pesoInput->value(); }

/**
 * @brief Obtiene el valor de la presión arterial sistólica ingresada por el usuario.
 * @return La presión sistólica en milímetros de mercurio (mmHg).
 */
int Calculo::getPresionSis() const { return presionSisInput->value(); }

/**
 * @brief Obtiene el valor de la presión arterial diastólica ingresada por el usuario.
 * @return La presión diastólica en milímetros de mercurio (mmHg).
 */
int Calculo::getPresionDia() const { return presionDiaInput->value(); }

/**
 * @brief Obtiene el valor del nivel de glucosa ingresado por el usuario.
 * @return El nivel de glucosa en mg/dL.
 */
int Calculo::getGlucosa() const { return glucosaInput->value(); }