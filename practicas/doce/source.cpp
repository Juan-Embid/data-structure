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
#include <sstream>
#include <vector>


using namespace std;


class Spitter {
public:
  
  Spitter() { }
  
  void nueva_publicacion(int id, const string & texto, const vector<string> &hashtags) {
  }
  
  void borrar_publicacion(int id) {
  }

  
  vector<string> mas_recientes(int n) const {
  }  

  vector<string> hashtags(int id) const {
  }
  
  void anyadir_hashtag(int id, const string &hashtag) {
  }
  
  int popularidad(const string &hashtag) const {
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

while (tratar_caso()) {
    Spitter spitter;
    string spits, operacion;
    int id;

    cin >> operacion;

    if (!cin) 
        return false; 

    while (operacion != "FIN") {
        try {
            if (operacion == "nueva_publicacion") {
                vector<string> hashtags; 
                string palabra, total;
                        
                cin >> id;
                getline(cin, spits);
                getline(cin, total);

                stringstream strm(total);
                while (strm >> palabra) 
                    hashtags.push_back(palabra);
                spitter.nueva_publicacion(id, spits, hashtags);
            }

            if (operacion == "borrar_publicacion") {
                cin >> id;
                spitter.borrar_publicacion(id);
            }

            if (operacion == "mas_recientes") {
                int cantidad;
                vector<string> recientes;

                cin >> cantidad;
                recientes = spitter.mas_recientes(cantidad);                
                cout << "Las " << recientes.size() << " publicaciones mas recientes:" << endl;
               
               for (string publicacion : recientes) 
                    cout << publicacion << endl;
            }
            
            if (operacion == "hashtags") {
                vector<string> hasht;

                cin >> id;
                hasht = spitter.hashtags(id);
                for (string tag : hasht) 
                    cout << tag << " ";
                cout << endl;
            }

            if (operacion == "anyadir_hashtag") {
                string hasht;

                cin >> id >> hasht;
                spitter.anyadir_hashtag(id, hasht);
            }

            if (operacion == "popularidad") {
                string hasht;

                cin >> hasht;
                cout << spitter.popularidad(hasht) << endl;
            }

        } catch (std::domain_error& exception) {
        cout << "ERROR: " << exception.what() << endl;
        }

        cin >> operacion;
    }

    cout << "---" << endl;
    return true;
}

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}
