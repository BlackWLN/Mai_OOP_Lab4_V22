#include <iostream>
#include <memory>
#include <limits>
#include "../include/array.hpp"
#include "../include/pentagon.hpp"
#include "../include/hexagon.hpp"
#include "../include/octagon.hpp"


template<Scalar T>
void showMenu() {
    std::cout << "\n=== Figure Management System ===" << std::endl;
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Add Pentagon" << std::endl;
    std::cout << "2. Add Hexagon" << std::endl;
    std::cout << "3. Add Octagon" << std::endl;
    std::cout << "4. Print All Figures" << std::endl;
    std::cout << "5. Calculate Total Area" << std::endl;
    std::cout << "6. Remove Figure" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

template<Scalar T>
int mainWithType() {
    Array<std::shared_ptr<Figure<T>>> figures;
    
    int choice;
    
    while (true) {
        showMenu<T>();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        try {
            switch (choice) {
                case 1: {
                    std::cout << "Enter Pentagon data (center x, center y, radius): ";
                    auto pentagon = std::make_shared<Pentagon<T>>();
                    pentagon->read(std::cin);
                    figures.add(pentagon);
                    std::cout << "Pentagon added." << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Enter Hexagon data (center x, center y, radius): ";
                    auto hexagon = std::make_shared<Hexagon<T>>();
                    hexagon->read(std::cin);
                    figures.add(hexagon);
                    std::cout << "Hexagon added." << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Enter Octagon data (center x, center y, radius): ";
                    auto octagon = std::make_shared<Octagon<T>>();
                    octagon->read(std::cin);
                    figures.add(octagon);
                    std::cout << "Octagon added." << std::endl;
                    break;
                }
                case 4: {
                    if (figures.size() == 0) {
                        std::cout << "No figures to print." << std::endl;
                    } else {
                        std::cout << "All figures:" << std::endl;
                        figures.printAll();
                    }
                    break;
                }
                case 5: {
                    if (figures.size() == 0) {
                        std::cout << "Figure list is empty." << std::endl;
                    } else {
                        std::cout << "Total area of all figures: " << figures.totalArea() << std::endl;
                    }
                    break;
                }
                case 6: {
                    if (figures.size() == 0) {
                        std::cout << "No figures to remove." << std::endl;
                        break;
                    }
                    std::cout << "All figures:" << std::endl;
                    figures.printAll();
                    std::cout << "Enter index to remove: ";
                    int index;
                    if (std::cin >> index) {
                        figures.remove(index);
                        std::cout << "Figure removed." << std::endl;
                    }
                    break;
                }
                case 7: {
                    std::cout << "Exiting program." << std::endl;
                    return 0;
                }
                default: {
                    std::cout << "Invalid choice." << std::endl;
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    return 0;
}

int main() {
    std::cout << "Select data type:" << std::endl;
    std::cout << "1. int" << std::endl;
    std::cout << "2. float" << std::endl;
    std::cout << "3. double" << std::endl;
    std::cout << "4. long double" << std::endl;
    std::cout << "Enter number: ";
    
    int typeChoice;
    std::cin >> typeChoice;
    
    switch (typeChoice) {
        case 1:
            return mainWithType<int>();
        case 2:
            return mainWithType<float>();
        case 3:
            return mainWithType<double>();
        case 4:
            return mainWithType<long double>();
        default:
            std::cout << "Invalid choice, using double." << std::endl;
            return mainWithType<double>();
    }
}