#include <fstream>
#include <iostream>
#include <string>

// Function to calculate factorial
int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// Simple class example
class Rectangle {
   private:
    double width, height;

   public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() { return width * height; }
    double perimeter() { return 2 * (width + height); }
};

int main() {
    // Basic output
    std::cout << "Welcome to C++ Program!\n";

    // Variables and input
    int age;
    std::cout << "Enter your age: ";
    std::cin >> age;
    std::cout << "You are " << age << " years old.\n";

    // Conditional statement
    if (age >= 18) {
        std::cout << "You are an adult.\n";
    } else {
        std::cout << "You are a minor.\n";
    }

    // Loop example
    std::cout << "Counting to 5: ";
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // Function call
    int num = 5;
    std::cout << "Factorial of " << num << " is " << factorial(num) << "\n";

    // Class usage
    Rectangle rect(3.0, 4.0);
    std::cout << "Rectangle area: " << rect.area() << "\n";
    std::cout << "Rectangle perimeter: " << rect.perimeter() << "\n";

    // Array example
    int numbers[] = {10, 20, 30, 40, 50};
    std::cout << "Array elements: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // File I/O example
    std::ofstream outFile("example.txt");
    if (outFile.is_open()) {
        outFile << "This is a test file.\n";
        outFile << "Created by C++ program.\n";
        outFile.close();
        std::cout << "File written successfully.\n";
    }

    // String operations
    std::string greeting = "Hello, World!";
    std::cout << "String length: " << greeting.length() << "\n";
    std::cout << "First character: " << greeting[0] << "\n";

    // End of program
    std::cout << "Program completed successfully!\n";
    return 0;
}
