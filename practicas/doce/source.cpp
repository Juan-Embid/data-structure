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
#include <list>
#include <unordered_map>
#include <set>

using namespace std;


class Spitter {
public:
  
  Spitter() { }
  
  void nueva_publicacion(int id, const string & texto, const vector<string> &hashtags) { // O(n)
    if(pub.count(id)) // O(n)
        throw std::domain_error("Identificador duplicado");

    rec.push_front(texto); // O(1)
    pub.insert({id,{{texto,rec.begin()},{}}}); // O(1) 

    auto& has = pub[id].second;
    for(auto hashtag : hashtags) { // O(n)
        has.insert(hashtag);  // O(1)
        fam[hashtag]++;
    }
  }
  
  void borrar_publicacion(int id) { // O(n)
    if(pub.count(id)) {  // O(n)
        auto it = pub[id].first.second;
        rec.erase(it); // O(n)

        auto has = pub[id].second;
        for(auto hashtag : has)
            fam[hashtag]--;
        pub.erase(id); // O(1)
    }
  }

  
  vector<string> mas_recientes(int n) const { // O(n)
      auto it = rec.begin(); // O(1)
      vector<string> last;

      while(it != rec.end()) { // O(n)
          last.push_back(*it); // O(1)
          it++;
      }
      return last;
  }  

  vector<string> hashtags(int id) const { // O(n)
      if(pub.count(id) == 0) // O(n)
        throw std::domain_error("Publicacion no existente");

        auto has = pub.at(id).second;
        vector<string> has1;
        for(auto elem : has) // O(n)
            has1.push_back(elem); // O(1)

        return has1; 
  }
  
  void anyadir_hashtag(int id, const string &hashtag) { // O(n)
      if(pub.count(id) == 0) // O(n)
        throw std::domain_error("Publicacion no existente");
    
    auto& has = pub[id].second;
    if(has.count(hashtag) == 0) { // O(n)
        has.insert(hashtag);  // O(log n)
        fam[hashtag]++;
    }
  }
  
  int popularidad(const string &hashtag) const { // O(n)
      if(fam.count(hashtag))  // O(n)
        return fam.at(hashtag); // O(n)
    return 0;
  }
  
  
private:
  // Añade aquí los atributos que conforman la representación
  // interna del TAD
  //
  // También puedes añadir métodos auxiliares privados
    list<string> rec;
    unordered_map<int, pair<pair<string, list<string>::iterator>, set<string>>> pub;
    unordered_map<string, int> fam;
};


// Función para tratar un caso de prueba
// Devuelve true si se ha procesado el caso de prueba
// o false si no se ha procesado porque se ha encontrado el
// fin de fichero
bool tratar_caso() {
    Spitter spitter;
    string spits, operacion;
    int id;

    cin >> operacion;

    if (!cin) 
        return false; 

    while (operacion != "FIN") { // O((cantidad de hashtahs) * n)
        try {
            if (operacion == "nueva_publicacion") {
                vector<string> hashtags; 
                string palabra, total;
                        
                cin >> id;
                getline(cin, spits);
                getline(cin, total);

                stringstream strm(total);
                while (strm >> palabra) // O((cantidad de palabras)*n)
                    hashtags.push_back(palabra);
                spitter.nueva_publicacion(id, spits, hashtags); // O(n)
            }

            if (operacion == "borrar_publicacion") {
                cin >> id;
                spitter.borrar_publicacion(id); // O(n)
            }

            if (operacion == "mas_recientes") {
                int cantidad;
                vector<string> recientes;

                cin >> cantidad;
                recientes = spitter.mas_recientes(cantidad); // O(n)         
                cout << "Las " << recientes.size() << " publicaciones mas recientes:" << endl;
               
               for (string publicacion : recientes) 
                    cout << "  " << publicacion << endl;
            }
            
            if (operacion == "hashtags") {
                vector<string> hasht;
                int n = 1;

                cin >> id;
                hasht = spitter.hashtags(id); // O(n)
                if (hasht.size() != 0)
                    cout << hasht[0];
                while (hasht.size() > n) {
                    cout << " " << hasht[n];
                    n++;
                }
                cout << endl;
            }

            if (operacion == "anyadir_hashtag") {
                string hasht;

                cin >> id >> hasht;
                spitter.anyadir_hashtag(id, hasht); // O(n)
            }

            if (operacion == "popularidad") {
                string hasht;

                cin >> hasht;
                cout << spitter.popularidad(hasht) << endl; // O(n)
            }

        } catch (std::domain_error& exception) {
        cout << "ERROR: " << exception.what() << endl;
        }

        cin >> operacion;
    }

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
