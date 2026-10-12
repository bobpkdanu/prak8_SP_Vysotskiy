#include <iostream>
#include <cstring>
using namespace std;

struct Route
{
    int number;
    char destination[50];
    int travelTime;
};

struct Node
{
    Route data;
    Node* next;
    Node* prev;
};

class RouteList
{
private:
    Node* head;
    Node* tail;

public:
    RouteList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void pushFront(Route route)
    {
        Node* newN = new Node;
        newN->data = route;
        newN->next = head;
        newN->prev = nullptr;

        if (head != nullptr)
        {
            head->prev = newN;
        }
        else
        {
            tail = newN;
        }

        head = newN;
    }

    void pushBack(Route route)
    {
        Node* newN = new Node;
        newN->data = route;
        newN->next = nullptr;
        newN->prev = tail;

        if (tail != nullptr)
        {
            tail->next = newN;
        }
        else
        {
            head = newN;
        }

        tail = newN;
    }

    void popFront()
    {
        if (head == nullptr)
        {
            cout << "Список пуст" << endl;
            return;
        }

        Node* temp = head;
        head = head->next;

        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;
        }

        delete temp;

        cout << "Первый маршрут удалён" << endl;
    }

    void popBack()
    {
        if (tail == nullptr)
        {
            cout << "Список пуст" << endl;
            return;
        }

        Node* temp = tail;
        tail = tail->prev;

        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }

        delete temp;

        cout << "Последний маршрут удалён" << endl;
    }

    void displayFrwrd()
    {
        if (head == nullptr)
        {
            cout << "Список пуст" << endl;
            return;
        }

        Node* current = head;

        cout << "Маршруты от начала к концу:" << endl;

        while (current != nullptr)
        {
            cout << "Номер: " << current->data.number << ", пункт назначения: " << current->data.destination
                << ", время поездки: " << current->data.travelTime << " мин." << endl;

            current = current->next;
        }
    }

    void displayBckwrd()
    {
        if (tail == nullptr)
        {
            cout << "Список пуст" << endl;
            return;
        }

        Node* current = tail;

        cout << "Маршруты от конца к началу:" << endl;

        while (current != nullptr)
        {
            cout << "Номер: " << current->data.number << ", пункт назначения: "
                << current->data.destination << ", время поездки: " << current->data.travelTime << " мин.";

            current = current->prev;
        }
    }

    Node* find(int number)
    {
        Node* current = head;

        while (current != nullptr)
        {
            if (current->data.number == number)
            {
                return current;
            }

            current = current->next;
        }

        return nullptr;
    }

    void remove(int number)
    {
        Node* current = find(number);

        if (current == nullptr)
        {
            cout << "Маршрут с таким номером не найден" << endl;
            return;
        }

        if (current == head)
        {
            popFront();
            return;
        }

        if (current == tail)
        {
            popBack();
            return;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;

        cout << "Маршрут удалён" << endl;
    }

    void findMinTime()
    {
        if (head == nullptr)
        {
            cout << "Список пуст" << endl;
            return;
        }

        Node* minNode = head;
        Node* current = head->next;

        while (current != nullptr)
        {
            if (current->data.travelTime < minNode->data.travelTime)
            {
                minNode = current;
            }

            current = current->next;
        }

        cout << "Маршрут с минимальным временем поездки: " << endl;
        cout << "Номер: " << minNode->data.number << endl;
        cout << "Пункт назначения: " << minNode->data.destination << endl;
        cout << "Время поездки: " << minNode->data.travelTime << " мин." << endl;
    }

    void removeLong(int time)
    {
        Node* current = head;
        int count = 0;

        while (current != nullptr)
        {
            Node* nextNode = current->next;

            if (current->data.travelTime > time)
            {
                if (current == head)
                {
                    popFront();
                }
                else if (current == tail)
                {
                    popBack();
                }
                else
                {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                }

                count++;
            }

            current = nextNode;
        }

        cout << "Удалено маршрутов: " << count << endl;
    }

    void insert(int number, Route route)
    {
        Node* current = find(number);

        if (current == nullptr)
        {
            cout << "Маршрут с таким номером не найден" << endl;
            return;
        }

        if (current == tail)
        {
            pushBack(route);
            return;
        }

        Node* newN = new Node;
        newN->data = route;
        newN->prev = current;
        newN->next = current->next;
        current->next->prev = newN;
        current->next = newN;
        cout << "Новый маршрут добавлен" << endl;
    }

    void clear()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        tail = nullptr;
    }

    ~RouteList()
    {
        clear();
    }
};

Route inputRoute()
{
    Route route;

    cout << "Введите номер маршрута: ";
    cin >> route.number;

    cin.ignore();

    cout << "Введите пункт назначения: ";
    cin.getline(route.destination, 50);

    cout << "Введите время поездки (мин): ";
    cin >> route.travelTime;

    return route;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    RouteList list;
    int choice;
    do
    {
        cout << "Выберите действие: " << endl;
        cout << "1. Добавить маршрут в начало" << endl;
        cout << "2. Добавить маршрут в конец" << endl;
        cout << "3. Удалить первый маршрут" << endl;
        cout << "4. Удалить последний маршрут" << endl;
        cout << "5. Вывести список" << endl;
        cout << "6. Вывести список в обратном порядке" << endl;
        cout << "7. Найти маршрут" << endl;
        cout << "8. Удалить найденный маршрут" << endl;
        cout << "9. Найти маршрут с минимальным временем" << endl;
        cout << "10. Удалить маршруты, время которых больше заданного" << endl;
        cout << "11. Вставить маршрут после указанного номера" << endl;
        cout << "12. Очистить список" << endl;
        cout << "0. Выход" << endl;

        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Route route = inputRoute();
            list.pushFront(route);
            cout << "Маршрут добавлен в начало" << endl;
            break;
        }

        case 2:
        {
            Route route = inputRoute();
            list.pushBack(route);
            cout << "Маршрут добавлен в конец" << endl;
            break;
        }

        case 3:
            list.popFront();
            break;

        case 4:
            list.popBack();
            break;

        case 5:
            list.displayFrwrd();
            break;

        case 6:
            list.displayBckwrd();
            break;

        case 7:
        {
            int number;
            cout << "Введите номер маршрута: ";
            cin >> number;
            Node* found = list.find(number);
            if (found != nullptr)
            {
                cout << "Номер: " << found->data.number << endl;
                cout << "Пункт назначения: " << found->data.destination << endl;
                cout << "Время поездки: "<< found->data.travelTime << " мин";
            }
            else
            {
                cout << "Маршрут не найден" << endl;
            }
            break;
        }

        case 8:
        {
            int number;
            cout << "Введите номер маршрута для удаления: ";
            cin >> number;
            list.remove(number);
            break;
        }

        case 9:
            list.findMinTime();
            break;

        case 10:
        {
            int time;
            cout << "Введите максимальное время: ";
            cin >> time;
            list.removeLong(time);
            break;
        }

        case 11:
        {
            int number;
            cout << "Введите номер маршрута после которого создастся новый:  ";
            cin >> number;
            Route route = inputRoute();
            list.insert(number, route);
            break;
        }

        case 12:
            list.clear();
            cout << "Очищено" << endl;
            break;

        case 0:
            cout << "Пока" << endl;
            break;

        default:
            cout << "Это мы ещё посмотрим";
        }

    } while (choice != 0);

    return 0;
}