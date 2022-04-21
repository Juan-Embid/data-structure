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
  
  Componente 1:
  Componente 2:
*/



// Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>


using namespace std;

// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado la
// marca de fin de entrada
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

