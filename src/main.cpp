#include <iostream>

#include "Queen.h"

int main() {

    Queen queen(Color::WHITE);

    std::cout << std::boolalpha;

    std::cout << "Queen (4,4) -> (4,7): "
              << queen.isValidMovement(
                    Position{4,4},
                    Position{4,7}
                 )
              << std::endl;

    std::cout << "Queen (4,4) -> (7,4): "
              << queen.isValidMovement(
                    Position{4,4},
                    Position{7,4}
                 )
              << std::endl;

    std::cout << "Queen (4,4) -> (7,7): "
              << queen.isValidMovement(
                    Position{4,4},
                    Position{7,7}
                 )
              << std::endl;

    std::cout << "Queen (4,4) -> (6,5): "
              << queen.isValidMovement(
                    Position{4,4},
                    Position{6,5}
                 )
              << std::endl;

    std::cout << "Queen (4,4) -> (4,4): "
              << queen.isValidMovement(
                    Position{4,4},
                    Position{4,4}
                 )
              << std::endl;

    return 0;
}