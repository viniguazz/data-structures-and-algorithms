#include <iostream>
#include <cstdio>
#include <cmath>

struct City {
    int x;
    int y;
};

struct Node {
    City value;
    Node* next;
};

class LinkedList {

private:
    Node* head;
    unsigned int _size;

public:
    LinkedList();
    void push(City x);
    void swap(unsigned int pos);
    City getCity(unsigned int pos);
    Node* getNode(unsigned int pos);
    unsigned int size();
    void print();
    ~LinkedList();
};

LinkedList::LinkedList() {                       // O(1)
    head = nullptr;
    _size = 0;
}

void LinkedList::push(City x) {                  // O(n)

    Node* new_node = new Node();
    (*new_node).value = x;
    (*new_node).next = nullptr;
        
    if (_size == 0) {
        head = new_node;
        (*head).next = new_node;
    }
    else {
        Node* pivot = head;
        for (unsigned int i = 1; i < _size; i++) {
            pivot = (*pivot).next;
        }
        (*new_node).next = (*pivot).next;
        (*pivot).next = new_node;
    }
    _size++;
    
}

Node* LinkedList::getNode(unsigned int pos) {     // O(n)
    Node* pivot = head;
    for (unsigned int i = 0; i < pos; i++) {
        pivot = (*pivot).next;
    }
    return pivot;
}

void LinkedList::swap(unsigned int pos) {         // O(n)
    //pos = (_size - 1) + pos;
    Node* observer = getNode(pos);
    Node* a = (*observer).next;
    Node* b = (*(*observer).next).next;

    (*a).next = (*b).next;
    (*b).next = a;
    (*observer).next = b;

    if (head == a) {
        head = b;
    } else if (head == b)
    {
        head = a;
    }
}

void LinkedList::print() {   // O(n) 
    Node* pivot = head;
    for (unsigned int i = 0; i < _size; i++) {
        std::cout << "City: " << "x: " << (*pivot).value.x << " y: " << (*pivot).value.y << "\n";
        pivot = (*pivot).next;
    }
}

City LinkedList::getCity(unsigned int pos) {     // O(n)
    Node* pivot = head;
    for (unsigned int i = 0; i < pos; i++) {
        pivot = (*pivot).next;
    }
    return (*pivot).value;
}

LinkedList::~LinkedList() {                      // O(n)
    Node* to_delete = (*head).next;
    while(to_delete != head) {
        Node* aux = (*to_delete).next;
        delete to_delete;
        to_delete = aux;
    }
    delete head;
}

unsigned int LinkedList::size() {                // O(1)
    return _size;
}

float calc_route(LinkedList& city_list) {


    float sum = 0;

    for (unsigned int i = 0; i < city_list.size(); i++) {      // O(n^2)
        City city_a = city_list.getCity(i);
        City city_b = city_list.getCity(i+1);

        int x_axis = std::pow((city_a.x - city_b.x), 2.0);
        int y_axis = std::pow((city_a.y - city_b.y), 2.0);

        sum += std::sqrt((x_axis + y_axis));
    }

    return sum;

}


float cityDistance(City a, City b) {
        int x_axis = std::pow((a.x - b.x), 2.0);
        int y_axis = std::pow((a.y - b.y), 2.0);
        
        return std::sqrt((x_axis + y_axis));
    }

float tetraDistance(City a, City b, City c, City d) {

        return cityDistance(a, b) + cityDistance(b, c) + cityDistance(c, d) + cityDistance(d, a);
    }


bool improvedBySwap(LinkedList& city_list)  {

    float sum = 0;
    bool isImproved = false;
    float best;
    unsigned int list_size = city_list.size();


    for (unsigned int i = list_size -1; i < list_size * 2; i++) {      // O(n^2)


        Node* a = city_list.getNode(i);    // O(n)
        Node* b = (*a).next;               // O(1)
        Node* c = (*b).next;
        Node* d = (*c).next;

        City alpha = (*a).value;
        City beta = (*b).value;
        City gama = (*c).value;
        City delta = (*d).value;

        float original = tetraDistance(alpha, beta, gama, delta);
        float swaped = tetraDistance(alpha, gama, beta, delta);

        if (swaped < original) {
            city_list.swap(i);
            isImproved = true;
        }

    }

    return isImproved;

}


void cPrint(float value) {                       // O(1)
    std::printf("%.2f\n", value);
}


int main() {

    int x, y;
    std::cin >> x >> y;
    LinkedList city_list;
    
    while (x != -1) {

        City new_city;
        new_city.x = x;
        new_city.y = y;
        city_list.push(new_city);
        
        std::cin >> x >> y;
    }

    bool is_improve = true;
    float initial_route = calc_route(city_list);
    float best_route = initial_route;

    while(improvedBySwap(city_list)) {
        best_route = calc_route(city_list);
    }

    cPrint(initial_route);
    cPrint(best_route);

    return 0;
}
