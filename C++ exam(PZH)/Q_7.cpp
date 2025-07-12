/*7. Write a template function in C++ that takes two values of any data type 
and returns the maximum of the two. Also, demonstrate its usage with 
different data types in the main function.*/

#include <iostream>
#include <string>

template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    int int1 , int2 = 25;
    float float1, float2;
    char char1, char2;
    std::string str1, str2;


    std::cout << "Eneter interger1:";
    std::cin >> int1;
    std::cout << "Eneter interger2:";
    std::cin >> int2;
    
    std::cout << "Max of " << int1 << " and " << int2 << " is " << getMax(int1, int2) << std::endl;

    std::cout << "Eneter float1:";
    std::cin >> float1;
    std::cout << "Eneter float2:";
    std::cin >> float2;

    std::cout << "Max of " << float1 << " and " << float2 << " is " << getMax(float1, float2) << std::endl;

    std::cout << "Eneter character1:";
    std::cin >> char1;
    std::cout << "Eneter character2:";
    std::cin >> char2;

    std::cout << "Max of '" << char1 << "' and '" << char2 << "' is '" << getMax(char1, char2) << "'" << std::endl;

    std::cout << "Eneter string1:";
    std::cin >> str1;
    std::cout << "Eneter string2:";
    std::cin >> str2;

    std::cout << "Max of \"" << str1 << "\" and \"" << str2 << "\" is \"" << getMax(str1, str2) << "\"" << std::endl;

    return 0;
}
