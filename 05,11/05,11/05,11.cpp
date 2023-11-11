#include <iostream>
#include <string>

enum Type { Bird, Animal, Human };

union Characteristic {
    double flight_speed;
    bool hooves;
    int IQ_level;
};

struct LivingEntity {
    double movement_speed;
    Type type;
    std::string color;
    Characteristic characteristics;
};

void inputInformation(LivingEntity& entity) {
    std::cout << "Enter movement speed: ";
    std::cin >> entity.movement_speed;
    std::cout << "Enter type (0 - Bird, 1 - Animal, 2 - Human): ";
    int type;
    std::cin >> type;
    entity.type = static_cast<Type>(type);
    std::cout << "Enter color: ";
    std::cin.ignore();
    std::getline(std::cin, entity.color);

    if (entity.type == Bird) {
        std::cout << "Enter flight speed: ";
        std::cin >> entity.characteristics.flight_speed;
    } else if (entity.type == Animal) {
        std::cout << "Is it hooved? (1 - Yes, 0 - No): ";
        std::cin >> entity.characteristics.hooves;
    } else if (entity.type == Human) {
        std::cout << "Enter IQ level: ";
        std::cin >> entity.characteristics.IQ_level;
    }
}

void printInformation(const LivingEntity& entity) {
    std::cout << "Movement speed: " << entity.movement_speed << std::endl;
    std::cout << "Type: ";
    if (entity.type == Bird) {
        std::cout << "Bird" << std::endl;
        std::cout << "Flight speed: " << entity.characteristics.flight_speed << std::endl;
    } else if (entity.type == Animal) {
        std::cout << "Animal" << std::endl;
        std::cout << "Hooves: " << (entity.characteristics.hooves ? "Yes" : "No") << std::endl;
    } else if (entity.type == Human) {
        std::cout << "Human" << std::endl;
        std::cout << "IQ level: " << entity.characteristics.IQ_level << std::endl;
    }
    std::cout << "Color: " << entity.color << std::endl;
}

void editData(LivingEntity& entity) {
    inputInformation(entity);
}

void printList(const LivingEntity* list, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << "Living Entity #" << i + 1 << ":" << std::endl;
        printInformation(list[i]);
        std::cout << std::endl;
    }
}

void searchByCharacteristic(const LivingEntity* list, int size, double value) {
    for (int i = 0; i < size; i++) {
        if (list[i].type == Bird && list[i].characteristics.flight_speed == value) {
            std::cout << "Found: Bird with flight speed " << value << std::endl;
            printInformation(list[i]);
            std::cout << std::endl;
        } else if (list[i].type == Animal && list[i].characteristics.hooves == static_cast<bool>(value)) {
            std::cout << "Found: Animal with hooves = " << (value ? "Yes" : "No") << std::endl;
            printInformation(list[i]);
            std::cout << std::endl;
        } else if (list[i].type == Human && list[i].characteristics.IQ_level == static_cast<int>(value)) {
            std::cout << "Found: Human with IQ level " << value << std::endl;
            printInformation(list[i]);
            std::cout << std::endl;
        }
    }
}

int main() {
    const int listSize = 10;
    LivingEntity list[listSize];

    for (int i = 0; i < listSize; i++) {
        inputInformation(list[i]);
    }

    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Edit data" << std::endl;
        std::cout << "2. Print entire list" << std::endl;
        std::cout << "3. Search by characteristic" << std::endl;
        std::cout << "4. Exit" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            int index;
            std::cout << "Enter the index of the living entity to edit: ";
            std::cin >> index;
            if (index >= 1 && index <= listSize) {
                editData(list[index - 1]);
            } else {
                std::cout << "Invalid index." << std::endl;
            }
        } else if (choice == 2) {
            printList(list, listSize);
        } else if (choice == 3) {
            int type;
            std::cout << "Enter type for searching (0 - Bird, 1 - Animal, 2 - Human): ";
            std::cin >> type;
            if (type >= 0 && type <= 2) {
                double value;
                if (type == 0) {
                    std::cout << "Enter flight speed to search: ";
                } else if (type == 1) {
                    std::cout << "Enter hooves (1 - Yes, 0 - No) to search: ";
                } else if (type == 2) {
                    std::cout << "Enter IQ level to search: ";
                }
                std::cin >> value;
                searchByCharacteristic(list, listSize, value);
            } else {
                std << "Invalid type." << std::endl;
            }
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    }

    return 0;
}
