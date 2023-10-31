#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>

// Defines a square as a pair (row, col):
struct Square {
    unsigned row;
    unsigned col;

    Square() = default;

    Square(unsigned r, unsigned c) {
        row = r;
        col = c;
    }
};

class ChessBoard {
private:
    int board[8][8] = {
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1
    };
    unsigned int _sz = 8;
public:
    unsigned int size() const {
        return _sz;
    }

    int *operator[](unsigned i) {
        /* Enables the use of [] operator for ChessBoard objects */
        return board[i];
    }

};

std::ostream &operator<<(std::ostream &out, ChessBoard &board) {
    /* Enables the use of std::cout << board
     * to print the board.
     * May be used for debugging.
     */
    for (auto i = 0u; i < board.size(); ++i) {
        for (auto j = 0u; j < board.size(); ++j) {
            out << board[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

bool square_valid(const Square &s, const ChessBoard &board) {
    // Since weare using unsigned for the squares,there is no need to check
    // whether values are >=0.
    unsigned n = board.size();
    return (s.row < n && s.col < n);
}

unsigned get_knight_path_length ( const Square & origin , const Square & dest ) {

    ChessBoard play_board;

    play_board[origin.row][origin.col] = 0;

    std::cout << play_board;

    std::queue<Square> search_queue;
    search_queue.push(origin);

    while (!search_queue.empty()) {

        

        Square current = search_queue.front();

        std::cout << "front element:" << current.row << " " << current.col << "\n";

        int current_val = play_board[current.row][current.col];
        search_queue.pop();

        std::cout << "current: " << "r:" << current.row << " " << "c:" << current.col << "\n";


        Square move1 = Square(current.row - 2, current.col + 1);
        Square move2 = Square(current.row - 1, current.col + 2);
        Square move3 = Square(current.row + 1, current.col + 2);
        Square move4 = Square(current.row + 2, current.col + 1);
        Square move5 = Square(current.row + 2, current.col - 1);
        Square move6 = Square(current.row + 1, current.col - 2);
        Square move7 = Square(current.row - 1, current.col - 2);
        Square move8 = Square(current.row - 2, current.col - 1);

        std::cout << "move1" << " " << move1.row << " " << move1.col << "\n";
        std::cout << "move2" << " " << move2.row << " " << move2.col << "\n";
        std::cout << "move3" << " " << move3.row << " " << move3.col << "\n";
        std::cout << "move4" << " " << move4.row << " " << move4.col << "\n";
        std::cout << "move5" << " " << move5.row << " " << move5.col << "\n";
        std::cout << "move6" << " " << move6.row << " " << move6.col << "\n";
        std::cout << "move7" << " " << move7.row << " " << move7.col << "\n";
        std::cout << "move8" << " " << move8.row << " " << move8.col << "\n";
        

        std::vector<Square> moves = {move1, move2, move3, move4, move5, move6, move7, move8};
        std::vector<Square> valid_moves = {};

        for (Square square : moves) {
            if (square_valid(square, play_board)) {
                valid_moves.push_back(square);
                std::cout << "valid move: " << square.row << " " << square.col << "\n";
            }
        }

        std::cout << "VALID_VECTOR: ";
        for (unsigned int i; i < valid_moves.size(); i++) {
            auto element = valid_moves[i];
            std::cout << element.row << " " << element.col << "//";
        }
        std::cout << "\n";


        for (auto v_square : valid_moves) {

            if (play_board[v_square.row][v_square.col] == -1) {
                search_queue.push(v_square);
                play_board[v_square.row][v_square.col] = current_val + 1;
                std::cout << "atualizando: " << v_square.row << " " << v_square.col << "\n";

                

                if (v_square.row == dest.row && v_square.col == dest.col) {
                    return play_board[v_square.row][v_square.col];
                }
            }
        }
        std::cout << "\n";
        std::cout << play_board;
    }

    return -1;
}

int main() {
    //Used to map the squares as char to indices of the board
    std::unordered_map<char, unsigned> table = {
            {'a', 0},
            {'b', 1},
            {'c', 2},
            {'d', 3},
            {'e', 4},
            {'f', 5},
            {'g', 6},
            {'h', 7}
    };
    char icol, ocol;
    unsigned irow, orow;
    std::cin >> icol >> irow;
    std::cin.ignore(1);
    //Skip the '\n' char at the input;
    std::cin >> ocol >> orow;
    Square origin(irow - 1, table[icol]);
    Square dest(orow - 1, table[ocol]);
    unsigned nmoves = get_knight_path_length(origin, dest);
    std::cout << "Movimentos: " << nmoves << '\n';
    return 0;
}