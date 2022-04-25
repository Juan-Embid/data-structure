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

   No te olvides del coste de las operaciones
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
#include <utility>
#include <stdexcept>
#include <unordered_map>

using namespace std;

const int MAX = 10000;
// Tipo de datos para representar direcciones
// Para hacer referencia a los elementos de este tipo enumerado se utiliza:
//   Direccion::Norte, Direccion::Sur, etc.
enum class Direccion { Norte, Sur, Este, Oeste };

// Operador para leer una dirección desde un flujo de entrada.
// Ejemplo de uso:
//
// Direccion dir;
// cin >> dir;
//
istream& operator>>(istream& is, Direccion& dir) {
	string palabra; is >> palabra;
	if (palabra == "Norte") dir = Direccion::Norte;
	else if (palabra == "Sur") dir = Direccion::Sur;
	else if (palabra == "Este") dir = Direccion::Este;
	else if (palabra == "Oeste") dir = Direccion::Oeste;
	else throw std::domain_error("Lectura de direccion incorrecta");
	return is;
}

class Desierto {
public:

	Desierto() { }

	void anyadir_torre(const string& nombre, int x, int y) {
		pair<int, int> aux;
		aux = { x, y };
		
		auto it = mapnames.find(nombre);
		if(it != mapnames.end())
			throw std::domain_error("Torre ya existente");
		auto it2 = map.find(aux);
		if (it2 != map.end())
			throw std::domain_error("Posicion ocupada");
		else {
			map.insert(pair<pair<int, int>, string>(aux, nombre));
			mapnames.insert(pair<string, pair<int, int>>(nombre, aux));
		}
		
	}

	void eliminar_torre(const string& nombre) {
		auto it = mapnames.find("nombre");
		if (it == mapnames.end())
			throw std::domain_error("Torre no existente");
		else{
			pair<int, int> aux =  mapnames["nombres"];
			map.erase(aux);
			mapnames.erase("nombre");
		}
	}

	pair<bool, string> torre_en_posicion(int x, int y) const {
		pair<bool, string> result;
		pair <int, int> aux = { x,y };
		auto it2 = map.find(aux);
		if (it2 != map.end()) {
			string m = map.at(pair<int, int>(aux));
			result = { true, m };
		}
		else {
			result = { false, "" };
		}
		return result;
	}

	pair<int, int> posicion(const string& nombre) const {
		pair<int, int> m;
		auto it = mapnames.find(nombre);
		if (it == mapnames.end())
			throw std::domain_error("Torre no existente");
		else
			return mapnames.at(nombre);
	}

	string torre_mas_cercana(const string& nombre, const Direccion& dir) const {
		pair<int, int> aux;
		auto it = mapnames.find(nombre);
		bool ok = false;
		if (it != mapnames.end()) {
			switch (dir)
			{
			case Direccion::Norte:
				
					for(int i = mapnames.at(nombre).first && !ok; i < MAX; i++){
						aux = { i, mapnames.at(nombre).second };
						auto it2 = map.find(pair<int, int>(aux));
						if (it2 != map.end()) {
							ok = true;
						}
					}
				
				break;
			case Direccion::Sur:
				
					for (int i = mapnames.at(nombre).first && !ok; i > 0; i--) {
						aux = { i, mapnames.at(nombre).second };
						auto it2 = map.find(pair<int, int>(aux));
						if (it2 != map.end()) {
							ok = true;
						}
				}
				break;
			case Direccion::Este:
				
					for (int i = mapnames.at(nombre).second && !ok;i < MAX; i++) {
						aux = { mapnames.at(nombre).first ,i };
						auto it2 = map.find(pair<int, int>(aux));
						if (it2 != map.end()) {
							ok = true;
						}
					}
				
				break;
			case Direccion::Oeste:
				
					for (int i = mapnames.at(nombre).second && !ok; i > 0; i--) {
						aux = { mapnames.at(nombre).first ,i};
						auto it2 = map.find(pair<int, int>(aux));
						if (it2 != map.end()) {
							ok = true;
						}
					}
				
				break;
			}
		}
		else {
			throw std::domain_error("No hay torres en esa direccion");
		}

		return map.at(aux);
	}


private:

	unordered_map<pair<int, int>,string > map;
	unordered_map<string, pair<int, int> > mapnames;
	// Añade aquí los atributos que conforman la representación
	// interna del TAD
	//
	// También puedes añadir métodos auxiliares privados
	
};


// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado el
// fin de fichero
void parse(Desierto d, string const order) {
	string name;
	int x, y;
	Direccion dir;
	
	if (order == "anyadir_torre") {
		cin >> name;
		cin >> x;
		cin >> y;
		d.anyadir_torre(name, x, y);

	}
	else if (order == "eliminar_torre") {
		cin >> name;
		d.eliminar_torre(name);
	}
	else if (order == "posicion") {
		cin >> name;
		d.posicion(name);
	}
	else if (order == "torre_en_posicion") {
		cin >> x;
		cin >> y;
		pair<bool, string> final = d.torre_en_posicion(x, y);
		if (!final.first)
			cout << "NO" << endl;
		else
			cout << "SI" << " " << final.second<<endl;
	}
	else if (order == "torre_mas_cercana") {
		cin >> name;
		cin >> dir;
		
	}

}
bool tratar_caso() {
	string order;
	if (std::cin)
		return false;
	cin >> order;
	if (order != "FIN") {
		Desierto ok;
		parse(ok, order);
	}
	else
		cout << "---" << endl;
	
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
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}

