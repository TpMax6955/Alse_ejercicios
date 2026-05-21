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
    /// @brief Constructor de la ventana
    explicit Login(QWidget *parent = nullptr);
    
    /// @brief Destructor
    ~Login();

private slots:
    void onLoginClicked();
    void onRegisterClicked();

private:
    QLabel *userLabel;
    QLineEdit *userInput;
    
    QLabel *passLabel;
    QLineEdit *passInput;
    
    QPushButton *loginButton;
    QPushButton *registerButton;

    /// @brief Inicializa y organiza los widgets en la pantalla
    void setupUI();
};

#endif 
