/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  Introduce aquí los nombres de los componentes del grupo:

  Componente 1: Alejandro Valencia Blancas
  Componente 2: Juan Embid Sánchez
  */

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_ELEMS = 2000;


class Multiconjunto {
public:
    // No olvides el coste!

    bool pertenece(int elem) { //Esto está bien, NO SE TOCA
        int pos = buscar(elem, 0, num_elems);
        return elem == elems[pos].valor && elems[pos].multiplicidad > 0;
    }

    void anyadir(int elem) {
        if (pertenece(elem)) {
            elems[buscar(elem, 0, num_elems)].multiplicidad++; //si pertenece aumenta multiplicidad
        }
        else {
            if (num_elems == 0) { //si no pertenece y no hay elementos lo mete en la primera posición
                elems[0].valor = elem;
                elems[0].multiplicidad++;
                num_elems++;
            }
            else { //si no pertenece y si hay elementos
                for (int i = num_elems; i > buscar(elem, 0, num_elems) && buscar(elem, 0, num_elems) != num_elems; i--) {
                    elems[i] = elems[i - 1];
                }
                elems[buscar(elem, 0, num_elems)].valor = elem;
                elems[buscar(elem, 0, num_elems)].multiplicidad = 1;
                num_elems++;
            }
        }
    }

    void eliminar(int elem) {
 //creo que hay que poner esto, porque si bajas la multiplicidad nunca se llega a eliminar
        elems[buscar(elem, 0, num_elems - 1)].multiplicidad--; 
       /* if (elems[buscar(elem, 0, num_elems - 1)].multiplicidad == 0)
            elems[buscar(elem, 0, num_elems - 1)].valor = -1;*/

    }

private:
    bool ok = false;

    int buscar(int elem, int inicio, int fin) { //CORRECTA NO TOCAR
        int centro = (fin + inicio) / 2;

        if (fin < inicio) {
            return centro;
        }

        if (elem < elems[centro].valor) {
            return buscar(elem, inicio, (centro - 1));
        }

        if (elem > elems[centro].valor) {
            return buscar(elem, (centro + 1), fin);
        }

        if (elem == elems[centro].valor && elems[centro].multiplicidad > 0) {
            return centro;
        }

        return centro;

    }

    struct Elem {
        int valor;
        int multiplicidad = 0;
    };
    Elem elems[MAX_ELEMS];
    int num_elems = 0;
};

bool tratar_caso() {
    // Implementar
    Multiconjunto m;
    int aux[MAX_ELEMS], aux2[MAX_ELEMS]; //aux primer array sin ordenar, aux2 segundo array sin ordenar
    int num;
    cin >> num;
    if (num != 0) {
        for (int i = 0; i < num; i++) {
            cin >> aux[i];;
            m.anyadir(aux[i]);
        }

        for (int i = 0; i < num; i++) {
            cin >> aux2[i];
        }

         for (int i = 0; i < num; i++) { //creo que el problema está por aqui
            if (aux2[i] == aux[i])
                m.eliminar(aux[i]); //no se si está eliminando bien
        } 

        for (int i = 0; i < num; i++) { //creo que el problema está por aqui
            if (aux2[i] == aux[i]) {
                     //no se si está eliminando bien
                cout << "#";//estoy
            }
            else if (m.pertenece(aux2[i])) {
                m.eliminar(aux2[i]);
                cout << "O";
            }
            else {
                cout << ".";
            }
        }
        cout << "\n";
    }
    else  return false;

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar en Windows si la consola se cierra inmediatamente
    // system("PAUSE");
#endif
    return 0;
}