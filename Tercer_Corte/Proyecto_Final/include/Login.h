/**
 * @file Login.h
 * @brief Definición de la ventana de inicio de sesión de HealthSync.
 */
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox> 

/**
 * @class Login
 * @brief Interfaz gráfica para la autenticación y registro de usuarios.
 */
class Login : public QWidget {
    Q_OBJECT 

public:
    /**
     * @brief Constructor de la ventana.
     * @param parent Widget padre de la ventana.
     */
    explicit Login(QWidget *parent = nullptr);
    
    /**
     * @brief Destructor de la clase Login.
     */
    ~Login();

private slots:
    /**
     * @brief Procesa el evento de clic en el botón de inicio de sesión.
     */
    void onLoginClicked();

    /**
     * @brief Procesa el evento de clic en el botón de registro de nuevo usuario.
     */
    void onRegisterClicked();

private:
    /**
     * @brief Etiqueta de texto para el campo de usuario.
     */
    QLabel *userLabel;

    /**
     * @brief Campo de entrada de texto para el nombre de usuario.
     */
    QLineEdit *userInput;
    
    /**
     * @brief Etiqueta de texto para el campo de contraseña.
     */
    QLabel *passLabel;

    /**
     * @brief Campo de entrada de texto protegido para la contraseña.
     */
    QLineEdit *passInput;
    
    /**
     * @brief Botón para ejecutar la acción de iniciar sesión.
     */
    QPushButton *loginButton;

    /**
     * @brief Botón para ejecutar la acción de registrar un usuario.
     */
    QPushButton *registerButton;

    /**
     * @brief Inicializa y organiza los widgets en la pantalla.
     */
    void setupUI();
};

#endif