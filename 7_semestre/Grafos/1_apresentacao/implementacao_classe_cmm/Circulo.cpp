#include "Circulo.h"
#include <iostream>

using namespace std;

Circulo::Circulo(double raio) {
    if (raio <= 0) {
        throw(invalid_argument("Erro no construtor Circulo(double): o raio " +
            to_string(raio) + " eh invalido!"));
    }

    raio_ = raio;
}

double Circulo::calcula_area() {
    return (3.1416 * raio_ * raio_);
}

void Circulo::imprime_area() {
    cout << "Area: " << calcula_area() << "\n";
}

double Circulo::calcula_perimetro() {
    return (2 * raio_ * 3.1416);
}

void Circulo::imprime_perimetro() {
    cout << "Perimetro: " << calcula_perimetro() << "\n";
}