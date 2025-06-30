    #include <iostream>
    #include <vector>
    #include <string>
    #include <fstream>
    #include <Windows.h>
    #include "functions.h"

    using namespace std;

    // создаем структуру дела
    struct Task {
    string name; // название
    string date_completion; // дата
    string description; // описание 
    bool status_task; // выполнено\не выполнено
    };
// Функция для сохранения задачи в файл
void save_tasks(const vector<Task>& tasks) {
    ofstream file("tasks.txt");
    for (const auto& task : tasks) { //цикл проходит по всем элементам вектора tasks и записывает каждую строку в файл
        file << task.name << endl;
        file << task.date_completion << endl;
        file << task.description << endl;
        file << task.status_task << endl;
    }
    file.close(); //закрывает файл, чтобы все данные были записаны корректно и в дальнейшем не бфли потеряны
}
// Функция для загрузки задач из файла
void load_tasks(vector<Task>& tasks) {
    ifstream file("tasks.txt");
    Task task;
    while (getline(file, task.name)) {
        getline(file, task.date_completion);
        getline(file, task.description);
        file >> task.status_task;
        file.ignore(); // очистка буфера
        tasks.push_back(task);
    }
    file.close();
}

// Функция для создания дела
void add_task(vector<Task>& tasks) {
    Task new_task;
    new_task.status_task = false; // сразу ставим статус задачи в не выполнено

    // ввод всех данных
    cout << "введите название дела: ";
    getline(cin, new_task.name);
    cout << "введите дату (ДД.ММ.ГГГГ): ";
    getline(cin, new_task.date_completion);
    cout << "введите описание дела: ";
    getline(cin, new_task.description);

    tasks.push_back(new_task); // добавляем элемент в конец вектора "tasks"
    save_tasks(tasks); // сохраняем в файл после добавления
    cout << "Дело добавлено!" << endl;
}

// Функция, чтобы пользователь отметил дело выполненным
void complete_task(vector<Task>& tasks) {
    int index;
    cout << "введите номер дела для выполнения: ";
    cin >> index;
    cin.ignore();

    if (index >= 0 && index < tasks.size()) { // проверяем существует ли дело с таким номером
        tasks[index].status_task = true; // отмечаем выполненным
        save_tasks(tasks); // сохраняем изменения в файл
        cout << "дело выполнено!" << endl;
    }
    else {
        cout << "неверный номер дела" << endl;
    }
}

// Функция для редактирования дела
void edit_task(vector<Task>& tasks) {
    int index;
    cout << "введите номер дела для редактирования: ";
    cin >> index;
    cin.ignore();

    if (index >= 0 && index < tasks.size()) { //ищет дело по его номеру
        cout << "введите новое название дела: ";
        getline(cin, tasks[index].name);
        cout << "введите новую дату исполнения: ";
        getline(cin, tasks[index].date_completion);
        cout << "введите новое описание дела: ";
        getline(cin, tasks[index].description);
        save_tasks(tasks); // сохраняем изменения в файл
        cout << "успешно обновлено!" << endl;
    }
    else {
        cout << "неверный номер дела!" << endl;
    }
}
// Функция для удаления дела
void delete_task(vector<Task>& tasks) {
    int index;
    cout << "введите номер дела для удаления: ";
    cin >> index;
    cin.ignore();
                                  //метод size возвращвет размерность вектора!
    if (index >= 0 && index < tasks.size()) { //проверяет корректность ввода. index должен быть равен 0 или быть меньше размера вектора
        tasks.erase(tasks.begin() + index); // удаляем дело с вектора
        save_tasks(tasks); // сохраняем изменения в файл
        cout << "дело удалено!" << endl;
    }
    else {
        cout << "неверный номер дела!" << endl;
    }
}

//выводит все сохраненые дела
void display_tasks(const vector<Task>& tasks) {
    for (int i = 0; i < tasks.size(); ++i) { //проходит по всем элементам вектора. выводит индекс дела, имя, дату и описание
        cout << "[" << i << "] " << tasks[i].name << " ("
            << (tasks[i].status_task ? "выполнено" : "не выполнено") << ")" //тернарный оператор
            << " - " << tasks[i].date_completion << ": " << tasks[i].description << endl;
    }
}

    int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Task> tasks;
    load_tasks(tasks);

    int choice;

    do {
        cout << R"(
     [1]- добавить дело
     [2] - отметить дело выполненным
     [3] - редактировать дело
     [4] - удалить дело
     [5] - показать список дел
     [0] - выход)";
        cout <<endl<<"Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: 
            add_task(tasks);
            break;
        case 2:
            complete_task(tasks);
            break;
        case 3:
            edit_task(tasks);
            break;
        case 4: 
            delete_task(tasks); 
            break;
        case 5:
            display_tasks(tasks); 
            break;
        case 0: 
            cout << "выход из программы" << endl;
            break;
        default: 
            cout << "неверный выбор. попробуйте еще раз" << endl;
            break;
        }
    } while (choice != 0);

    return 0;
    }
