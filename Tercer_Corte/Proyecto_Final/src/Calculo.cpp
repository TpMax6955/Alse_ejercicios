#include "Calculo.h"
#include <QFormLayout> 

Calculo::Calculo(QWidget *parent) : QDialog(parent) {
    setupUI();
}

Calculo::~Calculo() {

}

void Calculo::setupUI() {
    this->setWindowTitle("Registrar Nueva Medición");
    this->resize(300, 250);

    pesoInput = new QDoubleSpinBox(this);
    pesoInput->setRange(20.0, 300.0); // Solo permite entre 20kg y 300kg
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

double Calculo::getPeso() const { return pesoInput->value(); }
int Calculo::getPresionSis() const { return presionSisInput->value(); }
int Calculo::getPresionDia() const { return presionDiaInput->value(); }
int Calculo::getGlucosa() const { return glucosaInput->value(); }
