/**
 * @file Login.cpp
 * @brief Implementación de la ventana de inicio de sesión y registro de HealthSync.
 */

#include "Login.h"
#include "DatabaseManager.h"
#include "Principal.h"
#include <QDebug>

/**
 * @brief Constructor de la clase Login. Inicializa la interfaz gráfica.
 * @param parent Widget padre de la ventana.
 */
Login::Login(QWidget *parent) : QWidget(parent) {
    setupUI();
}

/**
 * @brief Destructor de la clase Login.
 */
Login::~Login() {
}

/**
 * @brief Configura e inicializa los elementos visuales, layouts y conexiones de los botones en la ventana.
 */
void Login::setupUI() {
    this->setWindowTitle("HealthSync - Iniciar Sesión");
    this->resize(350, 250);

    userLabel = new QLabel("Nombre de Usuario:", this);
    userInput = new QLineEdit(this);
    userInput->setPlaceholderText("Ej: max_alse");

    passLabel = new QLabel("Contraseña:", this);
    passInput = new QLineEdit(this);
    passInput->setEchoMode(QLineEdit::Password); 
    passInput->setPlaceholderText("Tu contraseña");

    loginButton = new QPushButton("Iniciar Sesión", this);
    registerButton = new QPushButton("Registrarse", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    mainLayout->addWidget(userLabel);
    mainLayout->addWidget(userInput);
    mainLayout->addSpacing(10); 
    
    mainLayout->addWidget(passLabel);
    mainLayout->addWidget(passInput);
    mainLayout->addSpacing(20);
    
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(registerButton);

    this->setLayout(mainLayout);
    
    connect(loginButton, &QPushButton::clicked, this, &Login::onLoginClicked);
    connect(registerButton, &QPushButton::clicked, this, &Login::onRegisterClicked);
}

/**
 * @brief Gestiona el evento de clic en el botón de inicio de sesión.
 * Valida las credenciales con la base de datos y, si son correctas, abre el Dashboard principal.
 */
void Login::onLoginClicked() {
    QString user = userInput->text();
    QString pass = passInput->text();

    DatabaseManager db("salud.db");
    
    if(db.validarUsuario(user, pass)) {
        QMessageBox::information(this, "Éxito", "¡Inicio de sesión correcto!");
  
        Usuario usuarioLogueado = db.obtenerUsuario(user);     
 
        Principal *ventanaDashboard = new Principal(usuarioLogueado);
        
        ventanaDashboard->show();
        
        this->close(); 
        
    } else {
        QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos.");
    }
}

/**
 * @brief Gestiona el evento de clic en el botón de registro.
 * Crea un nuevo usuario en la base de datos asignándole valores médicos iniciales por defecto.
 */
void Login::onRegisterClicked() {
    QString user = userInput->text();
    QString pass = passInput->text();

    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor, llena ambos campos.");
        return;
    }

    DatabaseManager db("salud.db");
    
    if(db.registrarUsuario(user, pass, 25, "M", 1.75, 70.0, 1.2)) {
        QMessageBox::information(this, "Éxito", "Usuario registrado. Ya puedes iniciar sesión.");
    } else {
        QMessageBox::warning(this, "Error", "No se pudo registrar. El usuario ya existe.");
    }
}