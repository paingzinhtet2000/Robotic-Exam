/*. Write an overloaded function to compare two numbers. The function 
should work for both integers and floats, returning true if the numbers 
are equal and false otherwise.*/

#include <iostream>
#include <cmath>

bool compare(int a, int b) {
    return a == b;
}

bool compare(float a, float b) {
    const float epsilon = 0.0001f;
    return std::fabs(a - b) < epsilon;
}

int main() {
    int int1, int2;
    float float1, float2;

    std::cout << "Type first integer: ";
    std::cin >> int1;

    std::cout << "Type second integer: ";
    std::cin >> int2;

    std::cout << "Type first float: ";
    std::cin >> float1;

    std::cout << "Type second float: ";
    std::cin >> float2;

    std::cout << "Are integers equal? " << (compare(int1, int2) ? "Yes" : "No") << std::endl;
    std::cout << "Are floats equal? " << (compare(float1, float2) ? "Yes" : "No") << std::endl;

    return 0;
}
