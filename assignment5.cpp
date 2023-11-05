#include <vector>
#include <iostream>
#include <string>



int main() {

    unsigned int vector_size;
    unsigned int vector_ocp = 0;
    unsigned int instruction;
    std::string word;

    std::cin >> vector_size;
    std::vector<std::string> vector(vector_size, "-1");
    std::cin.ignore(1);
    std::cin >> instruction;

    while (instruction != -1) {
        std::cin >> word;
        unsigned int word_size = word.size();
        unsigned int hash = word_size % vector_size;

        switch (instruction)
        {
        case 0:
            if (vector_ocp == vector_size) {
                break;
            } else {
                for (unsigned int i = hash; i < vector_size + hash; i++) {
                    i = i % vector_size;
                    if (vector[i] == "-1" || vector[i] == "-2") {
                        vector[i] = word;
                        break;
                    }
                }
                vector_ocp += 1;
            }
            break;
        
        default:
            if (vector[hash] == word) {
                vector[hash] = "-2";
                vector_ocp -= 1;
            } else {
                for (unsigned int i = 0; i < vector.size(); i++) {
                    if (vector[i] == word) {
                        vector[i] = "-2";
                        vector_ocp -= 1;
                    } 
                }
            }
            break;
        }
        std::cin >> instruction;
    }

    for(unsigned int i = 0; i < vector.size(); i++) {
        std::cout << vector[i] << "\n";
    }

    return 0;
}