#include "../inc/Perceptrons.hpp"
#include <iostream>

void test_step()
{
    bool bResult = false;
    for (int i = 0; i < 10; i++)
    {
        bResult = i >= 5 ? true : false;
        if (bResult != Perceptrons::StepFunction(i - 5)) {
            throw "error";
        }

        std::cout << bResult << "\n";
    }
}

void test_sigmoid()
{
    for (int i = -1; i <= 2; i++)
    {
        double dResult = Perceptrons::Sigmoid(i);
        std::cout << dResult << "\n";
    }
}

void test_relu()
{
    for (int i = -5; i <= 5; i++)
    {
        double dResult = i >= 0 ? i : 0;
        if (dResult != Perceptrons::Relu(i))
        {
            throw "error";
        }
    }
}


int main() {
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            std::cout << "And " << i << " " << j << ": " << Perceptrons::And<int>(i, j) << "\n";
            std::cout << "Nand " << i << " " << j << ": " << Perceptrons::Nand<int>(i, j) << "\n";
            std::cout << "Or  " << i << " " << j << ": " << Perceptrons::Or<int>(i, j) << "\n";
            std::cout << "Xor  " << i << " " << j << ": " << Perceptrons::Xor<int>(i, j) << "\n";
        }
    }
    test_step();
    test_sigmoid();
    test_relu();
    return 0;
}