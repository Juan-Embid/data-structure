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
  
  Componente 1:
  Componente 2:
*/


// Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>


using namespace std;

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
istream & operator>>(istream &is, Direccion &dir) {
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
  
  void anyadir_torre(const string &nombre, int x, int y) {
  }
  
  void eliminar_torre(const string &nombre) {
  }
  
  pair<bool, string> torre_en_posicion(int x, int y) const {
  }

  pair<int, int> posicion(const string &nombre) const {
  }
  
  string torre_mas_cercana(const string &nombre, const Direccion &dir) const {
  }


private:
  // Añade aquí los atributos que conforman la representación
  // interna del TAD
  //
  // También puedes añadir métodos auxiliares privados
};


// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado el
// fin de fichero
bool tratar_caso() {
  // Implementar.
}


int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}

