/*3. {4,6,39,73, 2,5 ,7} find min and max value of that array? ** Using return 
type function. ** Using minmax_element.*/

#include <iostream>
#include <algorithm>  
#include <vector>

std::pair<int, int> findMinMax(std::vector<int> arr) {
    auto result = std::minmax_element(arr.begin(), arr.end());
    return std::make_pair(*result.first, *result.second);
}

int main() {
    std::vector<int> numbers = {4, 6, 39, 73, 2, 5, 7};

    std::pair<int, int> minMax = findMinMax(numbers);

    std::cout << "Minimum value: " << minMax.first << std::endl;
    std::cout << "Maximum value: " << minMax.second << std::endl;

    return 0;
}
