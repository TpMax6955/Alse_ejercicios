/**
 * @file DatabaseManager.h
 * @brief Clase para gestionar la conexión y operaciones en SQLite3.
 */
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QVector>
#include <QPair>
#include "Usuario.h"

/**
 * @class DatabaseManager
 * @brief Gestiona la persistencia de datos de salud y usuarios.
 */
class DatabaseManager {
public:
    DatabaseManager();
    DatabaseManager(const QString& path);
    ~DatabaseManager();

    bool init();

    bool validarUsuario(const QString& username, const QString& password);
    Usuario obtenerUsuario(const QString& username);
    bool registrarUsuario(const QString& username, const QString& password, int edad, const QString& genero, double altura, double peso, double actividad);
    bool registrarMedicion(int usuario_id, double peso, int presion_sis, int presion_dia, int glucosa);
    
    QVector<QPair<QString, double>> obtenerHistorialPeso(int usuario_id);
    bool exportarHistorialCSV(int usuario_id, const QString& ruta_archivo);

private:
    QSqlDatabase m_db;
    QString m_path;

    bool createTables();
};

#endif // DATABASEMANAGER_H
