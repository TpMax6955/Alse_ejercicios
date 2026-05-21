#include <QApplication>
#include <QDebug>
#include "DatabaseManager.h"
#include "Login.h"

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
