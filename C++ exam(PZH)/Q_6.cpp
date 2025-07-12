/*6. Create Student class that has private member variables for name, class, 
roll number, and marks. Include member functions to calculate the grade 
based on the marks and display the student's  information.*/

#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    std::string className;
    int rollNumber;
    float marks;

public:
    Student(const std::string& n, const std::string& cls, int roll, float m)
        : name(n), className(cls), rollNumber(roll), marks(m) {}

    char calculateGrade() const {
        if (marks >= 80)
            return 'A';
        else if (marks >= 60)
            return 'B';
        else if (marks >= 40)
            return 'C';
        else if (marks >= 20)
            return 'D';
        else
            return 'F';
    }

    void displayInfo() const {
        std::cout << "Student Name: " << name << std::endl;
        std::cout << "Class: " << className << std::endl;
        std::cout << "Roll Number: " << rollNumber << std::endl;
        std::cout << "Marks: " << marks << std::endl;
        std::cout << "Grade: " << calculateGrade() << std::endl;
    }
};

int main() {
    std::string name, className;
    int roll;
    float marks;

    std::cout << "Enter student name: ";
    std::getline(std::cin, name);

    std::cout << "Enter class: ";
    std::getline(std::cin, className);

    std::cout << "Enter roll number: ";
    std::cin >> roll;

    std::cout << "Enter marks: ";
    std::cin >> marks;

    Student student(name, className, roll, marks);

    std::cout << "\n--- Student Information ---\n";
    student.displayInfo();

    return 0;
}
