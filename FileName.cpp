#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>
#include "functions.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Task> tasks;
    load_tasks(tasks);

    int choice;

    do {
        cout << R"([1]- �������� ����
[2] - �������� ���� �����������
[3] - ������������� ����
[4] - ������� ����
[5] - �������� ������ ���
[0] - �����)";
        cout <<endl<<"�������� ��������: ";
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
            cout << "����� �� ���������" << endl;
            break;
        default: 
            cout << "�������� �����. ���������� ��� ���" << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}