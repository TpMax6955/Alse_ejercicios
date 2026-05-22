/**
 * @file main.cpp
 * @brief Archivo principal que inicializa la aplicación HealthSync y la conexión a la base de datos.
 */

#include <QApplication>
#include <QDebug>
#include "DatabaseManager.h"
#include "Login.h"

/**
 * @brief Función principal de la aplicación.
 * @param argc Número de argumentos de la línea de comandos.
 * @param argv Arreglo de argumentos de la línea de comandos.
 * @return Código de estado al finalizar la ejecución (0 si es exitoso, -1 si falla la base de datos).
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    DatabaseManager db("salud.db");

    if (db.init()) {
        qDebug() << "✅ ¡Conexión exitosa! La base de datos y las tablas están listas.";
    } else {
        qDebug() << "❌ Error crítico: No se pudo inicializar la base de datos.";
        return -1;
    }

    Login loginWindow;
    loginWindow.show();

    return app.exec(); 
}