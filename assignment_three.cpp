#include <iostream>
#include <vector>

struct LandBlock {
    unsigned int i;
    unsigned int j;
};

class Node {

private:

    LandBlock coordinates;
    Node* next;

public:
    Node();
    LandBlock get_value();
    void set_value(LandBlock coordinates);
    Node* get_next();
    void set_next(Node* next);
    ~Node();
    
};

Node::Node() {
    next = nullptr;
}

LandBlock Node::get_value() {
    return coordinates;
}

void Node::set_value(LandBlock val) {
    coordinates = val;
};

Node* Node::get_next() {
    return next;
}

void Node::set_next(Node* element) {
    next = element;
}

Node::~Node() = default;


class Stack {

private:

    Node* head;
    unsigned int _size;


public:

    Stack();
    unsigned int size();
    void push(LandBlock coordinates);
    void pop();
    LandBlock top();
    bool is_empty();
    void print();
    ~Stack();

};

Stack::Stack() {
    head = new Node();
    (*head).set_next(nullptr);
    _size = 0;
}

unsigned int Stack::size() {
    return _size;
}

bool Stack::is_empty() {
    if (_size == 0) {
        return true;
    } else {
        return false;
    }
}

void Stack::push(LandBlock coordinates) {

    Node* new_node = new Node();
    (*new_node).set_value(coordinates);
    (*new_node).set_next((*head).get_next());
    (*head).set_next(new_node);
    _size++;
}

void Stack::pop() {
    if (_size != 0) {
        Node* to_pop = (*head).get_next();
        Node* to_top = (*to_pop).get_next();
        (*head).set_next(to_top);
        delete to_pop;
        _size--;
    }
}

LandBlock Stack::top() {
    Node* top_element = (*head).get_next();
    return (*top_element).get_value();
}

void Stack::print() {
    
    Node* pivot = (*head).get_next();
    for (unsigned int i = 0; i < _size; i++) {
        std::cout << "Element " << i << ": " << (*pivot).get_value().i << " " << (*pivot).get_value().j << "\n";
        pivot = (*pivot).get_next();
    }
}

Stack::~Stack() {
    Node* pivot = head;
    for (unsigned int i = 0; i < _size; i++) {
        Node* next = (*pivot).get_next();
        delete pivot;
        pivot = next;
    }
    delete head;
}

// --------------- main program functions ------------------------------------------------------

void read_input(std::vector<std::vector<char>>& matrix) {
    std::string line;
    while (std::cin >> line) {
        std::vector<char> aux (line.cbegin(), line.cend());
        matrix.push_back (aux);
    }
}

LandBlock generate_block(unsigned int i, unsigned int j) {
    LandBlock generated;
    generated.i = i;
    generated.j = j;
    return generated;
}

std::vector<LandBlock> search_neighbors(std::vector<std::vector<char>>& matrix, LandBlock pivot_block) {

    std::vector<LandBlock> land_neighbors;
    LandBlock current_block = pivot_block;

    unsigned int block_i = current_block.i;
    unsigned int block_j = current_block.j;

    if (block_i > 0) {
        LandBlock top = generate_block(block_i - 1, block_j);
        if (matrix[top.i][top.j] == '1') {
            matrix[top.i][top.j] = '8';
            land_neighbors.push_back(top);
        }
    }

    if (block_i < matrix.size() - 1) {
        LandBlock down = generate_block(block_i + 1, block_j);
        if (matrix[down.i][down.j] == '1') {
            matrix[down.i][down.j] = '8';
            land_neighbors.push_back(down);
        }
    }

    if (block_j > 0) {
        LandBlock left = generate_block(block_i, block_j - 1);
        if (matrix[left.i][left.j] == '1') {
            matrix[left.i][left.j] = '8';
            land_neighbors.push_back(left);
        }
    }

    if (block_j < matrix[block_i].size() - 1) {
        LandBlock right = generate_block(block_i, block_j + 1);
        if (matrix[right.i][right.j] == '1') {
            matrix[right.i][right.j] = '8';
            land_neighbors.push_back(right);
        }
    }

    return land_neighbors;
    }

// ------------------------------------------------------------------------------------------


int main() {

    std::vector<std::vector<char>> matrix;
    Stack size_stack;
    unsigned int greatest = 0;

    read_input(matrix);

    //for (unsigned int i = 0; i < matrix.size(); i++){
    //    for (unsigned int j = 0; j < matrix[i].size(); j++) {
    //        std::cout << matrix[i][j];
    //    }
    //    std::cout << "\n";
    //}

// If you're inputting from the console (like pressing keys on your keyboard), you need to signify the end of input. On many systems, you can do this by pressing Ctrl + D (on UNIX-like systems) or Ctrl + Z followed by Enter (on Windows systems). This sends an EOF (end-of-file) signal to std::cin, which will make the while loop terminate
    
    for (unsigned int i = 0; i < matrix.size(); i++) {

        for (unsigned int j = 0; j < matrix[i].size(); j++) {
            
            if (matrix[i][j] == '1') {
                
                matrix[i][j] = '8';
                
                LandBlock current_block;
                current_block.i = i;
                current_block.j = j;

                size_stack.push(current_block);

                unsigned int counter = 0;

                //for(unsigned int a = 0; a < matrix.size(); a++) {
                //    for (unsigned int b = 0; b < matrix[i].size(); b++) {
                //        std::cout << matrix[a][b];
                //    }
                //    std::cout << "\n";
                //}

                while(!size_stack.is_empty()) {

                    //for(unsigned int c = 0; c < matrix.size(); c++) {
                    //    for (unsigned int d = 0; d < matrix[i].size(); d++) {
                    //        std::cout << matrix[c][d];
                    //    }
                    //    std::cout << "\n";
                    //}

                    LandBlock top_block = size_stack.top();
                    size_stack.pop();
                    matrix[top_block.i][top_block.j] = '8';
                    counter++;
                    std::vector<LandBlock> current_neighbors = search_neighbors(matrix, top_block);

                    for(unsigned int i = 0; i < current_neighbors.size(); i++) {
                        size_stack.push(current_neighbors[i]);
                    }
                }

                if (counter > greatest) {
                    greatest = counter;
                }

            }
        }
    }

    std::cout << greatest;


    return 0;

}