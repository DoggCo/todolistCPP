#include <vector>
#include <iostream>
#include <string>
#include <fstream>

struct task {
    std::string taskName;
    int status = 0;
};
std::vector<task> tasks;
void addTask(std::string name, char status) {
    task newTask;
    newTask.taskName = name;
    if (status == 'y') {
        newTask.status = 1;
    } else if (status == 'n') {
        newTask.status = 0;
    } else {
        newTask.status = 2;
    }
    tasks.push_back(newTask);
}
void removeTask(int id) {
    tasks.erase(tasks.begin() + id - 1);
}
void viewTasks() {
    for (int i = 0; i < tasks.size(); i++) {
        char status = ' ';
        if (tasks[i].status == 0) {
            status = ' ';
        } else if (tasks[i].status == 1) {
            status = 'x';
        } else {
            status = '/';
        }
        std::cout << i + 1 << " [" << status << "] " << tasks[i].taskName << "\n";
    }
}
void modifyTask(int id, std::string newName, char status) {
    tasks[id - 1].taskName = newName;
    if (status == 'y') {
        tasks[id - 1].status = 1;
    } else if (status == 'n') {
        tasks[id - 1].status = 0;
    } else {
        tasks[id - 1].status = 2;
    }
}
void save() {
    std::ofstream outFile("tasks.txt");
    for (const auto& t : tasks) {
        outFile << t.status << "|" << t.taskName << "\n";
    }
    outFile.close();
}
void load() {
    std::ifstream inFile("tasks.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        size_t separator = line.find('|');
        if (separator != std::string::npos) {
            task t;
            t.status = std::stoi(line.substr(0, separator));
            t.taskName = line.substr(separator + 1);
            tasks.push_back(t);
        }
    }
    inFile.close();
}
int main() {
    load();
    std::string cmd;
    int id;
    std::string name;
    char status;
    while (true) {
        std::cin >> cmd;
        if (cmd == "new") {
            std::cin >> status;
            std::getline(std::cin >> std::ws, name);
            addTask(name, status);
        } else if (cmd == "view") {
            viewTasks();
        } else if (cmd == "modify") {
            std::cin >> id;
            std::cin >> status;
            std::getline(std::cin >> std::ws, name);
            modifyTask(id, name, status);
        } else if (cmd == "delete") {
            std::cin >> id;
            removeTask(id);
        } else if (cmd == "exit") {
            save();
            break;
        } else {
            std::cout << "????\n";
        }
    }
    return 0;
}