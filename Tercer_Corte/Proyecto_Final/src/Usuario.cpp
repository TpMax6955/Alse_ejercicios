#include "Usuario.h"

Usuario::Usuario() : id(0), edad(0), altura(0.0), peso(0.0), nivel_actividad(1.2) {}

Usuario::Usuario(int id, QString nombre, int edad, QString genero, double altura, double peso, double actividad)
    : id(id), nombre_usuario(nombre), edad(edad), genero(genero), altura(altura), peso(peso), nivel_actividad(actividad) {}

QString Usuario::getNombreUsuario() const { return nombre_usuario; }
void Usuario::setPeso(double nuevoPeso) { peso = nuevoPeso; }
double Usuario::getPeso() const { return peso; }
double Usuario::getAltura() const { return altura; }
int Usuario::getId() const { return id; }

double Usuario::calcularIMC() const {
    if (altura <= 0) return 0.0;
    return peso / (altura * altura);
}

double Usuario::calcularTMB() const {
    double altura_cm = altura * 100.0;
    
    double tmb_base = (10.0 * peso) + (6.25 * altura_cm) - (5.0 * edad);
    
    int s = (genero == "M" || genero == "m") ? 5 : -161;
    
    return (tmb_base + s) * nivel_actividad;
}
