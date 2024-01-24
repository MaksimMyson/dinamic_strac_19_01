#include <iostream>
#include "Array.h"

int main() {
    // �������� ������ ������ �� ��������� grow
    int size, grow;
    std::cout << "Enter the initial size of the array: ";
    std::cin >> size;
    std::cout << "Enter the growth parameter: ";
    std::cin >> grow;

    // ��������� ������
    Array<int> arr;
    arr.SetSize(size, grow);

    // ��������� �������� �� ������
    int value;
    std::cout << "Enter values to add to the array (enter -1 to stop): ";
    while (std::cin >> value && value != -1) {
        arr.Add(value);
    }

    // ��������� ������ �� �������� ������
    std::cout << "Array size: " << arr.GetSize() << std::endl;
    std::cout << "Array elements: ";
    for (int i = 0; i < arr.GetSize(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
