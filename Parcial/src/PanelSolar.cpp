#include "~/Proyectos/Segundo_corte/Ejercicios_1/Parcial/include/PanelSolar.h"
#include <stdexcept>

PanelSolar::PanelSolar(const std::string& id, float eficiencia)
    : id(id), eficiencia(eficiencia), energiaGenerada(0.0f) {
    if (eficiencia < 0.0f || eficiencia > 1.0f) {
        throw std::invalid_argument("La eficiencia debe estar entre 0 y 1.");
    }
}

void PanelSolar::registrarGeneracion(float wattHora) {
    if (wattHora < 0.0f) {
        throw std::invalid_argument("La generacion no puede ser negativa.");
    }

    energiaGenerada += wattHora;
    historialGeneracion.push_back(wattHora);
}

float PanelSolar::energiaTotal() const {
    return energiaGenerada;
}

float PanelSolar::eficienciaPromedio() const {
    if (historialGeneracion.empty()) {
        return 0.0f;
    }

    float totalGenerado = 0.0f;
    for (float generacion : historialGeneracion) {
        totalGenerado += generacion;
    }

    return (totalGenerado / historialGeneracion.size()) * eficiencia;
}
