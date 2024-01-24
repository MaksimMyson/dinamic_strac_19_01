#include "doublylinkedlist.h"

int main() {
    DoublyLinkedList<int> list1;
    list1.AddToTail(1);
    list1.AddToTail(2);
    list1.AddToTail(3);

    DoublyLinkedList<int> list2;
    list2.AddToTail(3);
    list2.AddToTail(4);
    list2.AddToTail(5);

    std::cout << "List 1: ";
    list1.Show();
    std::cout << "List 2: ";
    list2.Show();

    DoublyLinkedList<int> clonedList = list1.Clone();
    std::cout << "Cloned List: ";
    clonedList.Show();

    DoublyLinkedList<int> combinedList = list1 + list2;
    std::cout << "Combined List: ";
    combinedList.Show();

    DoublyLinkedList<int> commonElementsList = list1 * list2;
    std::cout << "Common Elements List: ";
    commonElementsList.Show();

    return 0;
}