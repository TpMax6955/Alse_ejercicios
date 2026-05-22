/**
 * @file DatabaseManager.cpp
 * @brief Implementación de las operaciones de la base de datos SQLite para HealthSync.
 */

#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVariant>

/**
 * @brief Constructor de la clase DatabaseManager.
 * @param path Ruta del archivo de la base de datos SQLite.
 */
DatabaseManager::DatabaseManager(const QString& path) : m_path(path) {}

/**
 * @brief Destructor de la clase DatabaseManager. Cierra la conexión si está abierta.
 */
DatabaseManager::~DatabaseManager() {
    if (m_db.isOpen()) m_db.close();
}

/**
 * @brief Inicializa la conexión con la base de datos y crea las tablas necesarias.
 * @return true si la conexión y creación de tablas fue exitosa, false en caso contrario.
 */
bool DatabaseManager::init() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_path);

    if (!m_db.open()) {
        qDebug() << "Error abriendo la base de datos:" << m_db.lastError().text();
        return false;
    }
    return createTables();
}

/**
 * @brief Crea las tablas de 'usuarios' y 'mediciones' en la base de datos si no existen.
 * @return true si las tablas se crearon o ya existían correctamente, false en caso de error.
 */
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

/**
 * @brief Valida las credenciales de un usuario en la base de datos.
 * @param username Nombre de usuario a validar.
 * @param password Contraseña ingresada por el usuario.
 * @return true si las credenciales coinciden, false si son incorrectas o no existe el usuario.
 */
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

/**
 * @brief Registra un nuevo usuario en la base de datos.
 * @param username Nombre de usuario único.
 * @param password Contraseña de la cuenta.
 * @param edad Edad cronológica del usuario.
 * @param genero Identidad de género.
 * @param altura Estatura en metros.
 * @param peso Peso inicial en kilogramos.
 * @param actividad Nivel de actividad física del usuario.
 * @return true si el registro se completó con éxito, false en caso de error.
 */
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

/**
 * @brief Obtiene el objeto Usuario completo con sus datos médicos más recientes desde la base de datos.
 * @param username El nombre de usuario que se desea recuperar.
 * @return Un objeto Usuario instanciado con los datos encontrados.
 */
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

/**
 * @brief Registra una nueva medición de salud para un usuario específico.
 * @param usuario_id El identificador único del usuario en la base de datos.
 * @param peso Peso medido en kilogramos.
 * @param presion_sis Presión arterial sistólica en mmHg.
 * @param presion_dia Presión arterial diastólica en mmHg.
 * @param glucosa Nivel de glucosa en mg/dL.
 * @return true si la medición se guardó correctamente, false en caso de error.
 */
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

/**
 * @brief Obtiene el historial cronológico de peso de un usuario para graficarlo.
 * @param usuario_id El identificador del usuario.
 * @return Un vector de pares que contiene la fecha y hora como QString y el peso como double.
 */
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

/**
 * @brief Exporta todas las mediciones de un usuario a un archivo en formato CSV.
 * @param usuario_id El identificador del usuario.
 * @param ruta_archivo La ruta absoluta o relativa donde se guardará el archivo CSV.
 * @return true si el archivo se exportó con éxito, false si no se pudo escribir.
 */
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