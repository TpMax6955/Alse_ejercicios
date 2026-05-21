/**
 * @file Usuario.h
 * @brief Definición de la clase Usuario para la gestión de datos personales y cálculos de salud.
 */
#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

/**
 * @class Usuario
 * @brief Clase que representa a un usuario del sistema y realiza cálculos biométricos.
 */
class Usuario {
private:
    int id;
    QString nombre_usuario;
    int edad;
    QString genero;
    double altura; 
    double peso;   
    double nivel_actividad;

public:
    /// @brief Constructor por defecto
    Usuario();

    /// @brief Constructor con parámetros
    Usuario(int id, QString nombre, int edad, QString genero, double altura, double peso, double actividad);

    int getId() const;
    QString getNombreUsuario() const;
    void setPeso(double nuevoPeso);
    double getPeso() const;
    double getAltura() const;

    /**
     * @brief Calcula el Índice de Masa Corporal (IMC)
     * @return El valor del IMC
     */
    double calcularIMC() const;

    /**
     * @brief Calcula la Tasa Metabólica Basal usando la fórmula de Mifflin-St Jeor
     * @return Las kilocalorías diarias recomendadas
     */
    double calcularTMB() const;
};

#endif 
