#include <iostream>
#include <string>

class Node {

private:
Node* parent;
Node* left_node;
Node* right_node;
std::string content;

public:
Node* get_parent() {
    return parent;
}

Node* get_left_node() {
    return left_node;
}

Node* get_right_node() {
    return right_node;
}

std::string get_content() {
    return content;
}

void set_parent(Node* par) {
    parent = par;
}

void set_left_node(Node* left) {
    left_node = left;
}

void set_right_node(Node* right) {
    right_node = right;
}

void set_content(std::string cont) {
    content = cont;
}

Node() {
    parent = nullptr;
    left_node = nullptr;
    right_node = nullptr;
    content = "root";
}
};

class BinaryTree {

private:
Node* root;

public:
BinaryTree() {
    root = new Node();
}

Node* get_root() {
    return root;
}

Node* insert_right(std::string cont, Node* parent) {
    Node* new_node = new Node();
    (*new_node).set_content(cont);
    (*new_node).set_parent(parent);
    (*parent).set_right_node(new_node);
    return new_node;
}

Node* insert_left(std::string cont, Node* parent) {
    Node* new_node = new Node();
    (*new_node).set_content(cont);
    (*new_node).set_parent(parent);
    (*parent).set_left_node(new_node);
    return new_node;
}
};

void mount_tree_recursive(std::string expression, BinaryTree& tree, Node* parent) {

    //debug
    //std::cout << "executing mount function... expression: " << expression << "\n";

    if (expression.size() == 1) {
        if (((*parent).get_left_node()) == nullptr){
            tree.insert_left(expression, parent);
        } else {
            tree.insert_right(expression, parent);
        }

        //debug
        //std::cout << "inserted leaf: " << expression << "\n";
        //std::cout << "parent content: " << parent->get_content() << "\n";

        return; 
    }

    for (int i = expression.size() - 1; i >=0; i--) {
        if (expression[i] == '+' || expression[i] == '-') {
            Node* prnt;
            std::string exp{expression[i]};

            //debug
            //std::cout << exp << " found at position " << i << "\n";
            //std::cout << "parent content: " << parent->get_content() << "\n";

            if  ((*parent).get_left_node() == nullptr) {
                prnt = tree.insert_left(exp, parent);
            } else {
                prnt = tree.insert_right(exp, parent);
            }
            mount_tree_recursive(expression.substr(0,i), tree, prnt);
            mount_tree_recursive(expression.substr(i+1), tree, prnt);
            return;
        }
    }
    for (int i = expression.size() - 1; i >=0; i--) {
        if (expression[i] == '*' || expression[i] == '/') {
            Node* prnt;
            std::string exp{expression[i]};

            //debug
            //std::cout << exp << " found at position " << i << "\n";
            //std::cout << "parent content: " << parent->get_content() << "\n";

            if  ((*parent).get_left_node() == nullptr) {
                prnt = tree.insert_left(exp, parent);
            } else {
                prnt = tree.insert_right(exp, parent);
            }
            mount_tree_recursive(expression.substr(0,i), tree, prnt);
            mount_tree_recursive(expression.substr(i+1), tree, prnt);
            return;
        }
    }
}

std::string pre_order(Node* current) {
    
    //debug
    //std::cout << "Running pre_order()..." << "\n";
    //std::cout << "current node value: " << (*current).get_content() << "\n";

    Node* root = current;
    if ((*root).get_left_node() == nullptr) {
        std::string ret_expression = (*root).get_content();
        return ret_expression;
    }

    std::string ret_expression;
    ret_expression += (*root).get_content();

    if((*root).get_left_node() != nullptr){
        ret_expression += pre_order((*root).get_left_node());
    }
    if ((*root).get_right_node() != nullptr) {
        ret_expression += pre_order((*root).get_right_node());
    }

    //debug
    //std::cout << "ret_exp: " << ret_expression << "\n";

    return ret_expression;
}

std::string post_order(Node* current) {

    //debug
    //std::cout << "Running post_order()..." << "\n";

    Node* root = current;
    if ((*root).get_left_node() == nullptr) {
        return (*root).get_content();
    }

    std::string ret_expression;

    if((*root).get_left_node() != nullptr){
        ret_expression += post_order((*root).get_left_node());
    }
    if ((*root).get_right_node() != nullptr) {
        ret_expression += post_order((*root).get_right_node());
    }

    ret_expression += (*root).get_content();

    return ret_expression;
}

int main() {

    std::string expression;
    std::string pre_order_exp;
    std::string post_order_exp;

    //input
    std::cin >> expression;

    //debug
    //std::cout << "expression submited: " << expression << "\n";

    BinaryTree tree = BinaryTree();
    mount_tree_recursive(expression, tree, tree.get_root());

    //debug
    //std::cout << "root content: " << tree.get_root()->get_content() << "\n";
    //std::cout << "root left child: " << tree.get_root()->get_left_node()->get_content() << "\n";
    //std::cout << "#############\n";


    pre_order_exp = pre_order(((*(tree.get_root())).get_left_node()));

    //debug
    //std::cout << "### pre_order concluded" << "\n";

    post_order_exp = post_order(((*(tree.get_root())).get_left_node()));

    std::cout << pre_order_exp << "\n";
    std::cout << post_order_exp;

    return 0;
}