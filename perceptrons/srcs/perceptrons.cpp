#include "../inc/Perceptrons.hpp"
#include <iostream>

int main() {
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            std::cout << "And " << i << " " << j << ": " << Perceptrons::And<int>(i, j) << "\n";
            std::cout << "Nand " << i << " " << j << ": " << Perceptrons::Nand<int>(i, j) << "\n";
            std::cout << "Or  " << i << " " << j << ": " << Perceptrons::Or<int>(i, j) << "\n";
            std::cout << "Xor  " << i << " " << j << ": " << Perceptrons::Xor<int>(i, j) << "\n";
        }
    }

    return 0;
}