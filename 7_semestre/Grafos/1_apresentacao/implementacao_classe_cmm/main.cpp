#include "Circulo.h"
#include <iostream>

using namespace std;

int main() {
    try {
        double raio;

        cout << "Digite o raio do circulo: ";
        cin >> raio;
    
        Circulo circulo(raio);

        circulo.imprime_area();
    }
    catch (const exception &e) {
        cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}
