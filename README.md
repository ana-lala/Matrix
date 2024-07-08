# Algebraic Matrix in C++

## Description
This project implements a C++ class to manipulate algebraic matrices and perform various matrix operations, including:

- Matrix addition and subtraction
- Matrix multiplication and scalar multiplication
- Determinant calculation
- Inverse matrix calculation
- Cofactor matrix calculation
- Matrix transposition
- Matrix resizing

The `Matriz` class is designed to handle matrices of type `long double`.

## Usage
Here is an example of how to use the `Matriz` class:

```cpp
#include <iostream>
#include "Matriz.hpp"

int main() {
    try {
        Matriz v(3, 3), w(3, 3);

        std::cin >> v;
        std::cin >> w;

        Matriz sum = v + w;
        Matriz diff = v - w;
        Matriz product = v * w;
        Matriz scalarProduct = 2.5 * v;
        Matriz inverse = v.Inversa();
        Matriz transpose = v.Transpuesta();

        // Print the results of the operations
        std::cout << sum << std::endl;
        std::cout << diff << std::endl;
        std::cout << product << std::endl;
        std::cout << scalarProduct << std::endl;
        std::cout << inverse << std::endl;
        std::cout << transpose << std::endl;
    } catch (const char *msg) {
        std::cerr << "Error: " << msg << std::endl;
    } catch (...) {
        std::cerr << "Unexpected error" << std::endl;
    }

    return 0;
}
