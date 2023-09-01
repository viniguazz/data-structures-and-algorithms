#include <iostream>
#include <vector>

// 1) Contains the structure (struct) of the items that will be allocated inside the backpack;

    struct item {
        int id;
        int utility;
        int weight;
        int quantity;
        float ratio;
    };


// 2.1) Subroutine responsible for setting the vector items' ratio

void set_item_vector_ratio(std::vector<item>& v) {

    for(int i = 0; i < v.size(); i++) {
        item& current_element = v[i];
        current_element.ratio = static_cast<float>(current_element.utility) / current_element.weight;
    }
}

// 2.2) Subroutine responsible for ordering the vector in descending order of utility ratio;

void order_by_ratio(std::vector<item>& v) {

    int i;
    int j;
    int v_size = v.size();
    int last_shift;
    int wall = v_size;

    for(i = 0; i < v_size; i++) {
        last_shift = 0;
        for(j = 1; j < wall; j++) {
            if(v[j - 1].ratio < v[j].ratio) {
                auto aux = v[j - 1];
                v[j - 1] = v[j];
                v[j] = aux;
                last_shift = j;
            }
        }
        wall = last_shift;
    }
}

// 2.3) Subroutine responsible for printing the ID and quantity of the items allocated inside the backpack;

void print_allocated_items(std::vector<item>& v, int backpack_capacity) {
    int v_size = v.size();
    int i;
    int j;

    for(int i = 0; i < v_size; i++) {
        int id = v[i].id;
        int allocated_quantity = 0;
        while(((backpack_capacity - v[i].weight) >= 0) && (v[i].quantity > 0)) {
            allocated_quantity++;
            v[i].quantity--;
            backpack_capacity = backpack_capacity - v[i].weight;
        }
        if(allocated_quantity > 0) {
            std::cout << id << " " << allocated_quantity << "\n";
        }
        // std::cout << "Space left: " << backpack_capacity << "\n";
    }
}


// 3) driver code (entry point);

int main() {

    std::vector<item> v;
    unsigned int id = 0;

    while(true) {

        item temp_item;
        std::cin >> temp_item.utility >> temp_item.weight >> temp_item.quantity;
        if(temp_item.utility == -1 && temp_item.weight == -1 && temp_item.quantity == -1) {
            break;
        }
        temp_item.id = id++;
        v.push_back(temp_item);
    }

    int backpack_capacity;
    std::cin >> backpack_capacity;

    set_item_vector_ratio(v);
    order_by_ratio(v);
    print_allocated_items(v, backpack_capacity);

    return 0;
}