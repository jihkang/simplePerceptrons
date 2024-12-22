#include "../inc/Perceptrons.hpp"
#include "../inc/Parallel.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

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
            std::cout << "Xor  " << i << " " << j << ": " << Perceptrons::Xor<int>(i, j) << "\n";
            std::cout << "And " << i << " " << j << ": " << Perceptrons::And<int>(i, j) << "\n";
            std::cout << "Nand " << i << " " << j << ": " << Perceptrons::Nand<int>(i, j) << "\n";
            std::cout << "Or  " << i << " " << j << ": " << Perceptrons::Or<int>(i, j) << "\n";
        }
    }
    test_step();
    test_sigmoid();
    test_relu();
    

    auto work = [&](int t) {
        for (int i = 0; i < 100; i++) {
            std::cout << t <<" : "<< i << "\n";
        }
    };
    std::vector<int> v(1000001);
    std::vector<int> v2(1000001);

    for (int i = 0; i <= 100000; i++) {
        v[i] = i + 1;
        v2[i] = i + 1;
    }
    auto start_0 = std::chrono::steady_clock::now();
    parallel_for0(0, 10000, [&](int i) {
        v[i] = std::pow(v[i], 2);
    });
    auto end_0 = std::chrono::steady_clock::now();
    auto diff_0 = end_0 - start_0;
    std::cout << "\nTime elapsed: "
            << std::chrono::duration<double, std::milli>(diff_0).count()
            << " ms" << "\n";
    auto start_1 = std::chrono::steady_clock::now();
    parallel_for(0, 10000, [&](int i) {
        v2[i] = std::pow(v2[i], 2);
    });
    auto end_1 = std::chrono::steady_clock::now();
    auto diff_1 = end_1 - start_1;
    std::cout << "\nTime elapsed: "
            << std::chrono::duration<double, std::milli>(diff_1).count()
            << " ms" << "\n";
    auto diff_2 = diff_1 - diff_0;
    std::cout << "\nTime elapsed: "
            << std::chrono::duration<double, std::milli>(diff_2).count()
            << " ms" << "\n";
    
    // for (int i = 0; i < 100; i++)
    // {
    //     std::cout << v[i] << ", ";
    //     std::cout << v2[i] << "\n";
    // }
    return 0;
}