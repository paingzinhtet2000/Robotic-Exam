/*Create an enum for seasons of myanmar? Ask users to choose a season 
and make output of the months of season. */

#include <iostream>
#include <string>

enum MyanmarSeason {
    SUMMER = 1,
    RAINY,
    WINTER
};

void showSeasonMonths(MyanmarSeason season) {
    switch (season) {
        case SUMMER:
            std::cout << "Summer Months: March, April, May" << std::endl;
            break;
        case RAINY:
            std::cout << "Rainy Season Months: June, July, August, September, October" << std::endl;
            break;
        case WINTER:
            std::cout << "Winter Months: November, December, January, February" << std::endl;
            break;
        default:
            std::cout << "Invalid season selected!" << std::endl;
            break;
    }
}

int main() {
    int choice;

    std::cout << "Choose a season of Myanmar:\n";
    std::cout << "1. Summer\n";
    std::cout << "2. Rainy\n";
    std::cout << "3. Winter\n";
    std::cout << "Enter your choice (1-3): ";
    std::cin >> choice;

    MyanmarSeason selectedSeason = static_cast<MyanmarSeason>(choice);
    showSeasonMonths(selectedSeason);

    return 0;
}
