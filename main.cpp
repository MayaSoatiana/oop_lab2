#include <iostream>
#include<BitString.h>
#include<string.h>

int main(){
    std::cout << "=== Лабораторная работа 2: Класс BtString ===" << std::endl;
    
    // === ДЕМОНСТРАЦИЯ РАЗЛИЧНЫХ КОНСТРУКТОРОВ ===
    
    std::cout << "\n--- Создание объектов с помощью различных конструкторов ---" << std::endl;
    
    BitString firstArray{'1', '0', '1', '0', '1'};
    std::cout << "Первый массив: ";
    firstArray.print();

    BitString secondArray{'1', '1', '0'};
    std::cout << "Второй массив: ";
    secondArray.print();

    // === ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ ===
    
    std::cout << "\n--- Операции с массивами ---" << std::endl;
    
    BitString thirdArray(firstArray.andOperation(secondArray));
    std::cout << "Результат &: ";
    thirdArray.print();

    // === ДЕМОНСТРАЦИЯ ПЕРЕМЕЩАЮЩЕГО КОНСТРУКТОРА ===
    
    std::cout << "\n--- Перемещающий конструктор ---" << std::endl;
    
    BitString fourthArray(std::move(thirdArray));
    std::cout << "Четвертый массив (после перемещения): ";
    fourthArray.print();
    
    BitString tempArray(BitString{'1', '1', '4', '2'});

    // === ДЕМОНСТРАЦИЯ ОБРАБОТКИ ИСКЛЮЧЕНИЙ ===
    
    std::cout << "\n--- Обработка исключений ---" << std::endl;

    try {
        // Успешное вычитание
        BitString fifthArray = fourthArray.orOperation(secondArray);
        std::cout << "Результат вычитания (успешно): ";
        fifthArray.print();

        // Попытка вычитания, которое приведет к исключению
        BitString temp("1042");

    } catch (std::exception& exception) {
        std::cerr << "Перехвачено исключение: " << exception.what() << std::endl;
    }

    std::cout << "\n--- Выход из main() - вызов деструкторов ---" << std::endl;
    
    // Деструкторы вызываются в обратном порядке создания:
    // tempArray → fourthArray → secondArray → firstArray
    
    std::cout << "\n=== Лабораторная работа завершена ===" << std::endl;
    return 0;
}