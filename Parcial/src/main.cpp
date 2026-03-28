#include <iostream>
#include <vector>
#include "~/Proyectos/Segundo_corte/Ejercicios_1/Parcial/include/PanelSolar.h"

int main() {
    std::vector<PanelSolar> paneles;

    try {
        PanelSolar panel1("Panel1", 0.15f);
        PanelSolar panel2("Panel2", 0.20f);

        paneles.push_back(panel1);
        paneles.push_back(panel2);

        float generacion;

        for (size_t i = 0; i < paneles.size(); i++) {
            std::cout << "Ingrese la energia generada por el panel " << i + 1 << " en watt-hora: ";
            std::cin >> generacion;
            paneles[i].registrarGeneracion(generacion);
        }

        std::cout << "\nResultados:\n";
        for (size_t i = 0; i < paneles.size(); i++) {
            std::cout << "Panel " << i + 1 << ":\n";
            std::cout << "Energia total: " << paneles[i].energiaTotal() << " Wh\n";
            std::cout << "Eficiencia promedio: " << paneles[i].eficienciaPromedio() << "\n\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
