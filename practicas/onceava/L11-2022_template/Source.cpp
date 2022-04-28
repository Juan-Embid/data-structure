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
#include <map>
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
		try{
		if(mapnames.count(nombre) > 0)
			throw std::domain_error("Torre ya existente");
			if (map.count(x) > 0 && map.at(x).count(y) > 0)
			throw std::domain_error("Posicion ocupada");
		else {
				
				map[x][y] = nombre;
				mapy[y][x] = nombre;
				mapnames[nombre] ={x, y};
		}
		}
		catch (domain_error s) {
			cout << s.what() << endl;
		}
	}

	void eliminar_torre(const string& nombre) {
		unordered_map<int, int> aux2;
		try{
		if (mapnames.count(nombre) == 0)
			throw std::domain_error("torre no existente");
		else{
			map.at(mapnames[nombre].first).erase(mapnames[nombre].second);
			mapy.at(mapnames[nombre].second).erase(mapnames[nombre].first);
			mapnames.erase(nombre);
		}
		}
		catch (domain_error s) {
			cout << s.what();
		}
	}

	pair<bool, string> torre_en_posicion(int x, int y) const {
		pair<bool, string> result;
		if ( map.count(x) > 0 && map.at(x).count(y) > 0) {
			string m = map.at(x).at(y);
			result = { true, m };
		}
		else {
			result = { false, "" };
		}
		return result;
	}

	pair<int, int> posicion(const string& nombre) const {
		try{
		if (mapnames.count(nombre) == 0)
			throw std::domain_error("Torre no existente");
		
		
		else {
			return mapnames.at(nombre);
		}
		}
		catch (domain_error s) {
			cout << s.what()<<endl;
		}

		return { -1, -1 };
	}
	
	string torre_mas_cercana(const string& nombre, const Direccion& dir) const {
		string msg;
		bool ok = false;
		try{
		if (mapnames.count(nombre) > 0) {
			
			if (dir == Direccion::Norte) {
				
				auto it = map.at(mapnames.at(nombre).first).upper_bound(mapnames.at(nombre).second);
				if (it == map.at(mapnames.at(nombre).first).end()) {
					ok = false;
					}
				else {
					msg = it->second;
					ok = true;
				}
			}
				
			else if (dir == Direccion::Sur) {
				
				auto it = map.at(mapnames.at(nombre).first).lower_bound(mapnames.at(nombre).second);
				if (it == map.at(mapnames.at(nombre).first).begin()) {
					ok = false;
				}
				else {
					it--;
					msg = it->second;
					ok = true;
				}
				
			}
			
			else if (dir == Direccion::Este) {


				auto it = mapy.at(mapnames.at(nombre).second).upper_bound(mapnames.at(nombre).first);
				if (it == mapy.at(mapnames.at(nombre).second).end()) {
					ok = false;
				}
				else {
					msg = it->second;
					ok = true;
				}
				/*
				auto it = map.upper_bound(mapnames.at(nombre).first);
				while(it != map.end() && !ok){
				if (it == map.end() || it->second.count(mapnames.at(nombre).second) == 0) {
					ok = false;
				}
				else {
					msg = it->second.at(mapnames.at(nombre).second);
					ok = true;
				}
				}*/
			}
			else if (dir == Direccion::Oeste) {
				
				auto it = mapy.at(mapnames.at(nombre).second).lower_bound(mapnames.at(nombre).first);
				
				if (it == mapy.at(mapnames.at(nombre).second).begin()) {
					ok = false;
				}
				else {
					it--;
					msg = it->second;
					ok = true;
				}
				

				/*
				auto it = map.lower_bound(mapnames.at(nombre).first);
				while(it != map.begin() && !ok){
				it--;
				if (it == map.end() || it->second.count(mapnames.at(nombre).second) == 0) {
					ok = false;
				}
				else {
					msg = it->second.at(mapnames.at(nombre).second);
					ok = true;
				}
			}*/
			}
			if(!ok)
				throw std::domain_error("No hay torres en esa direccion");
		}
		else {
			throw std::domain_error("Torre no existente");
		}
		}
		catch (domain_error s) { msg = s.what(); }
		
		return msg;
	}


private:

	std::map<int, std::map<int ,string> > map;
	std::map<int, std::map<int, string> > mapy;
	unordered_map<string, pair<int,int>> mapnames;
	
	// Añade aquí los atributos que conforman la representación
	// interna del TAD
	//
	// También puedes añadir métodos auxiliares privados
	
};


// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado el
// fin de fichero
void parse(Desierto &d, string const order) {
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
		pair <int, int> temp = d.posicion(name);
		if(temp.first != -1 && temp.second != -1)
		cout << temp.first << " " << temp.second << endl;
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
		cout << d.torre_mas_cercana(name, dir) << endl;
		
	}

}
bool tratar_caso() {
	Desierto desert;
	string order;
	cin >> order;
	while(std::cin){
	
	if (order != "FIN") 
		parse(desert, order);
	else
		cout << "---" << endl;
	cin >> order;
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
	 system("PAUSE");
#endif
	return 0;
}

