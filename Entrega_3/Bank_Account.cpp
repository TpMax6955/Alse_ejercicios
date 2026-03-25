#include <iostream>
#include <stdexcept>

class CuentaBancaria {
private:
    double saldo_;
    bool esta_abierta_;

public:
    CuentaBancaria() : saldo_(0.0), esta_abierta_(true) {}

    void depositar(double monto) {
        if (!esta_abierta_) {
            throw std::runtime_error("La cuenta está cerrada.");
        }
        if (monto <= 0) {
            throw std::invalid_argument("El monto del depósito debe ser positivo.");
        }
        saldo_ += monto;
    }

    void retirar(double monto) {
        if (!esta_abierta_) {
            throw std::runtime_error("La cuenta está cerrada.");
        }
        if (monto <= 0) {
            throw std::invalid_argument("El monto de retiro debe ser positivo.");
        }
        if (monto > saldo_) {
            throw std::runtime_error("Fondos insuficientes.");
        }
        saldo_ -= monto;
    }

    double saldo() const {
        if (!esta_abierta_) {
            throw std::runtime_error("La cuenta está cerrada.");
        }
        return saldo_;
    }

    void cerrar() {
        if (!esta_abierta_) {
            throw std::runtime_error("La cuenta ya está cerrada.");
        }
        saldo_ = 0.0;
        esta_abierta_ = false;
    }

    bool esta_abierta() const {
        return esta_abierta_;
    }
};

int main() {
    try {
        CuentaBancaria cuenta;
        cuenta.depositar(1000);
        std::cout << "Saldo después del depósito: " << cuenta.saldo() << std::endl;

        cuenta.retirar(500);
        std::cout << "Saldo después del retiro: " << cuenta.saldo() << std::endl;

        cuenta.cerrar();
        std::cout << "Cuenta cerrada." << std::endl;

        cuenta.depositar(200);

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
