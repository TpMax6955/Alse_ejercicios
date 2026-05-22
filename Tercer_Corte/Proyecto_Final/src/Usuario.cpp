/**
 * @file Usuario.cpp
 * @brief Implementación de los constructores y métodos de cálculo de la clase Usuario.
 */

#include "Usuario.h"

/**
 * @brief Constructor por defecto de la clase Usuario. Inicializa los valores a cero o por defecto.
 */
Usuario::Usuario() : id(0), edad(0), altura(0.0), peso(0.0), nivel_actividad(1.2) {}

/**
 * @brief Constructor parametrizado para crear un perfil de usuario completo.
 * @param id Identificador único del usuario en la base de datos.
 * @param nombre Nombre de usuario.
 * @param edad Edad en años cronológicos.
 * @param genero Identidad de género biológica ("M" o "m" para masculino, otro para femenino).
 * @param altura Estatura física en metros.
 * @param peso Peso corporal en kilogramos.
 * @param actividad Factor multiplicador del nivel de actividad física.
 */
Usuario::Usuario(int id, QString nombre, int edad, QString genero, double altura, double peso, double actividad)
    : id(id), nombre_usuario(nombre), edad(edad), genero(genero), altura(altura), peso(peso), nivel_actividad(actividad) {}

/**
 * @brief Obtiene el nombre registrado del usuario.
 * @return Cadena de texto con el nombre de usuario.
 */
QString Usuario::getNombreUsuario() const { return nombre_usuario; }

/**
 * @brief Actualiza el peso actual del usuario en la memoria.
 * @param nuevoPeso El valor del nuevo peso en kilogramos a registrar.
 */
void Usuario::setPeso(double nuevoPeso) { peso = nuevoPeso; }

/**
 * @brief Obtiene el peso actual registrado del usuario.
 * @return El peso en kilogramos.
 */
double Usuario::getPeso() const { return peso; }

/**
 * @brief Obtiene la estatura del usuario.
 * @return La altura en metros.
 */
double Usuario::getAltura() const { return altura; }

/**
 * @brief Obtiene el identificador único del usuario.
 * @return Un entero que representa el ID del usuario.
 */
int Usuario::getId() const { return id; }

/**
 * @brief Calcula el Índice de Masa Corporal (IMC) del usuario en base a su peso y altura.
 * @return El valor del cálculo del IMC, o 0.0 si la altura registrada es menor o igual a 0.
 */
double Usuario::calcularIMC() const {
    if (altura <= 0) return 0.0;
    return peso / (altura * altura);
}

/**
 * @brief Calcula la Tasa Metabólica Basal (TMB) aplicando la fórmula de Mifflin-St Jeor.
 * @return El requerimiento calórico diario estimado (TMB) ajustado al nivel de actividad.
 */
double Usuario::calcularTMB() const {
    double altura_cm = altura * 100.0;
    
    double tmb_base = (10.0 * peso) + (6.25 * altura_cm) - (5.0 * edad);
    
    int s = (genero == "M" || genero == "m") ? 5 : -161;
    
    return (tmb_base + s) * nivel_actividad;
}