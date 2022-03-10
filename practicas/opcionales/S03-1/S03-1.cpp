/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 *
 *  Componente: Juan Embid Sánchez
 */

#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

class ListLinkedDouble {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    void push_back(const int& elem) {
        Node* new_node = new Node{ elem, head, head->prev };
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    const int& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    int& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const int& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    int& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }

    void swap2by2();


private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
    static void attach(Node* node, Node* before);
    static void detach(Node* node);
}; 

ListLinkedDouble::Node* ListLinkedDouble::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedDouble::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

void ListLinkedDouble::attach(Node* node, Node* before) { //O(1)
    node-> next = before -> next;
    before -> next = node;
    node -> prev = before;
    node -> next -> prev = node;
}

void ListLinkedDouble::detach(Node* node) { //O(1)
    node -> prev -> next = node -> next;
    node -> next -> prev = node -> prev;
    node = nullptr;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble& other) {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

void ListLinkedDouble::display(std::ostream& out) const {
    out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
    l.display(out);
    return out;
}

//@ <answer>
//---------------------------------------------------------------
// Modificar a partir de aquí
// --------------------------------------------------------------

// No olvides el coste!
void ListLinkedDouble::swap2by2() { //O(n) --> O(2n) En el peor caso recorremos la lista hasta el último nodo (si nos dan el índice del último nodo) y luego lo colocamos en el primer lugar de la lista.
    Node *cur = head->next;

    while(cur->next != head) { //y que cur != head
        detach(cur);
        cur->prev = cur->next;
        cur->next = cur->next->next;
        attach(cur, cur->prev);
        cur->prev = cur->next;
        cur->next = cur->next->next;
        //cur->next=head;
    }
    
    /* cur = nth_node(index);
    cur->value += val; */
    
    /* detach(cur);

    while(!encontrado) {
        //hacia delante
        if (cur->next->value < cur->value && cur->next != head) {
            cur->prev = cur->next;
            cur->next = cur->next->next;
        }
        
        //hacia atras
        else if (cur -> prev -> value > cur -> value && cur->prev != head) {
            cur -> next = cur -> prev;
            cur -> prev = cur -> prev -> prev;
        }

        //no hace nada
        else {
            encontrado = true;
            attach(cur, cur->prev);
        } */

    display();
    cout << "\n";
}

bool tratar_caso() {
    ListLinkedDouble l1;
    int length, value;

    cin >> length;
    for (int i = 0; i < length; i++) {
        cin >> value;
        l1.push_back(value);
    }

    if (length == 0)
        return false;
   
    l1.swap2by2();

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
#endif
    return 0;
}