/**
 * @file DatabaseManager.h
 * @brief Clase para gestionar la conexión y operaciones en SQLite3.
 */
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

/**
 * @class DatabaseManager
 * @brief Gestiona la persistencia de datos de salud y usuarios.
 */
class DatabaseManager {
public:
    DatabaseManager(const QString& path);
    ~DatabaseManager();

    bool init();

private:
    QSqlDatabase m_db;
    QString m_path;

    bool createTables();
};

#endif
