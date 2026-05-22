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
    int id;                 /**< Identificador único del usuario. */
    QString nombre_usuario; /**< Nombre de cuenta del usuario. */
    int edad;               /**< Edad en años cronológicos. */
    QString genero;         /**< Género registrado ("M" o "F"). */
    double altura;          /**< Altura física en metros. */
    double peso;            /**< Peso corporal en kilogramos. */
    double nivel_actividad; /**< Factor de nivel de actividad física. */

public:
    /**
     * @brief Constructor por defecto.
     */
    Usuario();

    /**
     * @brief Constructor con parámetros para inicializar el perfil del usuario.
     * @param id ID único.
     * @param nombre Nombre del usuario.
     * @param edad Edad en años.
     * @param genero Género del usuario.
     * @param altura Altura en metros.
     * @param peso Peso en kg.
     * @param actividad Factor de nivel de actividad.
     */
    Usuario(int id, QString nombre, int edad, QString genero, double altura, double peso, double actividad);

    /**
     * @brief Obtiene el identificador único del usuario.
     * @return El ID del usuario.
     */
    int getId() const;

    /**
     * @brief Obtiene el nombre del usuario.
     * @return El nombre de usuario.
     */
    QString getNombreUsuario() const;

    /**
     * @brief Actualiza el peso del usuario en memoria.
     * @param nuevoPeso El peso a registrar en kg.
     */
    void setPeso(double nuevoPeso);

    /**
     * @brief Obtiene el peso actual del usuario.
     * @return El peso en kg.
     */
    double getPeso() const;

    /**
     * @brief Obtiene la altura del usuario.
     * @return La altura en metros.
     */
    double getAltura() const;

    /**
     * @brief Calcula el Índice de Masa Corporal (IMC).
     * @return El valor del IMC.
     */
    double calcularIMC() const;

    /**
     * @brief Calcula la Tasa Metabólica Basal usando la fórmula de Mifflin-St Jeor.
     * @return Las kilocalorías diarias recomendadas.
     */
    double calcularTMB() const;
};

#endif