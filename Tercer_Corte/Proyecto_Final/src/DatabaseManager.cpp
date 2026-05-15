#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager(const QString& path) : m_path(path) {}

DatabaseManager::~DatabaseManager() {
    if (m_db.isOpen()) m_db.close();
}

bool DatabaseManager::init() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_path);

    if (!m_db.open()) {
        qDebug() << "Error abriendo la base de datos:" << m_db.lastError().text();
        return false;
    }
    return createTables();
}

bool DatabaseManager::createTables() {
    QSqlQuery query;
    
    QString usersTable = "CREATE TABLE IF NOT EXISTS usuarios ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         "nombre_usuario TEXT UNIQUE,"
                         "password TEXT,"
                         "edad INTEGER,"
                         "genero TEXT,"
                         "altura REAL,"
                         "nivel_actividad REAL)";
    
    QString measurementsTable = "CREATE TABLE IF NOT EXISTS mediciones ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "usuario_id INTEGER,"
                                "fecha_hora TEXT,"
                                "peso REAL,"
                                "presion_sis INTEGER,"
                                "presion_dia INTEGER,"
                                "glucosa INTEGER,"
                                "FOREIGN KEY(usuario_id) REFERENCES usuarios(id))";

    return query.exec(usersTable) && query.exec(measurementsTable);
}
