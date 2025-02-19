#include <iostream>

int main() {
    int num1, num2, sum;

    // Taking input from the user
    std::cout << "Enter first number: ";
    std::cin >> num1;
    
    std::cout << "Enter second number: ";
    std::cin >> num2;

    // Calculating sum
    sum = num1 + num2;

    // Displaying the result
    std::cout << "Sum: " << sum << std::endl;

    return 0;
}

