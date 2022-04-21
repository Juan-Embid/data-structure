/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
   Utiliza las librerías de la STL en esta práctica.

   No te olvides del coste.
 */

 /*
   Introduce aquí los nombres de los componentes del grupo:

   Componente 1: Alejandro Valencia Blancas
   Componente 2: Juan Embid Sánchez
 */



 // Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;

// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado la
// marca de fin de entrada

bool tratar_caso() {
	multimap<string, string> map;
	unordered_map<string,  int> invmap;
	int players, ships, shots;
	string name, coord, attackname, attack;
	std::map<string, string>::iterator it;
	bool ok = false;
	cin >> players;
	cin >> ships;
	
	for (int j = 0; j < players; j++) {
		cin >> name;
		invmap[name] = ships;
		for (int i = 0; i < ships; i++) {
			cin >> coord;
			map.insert(coord, name);
		}
	}
	cin >> shots;
	it = map.find(coord);
	for (int i = 0; i < shots; i++) {
		cin >> attackname;
		cin >> attack;
		auto range = map.equal_range(attack);
		for (auto i = range.first; i != range.second; ++i) {
			ok = true;
			if (i->second != attackname) {
				auto it2 = invmap.find(i->second);
				int temp = it2->second;
				it->second = temp - 1;
				map.erase(i);
				if (it2->second > 0)
					cout << "HUNDIDO" << endl;
				else cout << "VENCIDO" << endl;
			}
		}
		if (!ok) cout << "AGUA" << endl;
	}	
		return false;
}


int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}

