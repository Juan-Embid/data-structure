/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */
 
/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>. Toda modificación fuera de esas etiquetas está
 * prohibida, pues no se tendrá en cuenta para la corrección.
 *
 * Tampoco esta permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */
 
//@ <answer>
/*
  Introduce aquí los nombres de los componentes del grupo:
  
  Componente 1:
  Componente 2:
*/
//@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>
#include <memory>
#include <utility>
#include <tuple>

template <class T> class BinTree {
public:
  BinTree() : root_node(nullptr) {}

  BinTree(const T &elem)
      : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

  BinTree(const BinTree &left, const T &elem, const BinTree &right)
      : root_node(std::make_shared<TreeNode>(left.root_node, elem, right.root_node)) {}

  bool empty() const { return root_node == nullptr; }

  const T &root() const {
    assert(root_node != nullptr);
    return root_node->elem;
  }

  BinTree left() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->left;
    return result;
  }

  BinTree right() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->right;
    return result;
  }

  void display(std::ostream &out) const { display_node(root_node, out); }

private:
  // Las definiciones de TreeNode y NodePointer dependen recursivamente
  // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
  // para que el compilador sepa, cuando analice la definición de NodePointer,
  // que TreeNode va a ser definida más adelante.

  struct TreeNode;
  using NodePointer = std::shared_ptr<TreeNode>;

  struct TreeNode {
    TreeNode(const NodePointer &left, const T &elem, const NodePointer &right)
        : elem(elem), left(left), right(right) {}

    T elem;
    NodePointer left, right;
  };

  NodePointer root_node;

  static void display_node(const NodePointer &root, std::ostream &out) {
    if (root == nullptr) {
      out << ".";
    } else {
      out << "(";
      display_node(root->left, out);
      out << " " << root->elem << " ";
      display_node(root->right, out);
      out << ")";
    }
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const BinTree<T> &tree) {
  tree.display(out);
  return out;
}

template <typename T> BinTree<T> read_tree(std::istream &in) {
  char c;
  in >> c;
  if (c == '.') {
    return BinTree<T>();
  } else {
    assert(c == '(');
    BinTree<T> left = read_tree<T>(in);
    T elem;
    in >> elem;
    BinTree<T> right = read_tree<T>(in);
    in >> c;
    assert(c == ')');
    BinTree<T> result(left, elem, right);
    return result;
  }
}

using namespace std;

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------



// No olvides el coste!
template <typename T>
bool estable_altura(const BinTree<T> &arbol) { //O(n) para el número de nodos del árbol
  // Implementa aquí la función. No puedes modificar el tipo
  // de entrada ni de salida. No obstante, puedes apoyarte en
  // funciones auxiliares con el tipo que quieras.
  return altura(arbol).second;
}

template <typename T>
//primera componente la altura
//segunda componente un booleano que devuelve si es estable o no
pair<int, bool> altura(const BinTree<T> &arbol) { //O(n_iz) + O(n_der) + K_empty + K_hojas = O(n) donde n es el número de nodos
  if(arbol.empty()) // si está vacio su altura será 0 y si será estable en altura
    return {0, true};
  else if(arbol.left().empty() && arbol.right().empty()) // si es una hoja tendrá altura 1 y no será estable en altura
    return {1, false};
  else {
    auto [altura_iz, bool_iz] = altura(arbol.left());
    auto [altura_der, bool_der]= altura(arbol.right());
    int alt = 1 + std::max(altura_iz, altura_der);  
    if (altura_der == altura_iz) //significa que si hay dos alturas iguales será estable en altura para esa altura
      return{alt, true};
    else if(altura_der < altura_iz)
      return{altura_iz + 1, bool_iz};
    else 
      return{altura_der + 1, bool_der};
  }
}

// Función para tratar un caso de prueba
void tratar_caso() {
  BinTree<int> t = read_tree<int>(cin);
  cout << (estable_altura(t) ? "SI" : "NO") << "\n";
}


//---------------------------------------------------------------
// No modificar por debajo de esta línea
// --------------------------------------------------------------
//@ </answer>


int main() {
#ifndef DOMJUDGE
  std::ifstream in("sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  int num_casos;
  cin >> num_casos;
  
  for (int i = 0; i < num_casos; i++) {
    tratar_caso();
  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}

