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

	Componente 1: Alejandro Valencia Blancas
	Componente 2: Juan Embid Sánchez
  */
  //@ </answer>



// Puedes copiar aquí algunas de las implementaciones de los TADs vistos esta semana:

// Pilas: https://github.com/manuelmontenegro/ED/blob/main/lineales/stack_linkedlist/stack_linkedlist.h
// Colas: https://github.com/manuelmontenegro/ED/blob/main/lineales/queue_linkedlist/queue_linkedlist.h
// Colas dobles: https://github.com/manuelmontenegro/ED/blob/main/lineales/deque/dequeue.h

// En caso de utilizar alguno de los TADs anteriores, ha de copiarse TAL CUAL, sin realizar ningún cambio
// en sus implementaciones. Para facilitar la corrección, coloca la implementación de estos TADs fuera
// de las etiquetas <answer> y </answer>. El profesor asumirá que tienen la misma implementación que la
// vista en teoría.

// Alternativamente, puedes utilizar las clases de la librería estándar de C++ (stack<T>, queue<T> y deque<T>).
/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Implementación del TAD Doble Cola utilizando una lista
  * doblemente enlazada con nodo fantasma.
  */

#ifndef __QUEUE_LINKEDLIST_H
#define __QUEUE_LINKEDLIST_H

#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T> class QueueLinkedList {
public:
  QueueLinkedList() : front_node(nullptr), back_node(nullptr) {}
  QueueLinkedList(const QueueLinkedList &other) {
    copy_nodes_from(other.front_node);
  }

  ~QueueLinkedList() { free_nodes_from(front_node); }

  QueueLinkedList &operator=(const QueueLinkedList &other) {
    if (this != &other) {
      free_nodes_from(front_node);
      copy_nodes_from(other.front_node);
    }
    return *this;
  }

  void push(const T &elem) {
    Node *new_node = new Node{elem, nullptr};
    if (back_node == nullptr) {
      back_node = new_node;
      front_node = new_node;
    } else {
      back_node->next = new_node;
      back_node = new_node;
    }
  }

  void pop() {
    assert(front_node != nullptr);
    Node *target = front_node;
    front_node = front_node->next;
    if (back_node == target) {
      back_node = nullptr;
    }
    delete target;
  }

  T &front() {
    assert(front_node != nullptr);
    return front_node->value;
  }

  const T &front() const {
    assert(front_node != nullptr);
    return front_node->elem;
  }

  bool empty() const { return (front_node == nullptr); }

private:
  struct Node {
    T value;
    Node *next;
  };

  void copy_nodes_from(Node *other);
  void free_nodes_from(Node *other);

  Node *front_node;
  Node *back_node;
};

template <typename T> void QueueLinkedList<T>::copy_nodes_from(Node *other) {
  if (other == nullptr) {
    front_node = nullptr;
    back_node = nullptr;
  } else {
    front_node = new Node{other->value, nullptr};
    back_node = front_node;
    Node *current = other->next;
    while (current != nullptr) {
      Node *new_node = new Node{current->value, nullptr};
      back_node->next = new_node;
      current = current->next;
      back_node = new_node;
    }
  }
}

template <typename T> void QueueLinkedList<T>::free_nodes_from(Node *other) {
  Node *current = other;
  while (current != nullptr) {
    Node *next = current->next;
    delete current;
    current = next;
  }
}

#endif

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------

//O(max(children, time)) Lineal respecto al mayor de los tres
int fungus_calculator(int fungus, int bud, int hours) {
    QueueLinkedList<int> adults, children;
    int time = 0, cont = 1;
    
    //anadimos tantos nodos con el valor 0 como horas - 1 tarde en reproducirse
    for (int i = 0; i < fungus - 1; i++) 
        adults.push(0);

    //anadimos un nodo con valor 1 en la posicion 4 (5) indicando que hay un adulto con 5 horas restantes
    adults.push(1);

    //anadimos tantos nodos con el valor 0 como horas tarde en reproducirse
    for (int i = 0; i < bud - fungus; i++)
        children.push(0);

    while (time < hours) { //o menor que el valor del primer elemento
        adults.push(adults.front() + children.front()); //Si hay algún niño que se vaya a conventir en adulto o algún adulto que se vaya a reproducir
        children.push(adults.front()); //Si hay algún adulto que se vaya a reproducir
        cont += adults.front(); // se suma 1 cuando se reproduce un adulto
        adults.pop(); // se va moviendo la lista
        children.pop();
        time++;
    }
    return cont;
}

// Indica el coste en función de los parámetros del problema (N, M, T)
bool tratar_caso() {
	// Introduce aquí el código para tratar un caso de prueba.
	// Devuelve false si ya no hay más casos de prueba que leer,
	// true en caso contrario.
	//0 < N < M < 1500
	//0 ≤ T ≤ 3000
    int fungus, bud, hours;

    cin >> fungus;
    cin >> bud;
    cin >> hours;

    if (!cin)
        return false;

    cout << fungus_calculator(fungus, bud, hours) << endl;

    return true;
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

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	 system("PAUSE");
#endif
	return 0;
}

