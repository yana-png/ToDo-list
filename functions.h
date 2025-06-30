#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


// ������� ��������� ����
struct Task {
    string name; // ��������
    string date_completion; // ����
    string description; // �������� 
    bool status_task; // ���������\�� ���������
};
// ������� ��� ���������� ������ � ����
void save_tasks(const vector<Task>& tasks) {
    ofstream file("tasks.txt");
    for (const auto& task : tasks) { //���� �������� �� ���� ��������� ������� tasks � ���������� ������ ������ � ����
        file << task.name << endl;
        file << task.date_completion << endl;
        file << task.description << endl;
        file << task.status_task << endl;
    }
    file.close(); //��������� ����, ����� ��� ������ ���� �������� ��������� � � ���������� �� ���� ��������
}
// ������� ��� �������� ����� �� �����
void load_tasks(vector<Task>& tasks) {
    ifstream file("tasks.txt");
    Task task;
    while (getline(file, task.name)) {
        getline(file, task.date_completion);
        getline(file, task.description);
        file >> task.status_task;
        file.ignore(); // ������� ������
        tasks.push_back(task);
    }
    file.close();
}

// ������� ��� �������� ����
void add_task(vector<Task>& tasks) {
    Task new_task;
    new_task.status_task = false; // ����� ������ ������ ������ � �� ���������

    // ���� ���� ������
    cout << "������� �������� ����: ";
    getline(cin, new_task.name);
    cout << "������� ���� (��.��.����): ";
    getline(cin, new_task.date_completion);
    cout << "������� �������� ����: ";
    getline(cin, new_task.description);

    tasks.push_back(new_task); // ��������� ������� � ����� ������� "tasks"
    save_tasks(tasks); // ��������� � ���� ����� ����������
    cout << "���� ���������!" << endl;
}

// �������, ����� ������������ ������� ���� �����������
void complete_task(vector<Task>& tasks) {
    int index;
    cout << "������� ����� ���� ��� ����������: ";
    cin >> index;
    cin.ignore();

    if (index >= 0 && index < tasks.size()) { // ��������� ���������� �� ���� � ����� �������
        tasks[index].status_task = true; // �������� �����������
        save_tasks(tasks); // ��������� ��������� � ����
        cout << "���� ���������!" << endl;
    }
    else {
        cout << "�������� ����� ����" << endl;
    }
}

// ������� ��� �������������� ����
void edit_task(vector<Task>& tasks) {
    int index;
    cout << "������� ����� ���� ��� ��������������: ";
    cin >> index;
    cin.ignore();

    if (index >= 0 && index < tasks.size()) { //���� ���� �� ��� ������
        cout << "������� ����� �������� ����: ";
        getline(cin, tasks[index].name);
        cout << "������� ����� ���� ����������: ";
        getline(cin, tasks[index].date_completion);
        cout << "������� ����� �������� ����: ";
        getline(cin, tasks[index].description);
        save_tasks(tasks); // ��������� ��������� � ����
        cout << "������� ���������!" << endl;
    }
    else {
        cout << "�������� ����� ����!" << endl;
    }
}
// ������� ��� �������� ����
void delete_task(vector<Task>& tasks) {
    int index;
    cout << "������� ����� ���� ��� ��������: ";
    cin >> index;
    cin.ignore();
                                  //����� size ���������� ����������� �������!
    if (index >= 0 && index < tasks.size()) { //��������� ������������ �����. index ������ ���� ����� 0 ��� ���� ������ ������� �������
        tasks.erase(tasks.begin() + index); // ������� ���� � �������
        save_tasks(tasks); // ��������� ��������� � ����
        cout << "���� �������!" << endl;
    }
    else {
        cout << "�������� ����� ����!" << endl;
    }
}

//������� ��� ���������� ����
void display_tasks(const vector<Task>& tasks) {
    for (int i = 0; i < tasks.size(); ++i) { //�������� �� ���� ��������� �������. ������� ������ ����, ���, ���� � ��������
        cout << "[" << i << "] " << tasks[i].name << " ("
            << (tasks[i].status_task ? "���������" : "�� ���������") << ")" //��������� ��������
            << " - " << tasks[i].date_completion << ": " << tasks[i].description << endl;
    }
}