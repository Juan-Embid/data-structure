/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no será corregida.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
   * Introduce el nombre y apellidos de los/as componentes del grupo:
   *
   * Estudiante 1: Alejandro Valencia Blancas
   * Estudiante 2: Juan Embid Sánchez
   *
   * Coste: O(n) donde n son los nodos de la segunda lista
   */
   //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>


class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }
    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) { }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head };
        head = new_node;
    }

    void push_back(const int& elem);

    void pop_front() {
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const int& front() const {
        assert(head != nullptr);
        return head->value;
    }

    int& front() {
        assert(head != nullptr);
        return head->value;
    }

    const int& back() const {
        return last_node()->value;
    }

    int& back() {
        return last_node()->value;
    }

    const int& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

    // Nuevo método. Debe implementarse abajo
    void escamochar(ListLinkedSingle& dest);

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const int& elem) {
    Node* new_node = new Node{ elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert(head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* previous = head;
        Node* current = head->next;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        delete current;
        previous->next = nullptr;
    }
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head != nullptr) {
        out << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

// ----------------------------------------------------------------
//@ <answer>

// Implementa a continuación el método pedido.

using namespace std;

//O(n) donde n son los nodos de la segunda lista
void ListLinkedSingle::escamochar(ListLinkedSingle& dest) {
    Node* aux = nullptr;
    Node* cur = head;
    Node* cur2 = nullptr;

    //conseguimos los primeros negativos en l2 y head en el primer positivo
    while (head != nullptr && head->value < 0) { //si empieza por numeros negativos
        if(dest.empty()) //inicializa el dest.head al primer negativo
            dest.head = head;
        cur2 = head;
        head = head->next;
        cur = head;
    }
    //cur2 -> next = nullptr;
    //encontramos el último positivo de l1
    if (head != nullptr && cur -> value >= 0) {
        while (cur != nullptr) {
            if (cur->value >= 0)
                aux = cur;
            cur = cur->next;
        }
    }

    if (aux != nullptr && aux -> next != nullptr) {
        if(dest.empty() && aux -> next != nullptr) //si l2 es vacio el siguiente nodo comenzará en aux->next
            dest.head = aux -> next;
        else //si no es vacio asignamos al siguiente de cur2 aux->next
            cur2 -> next = aux -> next;
        aux -> next = nullptr; //el siguiente de aux siempre va a tener que ser nullptr despues de quitarse los negativos
    }
    else { //si cur2 es distinto de nullptr
        if (!dest.empty()) {
            if (aux >= 0)
                cur2 -> next = nullptr;

            else
                cur2 = nullptr;
        }
    }
}

void tratar_caso() {
    // Implementar. Aquí se procesa cada caso de prueba
    ListLinkedSingle l1, l2;
    int temp, num;

    cin >> num;
    for (int i = 0; i < num; i++) {
        cin >> temp;
        l1.push_front(temp);
    }
    if (num != 0) //para que en los casos vacios no se meta en escamochar
        l1.escamochar(l2);
    l1.display();
    cout << "\n";
    l2.display();
    cout << "\n";
}


//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Leemos el número de casos de prueba que vendrán a continuación
    int num_casos;
    cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}