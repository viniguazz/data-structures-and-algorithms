#include <iostream>
#include <vector>
#include <cstdlib>

class MyVector {

private:
        unsigned int _size = 0;
        unsigned int capacity;
        int* vector_address;

public:
        MyVector();
        int find(int x);
        void insert(unsigned int pos);
        void remove(unsigned int pos);
        unsigned int size();
        void resize_array();
        void print();
        void clear();
        //void sort(std::string mode);
        //reverse();
        ~MyVector();

private:
        void resize_array();

};

MyVector::MyVector() {
    capacity = 10;
    vector_address = new int[capacity];
}

MyVector::size() {
    return _size;
}

int MyVector::find(int x) {
    if (size == 0) {
        return -1
    }
    for(unsigned int i = 0; i < size(); i++) {
        if(vector_address[i] == x) {
            return i;
        }
    }
    return -1;
}

void MyVector::print() {
    for(unsigned int i = 0; i < size(); i++) {
        std::cout << vector_address[i] << " ";
    }
    std::cout << '\n';
}

void MyVector::clear() {
    for(unsigned int i = 0; i < size(); i++) {
        vector_address[i] = 0;
    }
}

void MyVector::resize_array() {
    capacity *= 2;
    int* new_vector_address = new int[capacity];
    for(unsigned int i = 0; i < size(); i++) {
        new_vector_address[i] = vector_address[i];
    }
    delete [] vector_address;
    vector_address = new_vector_address;
}

void MyVector::insert(unsigned int pos) {

    if (size() == capacity) {
        resize_array();
    }

    for (unsigned int i = size(); i > pos; i--) {
        vector_address[i] = vector_address[i-1];
    }
    v[pos] = x;
    _size++;

}

void MyVector::remove(unsigned int pos) {

    if (pos > size()) {
        return;
    }

    for(unsigned int i = pos; i < size() - 1; i++) {
        vector_address[i] = vector_address[i + 1];
    }
    _size--;

}

MyVector::~MyVector() {
    delete [] vector_address;
}


int main() {

    

    return 0;
}