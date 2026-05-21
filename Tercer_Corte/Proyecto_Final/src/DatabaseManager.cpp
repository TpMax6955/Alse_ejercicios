#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
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

bool DatabaseManager::validarUsuario(const QString& username, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT password FROM usuarios WHERE nombre_usuario = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        QString dbPassword = query.value(0).toString();
        if (dbPassword == password) {
            return true;
        }
    }
    return false;
}

bool DatabaseManager::registrarUsuario(const QString& username, const QString& password, int edad, const QString& genero, double altura, double peso, double actividad) {
    QSqlQuery query;
    query.prepare("INSERT INTO usuarios (nombre_usuario, password, edad, genero, altura, nivel_actividad) "
                  "VALUES (:user, :pass, :edad, :genero, :altura, :actividad)");
                  
    query.bindValue(":user", username);
    query.bindValue(":pass", password);
    query.bindValue(":edad", edad);
    query.bindValue(":genero", genero);
    query.bindValue(":altura", altura);
    query.bindValue(":actividad", actividad);

    if (query.exec()) {
        qDebug() << "✅ Usuario registrado con éxito.";
        return true;
    } else {
        qDebug() << "❌ Error al registrar usuario:" << query.lastError().text();
        return false;
    }
}

Usuario DatabaseManager::obtenerUsuario(const QString& username) {
    QSqlQuery query;
    query.prepare("SELECT id, edad, genero, altura, nivel_actividad FROM usuarios WHERE nombre_usuario = :user");
    query.bindValue(":user", username);

    if (query.exec() && query.next()) {
        int id = query.value(0).toInt();
        int edad = query.value(1).toInt();
        QString genero = query.value(2).toString();
        double altura = query.value(3).toDouble();
        double actividad = query.value(4).toDouble();

 
        double peso = 70.0; 
        QSqlQuery pesoQuery;
        pesoQuery.prepare("SELECT peso FROM mediciones WHERE usuario_id = :id ORDER BY id DESC LIMIT 1");
        pesoQuery.bindValue(":id", id);
        
        if (pesoQuery.exec() && pesoQuery.next()) {
            peso = pesoQuery.value(0).toDouble();
        }

        return Usuario(id, username, edad, genero, altura, peso, actividad);
    }
    
    return Usuario();
}
bool DatabaseManager::registrarMedicion(int usuario_id, double peso, int presion_sis, int presion_dia, int glucosa) {
    QSqlQuery query;
    query.prepare("INSERT INTO mediciones (usuario_id, fecha_hora, peso, presion_sis, presion_dia, glucosa) "
                  "VALUES (:uid, datetime('now', 'localtime'), :peso, :psis, :pdia, :glu)");

    query.bindValue(":uid", usuario_id);
    query.bindValue(":peso", peso);
    query.bindValue(":psis", presion_sis);
    query.bindValue(":pdia", presion_dia);
    query.bindValue(":glu", glucosa);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "❌ Error al registrar medición:" << query.lastError().text();
        return false;
    }
}

QVector<QPair<QString, double>> DatabaseManager::obtenerHistorialPeso(int usuario_id) {
    QVector<QPair<QString, double>> historial;
    QSqlQuery query;
    
    query.prepare("SELECT fecha_hora, peso FROM mediciones WHERE usuario_id = :uid ORDER BY fecha_hora ASC");
    query.bindValue(":uid", usuario_id);

    if (query.exec()) {

        while (query.next()) {
            QString fecha = query.value(0).toString();
            double peso = query.value(1).toDouble();
            
            historial.append(qMakePair(fecha, peso));
        }
    } else {
        qDebug() << "❌ Error al obtener historial para la gráfica:" << query.lastError().text();
    }
    
    return historial;
}

bool DatabaseManager::exportarHistorialCSV(int usuario_id, const QString& ruta_archivo) {
    QFile file(ruta_archivo);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "❌ No se pudo abrir el archivo para escribir.";
        return false;
    }

    QTextStream out(&file);
    
    out << "Fecha y Hora,Peso (kg),Presion Sistolica (mmHg),Presion Diastolica (mmHg),Glucosa (mg/dL)\n";
     
    QSqlQuery query;
    query.prepare("SELECT fecha_hora, peso, presion_sis, presion_dia, glucosa FROM mediciones WHERE usuario_id = :uid ORDER BY fecha_hora ASC");
    query.bindValue(":uid", usuario_id);

    if (query.exec()) {
        while (query.next()) {
            out << query.value(0).toString() << ","
                << query.value(1).toString() << ","
                << query.value(2).toString() << ","
                << query.value(3).toString() << ","
                << query.value(4).toString() << "\n";
        }
        file.close();
        return true;
    }
     
    file.close();
    return false;
}
