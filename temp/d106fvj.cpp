#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20; // Default values if input fails
    cout << "Enter two numbers: ";
    
    if (!(cin >> a >> b)) { // Check if input is valid
        cout << "Invalid input! Using default values.\n";
    }

    cout << "Sum: " << (a + b) << endl;
    return 0;
}
