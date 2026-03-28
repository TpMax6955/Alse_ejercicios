#ifndef PANELSOLAR_H
#define PANELSOLAR_H

#include <string>
#include <vector>

/**
 * @class PanelSolar
 * @brief Representa un panel solar con eficiencia y registro de generación.
 */
class PanelSolar {
private:
    std::string id;
    float eficiencia;
    float energiaGenerada;
    std::vector<float> historialGeneracion;

public:
    /**
     * @brief Constructor de la clase PanelSolar.
     * @param id Identificador del panel.
     * @param eficiencia Eficiencia del panel.
     */
    PanelSolar(const std::string& id, float eficiencia);

    /**
     * @brief Registra una cantidad de energía generada.
     * @param wattHora Energía generada en watt-hora.
     */
    void registrarGeneracion(float wattHora);

    /**
     * @brief Retorna la energía total generada.
     * @return Energía total acumulada.
     */
    float energiaTotal() const;

    /**
     * @brief Calcula la eficiencia promedio.
     * @return Eficiencia promedio calculada.
     */
    float eficienciaPromedio() const;
};

#endif
