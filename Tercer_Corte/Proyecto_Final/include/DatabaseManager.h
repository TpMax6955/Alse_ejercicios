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
    /**
     * @brief Constructor por defecto de DatabaseManager.
     */
    DatabaseManager();

    /**
     * @brief Constructor parametrizado que recibe la ruta de la base de datos.
     * @param path Ruta o nombre del archivo de la base de datos.
     */
    DatabaseManager(const QString& path);

    /**
     * @brief Destructor de la clase DatabaseManager.
     */
    ~DatabaseManager();

    /**
     * @brief Inicializa la base de datos y prepara las tablas.
     * @return true si la inicialización fue exitosa, false en caso contrario.
     */
    bool init();

    /**
     * @brief Valida si el usuario y la contraseña coinciden con los registros.
     * @param username Nombre de usuario.
     * @param password Contraseña.
     * @return true si las credenciales son válidas, false de lo contrario.
     */
    bool validarUsuario(const QString& username, const QString& password);

    /**
     * @brief Obtiene un objeto Usuario con la información almacenada en la base de datos.
     * @param username Nombre del usuario a consultar.
     * @return Objeto Usuario con sus respectivos datos.
     */
    Usuario obtenerUsuario(const QString& username);

    /**
     * @brief Registra un nuevo usuario en la base de datos.
     * @param username Nombre de usuario.
     * @param password Contraseña.
     * @param edad Edad del usuario.
     * @param genero Género del usuario.
     * @param altura Altura en metros.
     * @param peso Peso en kilogramos.
     * @param actividad Factor de nivel de actividad física.
     * @return true si el registro fue exitoso, false si falló.
     */
    bool registrarUsuario(const QString& username, const QString& password, int edad, const QString& genero, double altura, double peso, double actividad);

    /**
     * @brief Registra una nueva medición de indicadores de salud para un usuario.
     * @param usuario_id ID del usuario al que pertenece la medición.
     * @param peso Peso registrado en kg.
     * @param presion_sis Presión sistólica en mmHg.
     * @param presion_dia Presión diastólica en mmHg.
     * @param glucosa Nivel de glucosa en mg/dL.
     * @return true si la medición se guardó con éxito, false en caso de error.
     */
    bool registrarMedicion(int usuario_id, double peso, int presion_sis, int presion_dia, int glucosa);
    
    /**
     * @brief Obtiene el historial de peso de un usuario ordenado cronológicamente.
     * @param usuario_id ID del usuario a consultar.
     * @return Un QVector de pares con la fecha (QString) y el peso (double).
     */
    QVector<QPair<QString, double>> obtenerHistorialPeso(int usuario_id);

    /**
     * @brief Exporta el historial médico de un usuario a un archivo de formato CSV.
     * @param usuario_id ID del usuario.
     * @param ruta_archivo Ruta física donde se creará el archivo CSV.
     * @return true si la exportación fue exitosa, false en caso de fallo.
     */
    bool exportarHistorialCSV(int usuario_id, const QString& ruta_archivo);

private:
    QSqlDatabase m_db; /**< Objeto de conexión a la base de datos de Qt. */
    QString m_path;    /**< Ruta del archivo de base de datos SQLite3. */

    /**
     * @brief Crea las tablas de usuarios y mediciones si no existen en la base de datos.
     * @return true si las tablas se crearon o ya existían correctamente.
     */
    bool createTables();
};

#endif // DATABASEMANAGER_H