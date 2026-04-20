#include <vector>
#include <iostream>
#include <string>
#include <fstream>

std::vector<std::string> tasks;
void addTask() {
    std::cout << "Please enter task: ";
    std::string enter;
    std::getline(std::cin >> std::ws, enter);
    tasks.push_back(enter);
}
void viewTasks() {
    for (int i = 0; i < tasks.size(); i++) {
        std::cout << tasks[i] << "\n";
    }
    std::cin.ignore();
    std::cin.get();
}
void removeTask() {
    std::cout <<"\n";
    for (int i = 0; i < tasks.size(); i++) {
        std::cout << i + 1 << " - " << tasks[i] << "\n";
    }
    int del = 0;
    std::cout << "Enter number of task to delete (-1 for all tasks, 0 to go back): ";
    std::cin >> del;
    if (del == 0) {
        return;
    }
    if (del == -1) {
        tasks.clear();
        return;
    }
    tasks.erase(tasks.begin() + del - 1);
}
void modifyTask() {
    std::cout <<"\n";
    for (int i = 0; i < tasks.size(); i++) {
        std::cout << i + 1 << " - " << tasks[i] << "\n";
    }
    int modify = 0;
    std::string newTask;
    std::cout << "Enter number of task to modify: ";
    std::cin >> modify;
    std::cout << "Enter new task: ";
    std::cin >> newTask;
    tasks[modify - 1] = newTask;
}

int menu() {
    std::cout << "--- Tasks ---\n\n";
    std::cout << "1 - Add task\n";
    std::cout << "2 - Remove task\n";
    std::cout << "3 - Modify task\n";
    std::cout << "4 - View tasks\n";
    std::cout << "0 - Save & Exit\n";
    int choice = 0;
    std::cin >> choice;
    return choice;
}
void save() {
    std::ofstream outFile("ez4ence.txt");
    for (const auto& line : tasks) {
        outFile << line << "\n";
    }
    outFile.close();
}

int main() {
    std::ifstream inFile("ez4ence.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        tasks.push_back(line);
    }
    inFile.close();
    while (true) {
        int choice = menu();
        switch (choice) {
            case 1:
            addTask();
            break;

            case 2:
            removeTask();
            break;

            case 3:
            modifyTask();
            break;

            case 4:
            viewTasks();
            break;

            case 0:
            save();
            return 0;
        }
    }
}

/*
TODO:

use a struct to show finished tasks, maybe add seperate task "lists", which is just different arrays

struct task {
    std::string text;
    bool completed = false;
};

[ ] Buy money
[x] Mcdonalds

*/