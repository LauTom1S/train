#include <iostream>
#include <string>
#include <locale>
#include <fcntl.h>
#include <io.h>
#include <regex>
#include <limits>
using namespace std;
/**
* @brief MASTER ветка
*
*/




/**
 * @brief Структура, описывающая студента и сведения о его участии в мероприятии.
 *
 * Содержит ФИО студента, номер группы, название мероприятия и дату его проведения.
 */
struct studentsMASH {
    wstring nameSurname; ///< ФИО студента.
    wstring group;       ///< Номер группы.
    wstring event;       ///< Название мероприятия.
    wstring eventDate;   ///< Дата проведения мероприятия.
};

/**
 * @brief Определяет критерий поиска по введённой строке.
 *
 * Функция преобразует текстовое название критерия или его числовой код
 * в целочисленный идентификатор критерия поиска.
 *
 * @param a Тип: wstring. Введённое пользователем значение критерия поиска.
 * Допустимые значения: L"ФИО", L"1", L"Номер группы", L"2",
 * L"Мероприятие", L"3", L"Дата проведения", L"4", L"0".
 *
 * @return Тип: int. Код критерия поиска.
 * Возможные значения:
 * - 1 — поиск по ФИО;
 * - 2 — поиск по номеру группы;
 * - 3 — поиск по мероприятию;
 * - 4 — поиск по дате проведения;
 * - 0 — выход;
 * - -1 — критерий не распознан.
 */
int takeCriterion(const wstring a) {
    if (a == L"ФИО" or a == L"1") { return 1; }
    else if (a == L"Номер группы" or a == L"2") { return 2; }
    else if (a == L"Мероприятие" or a == L"3") { return 3; }
    else if (a == L"Дата проведения" or a == L"4") { return 4; }
    else if (a == L"0") { return 0; }
    else { return -1; }
}


template<typename T>
class List
{
    
public:
    /**
     * @brief Конструктор двусвязного списка.
     *
     * Создаёт пустой список, инициализируя размер нулём,
     * а указатели на начало и конец списка значением nullptr.
     */
    List();

    /**
     * @brief Деструктор двусвязного списка.
     *
     * Освобождает память, занятую всеми элементами списка,
     * вызывая метод clear().
     */
    ~List();

    /**
     * @brief Удаляет первый элемент списка.
     *
     * Если в списке один элемент, список становится пустым.
     * Если элементов несколько, удаляется головной узел,
     * а указатель head переносится на следующий элемент.
     */
    void pop_front();

    /**
     * @brief Добавляет новый элемент в начало списка.
     *
     * Создаёт новый узел и помещает его перед текущей головой списка.
     *
     * @param student Тип: studentsMASH. Структура с данными студента,
     * которую необходимо добавить в начало списка.
     */
    void push_front(studentsMASH student);

    /**
     * @brief Добавляет новый элемент в конец списка.
     *
     * Если список пуст, новый элемент становится первым.
     * Иначе элемент добавляется в конец списка, а указатель tail обновляется.
     *
     * @param student Тип: studentsMASH. Структура с данными студента,
     * которую необходимо добавить в конец списка.
     */
    void push_back(studentsMASH student);

    /**
     * @brief Удаляет последний элемент списка.
     *
     * Удаление выполняется через вызов removeAt(Size - 1).
     */
    void pop_back();

    /**
     * @brief Полностью очищает список.
     *
     * Последовательно удаляет все элементы списка,
     * пока его размер не станет равным нулю.
     */
    void clear();

    /**
     * @brief Удаляет элемент списка по индексу.
     *
     * Для поиска нужного узла используется проход от начала
     * или от конца списка в зависимости от позиции индекса.
     *
     * @param index Тип: int. Индекс удаляемого элемента.
     * Допустимые значения: от 0 до Size - 1.
     */
    void removeAt(int index);

    /**
     * @brief Возвращает текущее количество элементов в списке.
     *
     * @return Тип: int. Размер списка.
     * Допустимые значения: целое неотрицательное число, от 0 и выше.
     */
    int GetSize() { return Size; };

    /**
     * @brief Предоставляет доступ к элементу списка по индексу.
     *
     * Выполняет поиск элемента либо от начала, либо от конца списка
     * для уменьшения количества проходов по узлам.
     *
     * @param index Тип: const int. Индекс элемента списка.
     * Допустимые значения: от 0 до Size - 1.
     *
     * @return Тип: T&. Ссылка на найденный элемент списка.
     * При некорректном индексе генерируется исключение std::out_of_range.
     */
    T& operator[](const int index);

private:
    template<typename T>
    class Node
    {
    public:
        Node* pNext;      ///< Указатель на следующий узел списка.
        Node* pPrev;      ///< Указатель на предыдущий узел списка.
        studentsMASH student; ///< Данные студента, хранящиеся в узле.

        /**
         * @brief Конструктор узла списка.
         *
         * Инициализирует данные студента и связи с соседними узлами.
         *
         * @param student Тип: studentsMASH. Данные студента, сохраняемые в узле.
         * По умолчанию используется пустой объект studentsMASH.
         * @param pNext Тип: Node*. Указатель на следующий узел.
         * Допустимые значения: адрес узла или nullptr.
         * @param pPrev Тип: Node*. Указатель на предыдущий узел.
         * Допустимые значения: адрес узла или nullptr.
         */
        Node(studentsMASH student = studentsMASH(), Node* pNext = nullptr, Node* pPrev = nullptr)
        {
            this->student = student;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
    };

    int Size;       ///< Количество элементов в списке.
    Node<T>* head;  ///< Указатель на первый элемент списка.
    Node<T>* tail;  ///< Указатель на последний элемент списка.
};

template<typename T>
List<T>::List() {
    Size = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
void List<T>::pop_front()
{
    if (Size == 1) {
        delete head;
        head = nullptr;
        Size = 0;
    }
    else {
        Node<T>* temp = head;
        Node<T>* nextElem = head->pNext;
        head = nextElem;
        nextElem->pPrev = nullptr;
        delete temp;
        Size--;
    }
}

template<typename T>
void List<T>::push_back(studentsMASH student)
{
    if (head == nullptr) {
        head = new Node<T>(student);
    }
    else if (tail != nullptr) {
        Node<T>* newNode = new Node<T>(student, nullptr, tail);
        tail->pNext = newNode;
        tail = newNode;
    }
    else if (tail == nullptr) {
        Node<T>* current = this->head;
        while (current->pNext != nullptr) {
            current = current->pNext;
        }
        Node<T>* newNode = new Node<T>(student);
        current->pNext = newNode;
        newNode->pPrev = current;
        tail = newNode;
    }
    Size += 1;
}

template<typename T>
void List<T>::clear()
{
    while (Size) {
        pop_front();
    }
}

template<typename T>
void List<T>::push_front(studentsMASH student)
{
    Node<T>* newNode = new Node<T>(student, head);
    if (head != nullptr) {
        head->pPrev = newNode;
    }
    head = newNode;
    Size++;
}

template<typename T>
void List<T>::removeAt(int index)
{
    if (index == 0) {
        pop_front();
    }
    else {
        Node<T>* toDelete = this->head;
        int middle = Size / 2;
        if (index <= middle) {
            for (int i = 0; i < index; i++) {
                toDelete = toDelete->pNext;
            }
        }
        else {
            toDelete = this->tail;
            for (int i = Size - 1; i > index; i--) {
                toDelete = toDelete->pPrev;
            }
        }
        Node<T>* previous = toDelete->pPrev;
        if (toDelete == tail) {
            previous->pNext = nullptr;
            tail = previous;
        }
        else {
            Node<T>* afterToDeleteElem = toDelete->pNext;
            previous->pNext = afterToDeleteElem;
            afterToDeleteElem->pPrev = previous;
        }
        delete toDelete;
        Size--;
    }
}

template<typename T>
void List<T>::pop_back()
{
    removeAt(Size - 1);
}

template<typename T>
T& List<T>::operator[](const int index)
{
    int middle = Size / 2;
    if (index < 0 || index >= Size)
        throw std::out_of_range("Incorrect idnex");
    if (index <= middle) {
        int counter = 0;
        Node<T>* current = this->head;
        while (current) {
            if (counter == index) {
                return current->student;
            }
            current = current->pNext;
            counter += 1;
        }
    }
    else if (index > middle) {
        Node<T>* current = this->tail;
        int counter = Size - 1;
        while (current) {
            if (counter == index) {
                return current->student;
            }
            current = current->pPrev;
            counter -= 1;
        }
    }
}

/**
 * @brief Главная функция программы — консольное меню управления списком студентов.
 *
 * Программа реализует интерактивное меню для управления списком студентов,
 * участвующих в творческих мероприятиях. Можно добавлять и удалять студентов,
 * выводить список, проверять его длину и искать элементы по различным критериям.
 *
 * Основные действия:
 * 1. Добавление студента в список;
 * 2. Удаление студента из списка по индексу;
 * 3. Вывод всего списка студентов;
 * 4. Вывод длины списка;
 * 5. Поиск элементов по значению (ФИО, группа, мероприятие, дата);
 * 0. Выход из программы.
 *
 */
int main()
{
    List<studentsMASH> lst; ///< Список студентов, участвующих в мероприятиях.

    int choise; ///< Выбор действия пользователем из меню (0–5).
    int index;  ///< Индекс элемента для удаления или поиска.

    studentsMASH student; ///< Объект студента для добавления в список.

    wstring inputNameSurname; ///< Введённое ФИО студента.
    wstring inputGroupString; ///< Введённая группа в виде строки.
    int inputGroupNumber;     ///< Номер группы в виде целого числа.
    wstring inputEvent;       ///< Введённое название мероприятия.
    wstring inputEventDate;   ///< Введённая дата мероприятия в формате ДД/ММ/ГГ.

    wregex pattern(LR"(\d{2}/\d{2}/\d{2})"); ///< Регулярное выражение для проверки формата даты.
    bool isDateInvalid = true;                 ///< Признак невалидности даты (true — дата не проверена).
    wstring criterion;                         ///< Критерий поиска (ФИО, группа, мероприятие, дата).
    wstring paramForFind;                      ///< Значение для поиска по выбранному критерию.
    int founded = 0;                           ///< Количество найденных элементов при поиске.

    wstring input; ///< Введённая пользователем строка (для индекса, выхода и т.п.).

    studentsMASH object; ///< Временный объект студента для вывода или поиска.

    bool declined = true;   ///< Признак необходимости повторного ввода номера группы (true — ввод неверен).
    bool success = false;   ///< Признак успешного ввода индекса для удаления (false — индекс не введён).
    bool exit = false;      ///< Признак выхода из режима удаления (true — пользователь ввёл "exit").

    _setmode(_fileno(stdout), _O_U16TEXT); 
    _setmode(_fileno(stdin), _O_U16TEXT);  
    setlocale(LC_ALL, "Russian");          ///< Установка локализации для русского языка.

    while (true) {
        system("cls"); ///< Очищает консольное окно.

        wcout << L"Список студентов, участвующих в творческих мероприятиях\n\
____________________________________________________\nДействия:\
\t1. Добавление в список \n\
\t\t2. Удалить из списка \n\
\t\t3. Вывести спиок \n\
\t\t4. Длина списка \n\
\t\t5. Поиск элемента по значению \n\
\t\t0. Выход из программы \n\
____________________________________________________\n";

        wcout << L"\nВыберите действие: ";
        wcin >> choise; ///< Чтение выбора действия из консоли.

        switch (choise) {
        case 0:
            wcout << L"\nВыполнен выход из программы. Нажмите любую клавишу для продолжения...";
            wcin.ignore(); ///< Пропускает оставшиеся символы в строке ввода.
            wcin.get();    ///< Ожидает нажатия любой клавиши.
            return 0;      ///< Завершение программы с кодом 0.

        case 1:
            system("cls");
            wcout << L"Добавление студента\n\
____________________________________________________\n";

            wcout << L"Введите ФИО: ";
            wcin.ignore();
            getline(wcin, inputNameSurname); ///< Чтение ФИО целиком (до конца строки).

            declined = true;
            while (declined) {
                wcout << L"Введите номер группы: ";
                getline(wcin, inputGroupString); ///< Чтение номера группы в виде строки.

                try {
                    inputGroupNumber = stoi(inputGroupString); ///< Преобразование строки в int.
                    declined = false;
                }
                catch (...) {
                    wcout << L"Ошибка: Введено не число. Повторите попытку...\n";
                    declined = true;
                    continue;
                }
                if (stoi(inputGroupString) < 0) {
                    wcout << L"Ошибка: Неверный ввод. Повторите попытку...\n"; declined = true; continue;
                }
            }

            wcout << L"Введите мероприятие: ";
            getline(wcin, inputEvent); ///< Чтение названия мероприятия.

            isDateInvalid = true;
            while (isDateInvalid) {
                wcout << L"Введите дату в формате ДД/ММ/ГГ: ";
                getline(wcin, inputEventDate); ///< Чтение даты в формате ДД/ММ/ГГ.

                if (!regex_match(inputEventDate, pattern)) {
                    std::wcout << L"Ошибка: Неверный формат. Повторите попытку...\n";
                    continue;
                }
                int day = std::stoi(inputEventDate.substr(0, 2)); ///< Извлечение дня из строки.
                int month = std::stoi(inputEventDate.substr(3, 2)); ///< Извлечение месяца из строки.

                if (day <= 0 or day > 31) {
                    wcout << L"Ошибка: Неверная дата. Повторите попытку...\n";
                    continue;
                }
                if (month <= 0 or month > 12) {
                    wcout << L"Ошибка: Неверная дата. Повторите попытку...\n";
                    continue;
                }
                isDateInvalid = false;
            }

            student.nameSurname = inputNameSurname; ///< Заполнение объекта студента.
            student.group = inputGroupString;
            student.event = inputEvent;
            student.eventDate = inputEventDate;

            try { lst.push_back(student); } ///< Добавление студента в конец списка.
            catch (...) {
                wcout << L"Непредвиденная ошибка. Попробуйте снова...";
                break;
            }

            wcout << L"\nДобавлен элемент: \n\
____________________________________________________\n\nФИО: " << student.nameSurname << L"     Группа: " << student.group << L"\n\
 \tМероприятие: " << student.event << L"     Дата проведения: " << student.eventDate << L"\n\
____________________________________________________\n";

            wcout << L"\nНажмите любую клавишу для продолжения...";
            wcin.get(); ///< Ожидание нажатия любой клавиши.
            break;

        case 2:
            exit = false;
            wcin.ignore();
            system("cls");

            if (lst.GetSize() == 0) {
                wcout << L"Удаление объекта из списка\n\
____________________________________________________\nСписок пуст.\n\nНажмите любую клавишу для продолжения...";
                wcin.get();
                break;
            }

            wcout << L"Удаление объекта из списка\n\
____________________________________________________\nОбъекты:\n\n";

            for (int i = 0; i < lst.GetSize(); i++) {
                studentsMASH object = lst[i]; ///< Получение объекта студента по индексу.
                wcout << i << L"     " << object.nameSurname << L"     " << object.group << L"     \
" << object.event << L"     " << object.eventDate;
            }

            wcout << L"\n";

            while (!success) {
                wcout << L"\nВведите индекс для удаления (exit для выхода): ";
                getline(wcin, input); ///< Чтение индекса или команды "exit".

                if (input == L"exit") { exit = true; break; }

                try { index = stoi(input); } ///< Преобразование строки в int.
                catch (...) {
                    cout << "\nВведено не число. Повторите попытку...";
                    continue;
                }

                if (!(index < 0 or index > lst.GetSize() - 1)) {
                    success = true; ///< Индекс корректен.
                }
                else {
                    wcout << L"\nНеверный индекс. Повторите попытку...";
                    continue;
                }
            }

            if (exit == true) { break; }

            try { lst.removeAt(index); } ///< Удаление элемента по индексу.
            catch (...) {
                wcout << L"Непредвиденная ошибка. Попробуйте снова...";
                break;
            }

            wcout << L"\nЭлемент успешно удалён. Нажмите любую клавишу для продолжения...";
            wcin.get();
            break;

        case 3:
            system("cls");

            if (lst.GetSize() == 0) {
                wcout << L"Вывод списка\n\
____________________________________________________\nСписок пуст\n";
                wcout << L"\nНажмите любую клавишу для продолжения...";
                wcin.ignore();
                wcin.get();
                break;
            }

            wcout << L"Вывод списка\n\
____________________________________________________\n\nОбъекты:\n\n\
____________________________________________________\n\n";

            for (int i = 0; i < lst.GetSize(); i++) {
                studentsMASH object = lst[i]; ///< Получение объекта студента по индексу.
                wcout << L"   " << object.nameSurname << L"   " << object.group << L"   \
" << object.event << L"   " << object.eventDate << L"\n";
            }

            wcout << L"\n____________________________________________________\n\n\
Нажмите любую клавишу для продолжения...";
            wcin.ignore();
            wcin.get();
            break;

        case 4:
            system("cls");
            wcout << L"Длина списка\n\
____________________________________________________\nДлина: " << lst.GetSize();
            wcout << L"\n\nНажмите любую клавишу для продолжения...";
            wcin.ignore();
            wcin.get();
            break;

        case 5:
            wcin.ignore();

            while (true) {
                system("cls");
                wcout << L"Поиск элемента по значению\n\
____________________________________________________\nКритерии для поиска:\t1.ФИО\n\
                \t2.Номер группы\n\
                \t3.Мероприятие\n\
                \t4.Дата проведения\n\
                \t0.Выход из программы\n\
____________________________________________________\
                \nВведите критерий для поиска: ";

                getline(wcin, criterion); ///< Чтение критерия поиска.

                if (criterion == L"0") {
                    break; ///< Выход из режима поиска.
                }

                if (takeCriterion(criterion) == -1) {
                    wcout << L"Критерий не найден. Повторите попытку...";
                    wcin.get();
                    continue;
                }

                wcout << L"Введите значение для поиска: ";
                getline(wcin, paramForFind); ///< Чтение значения для поиска.

                wcout << L"\nНайденные элементы списка: \n\
____________________________________________________\n";

                switch (takeCriterion(criterion)) {
                case 1: ///< Поиск по ФИО.
                    founded = 0;
                    for (int i = 0; i < lst.GetSize(); i++) {
                        studentsMASH object = lst[i];
                        if (object.nameSurname == paramForFind) {
                            founded += 1;
                            wcout << L"   " << object.nameSurname << L"   " << object.group << L"   \
" << object.event << L"   " << object.eventDate << "\n";
                        }
                    }
                    break;

                case 2: ///< Поиск по номеру группы.
                    founded = 0;
                    for (int i = 0; i < lst.GetSize(); i++) {
                        studentsMASH object = lst[i];
                        if (object.group == paramForFind) {
                            founded += 1;
                            wcout << L"   " << object.nameSurname << L"   " << object.group << L"   \
" << object.event << L"   " << object.eventDate << "\n";
                        }
                    }
                    break;

                case 3: ///< Поиск по мероприятию.
                    founded = 0;
                    for (int i = 0; i < lst.GetSize(); i++) {
                        studentsMASH object = lst[i];
                        if (object.event == paramForFind) {
                            founded += 1;
                            wcout << L"   " << object.nameSurname << L"   " << object.group << L"   \
" << object.event << L"   " << object.eventDate << "\n";
                        }
                    }
                    break;

                case 4: ///< Поиск по дате проведения.
                    founded = 0;
                    for (int i = 0; i < lst.GetSize(); i++) {
                        studentsMASH object = lst[i];
                        if (object.eventDate == paramForFind) {
                            founded += 1;
                            wcout << L"   " << object.nameSurname << L"   " << object.group << L"   \
" << object.event << L"   " << object.eventDate << "\n";
                        }
                    }
                    break;
                }

                if (founded == 0) {
                    wcout << L"Элементы списка не найдены.\n\
____________________________________________________\nНажмите любую клавишу для продолжения...";
                    wcin.get();
                    continue;
                }
                else {
                    wcout << L"____________________________________________________\n\
Нажмите любую клавишу для продолжения...";
                    wcin.get();
                    continue;
                }
                continue;
            }
            break;
        }
    }
}