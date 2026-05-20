#include <vector>
#include <iostream>
#include <string>
#include <fstream>

struct Task {
    std::string taskName;
    int status = 0;
};
struct TaskList {
    std::string listName;
    std::vector<Task> tasks;
};
std::vector<TaskList> tasks;
int currentList = 0;

void addTask(std::string name, char status) {
    Task newTask;
    newTask.taskName = name;
    if (status == 'y') {
        newTask.status = 1;
    } else if (status == 'n') {
        newTask.status = 0;
    } else {
        newTask.status = 2;
    }
    tasks[currentList].tasks.push_back(newTask);
}
void viewTasks() {
    // std::cout << tasks[currentList].listName << "\n";
    TaskList viewTask;
    for (int i = 0; i < tasks[currentList].tasks.size(); i++) {
        char status = ' ';
        if (tasks[currentList].tasks[i].status == 0) {
            status = ' ';
        } else if (tasks[currentList].tasks[i].status == 1) {
            status = 'x';
        } else {
            status = '/';
        }
        std::cout << i + 1 << " [" << status << "] " << tasks[currentList].tasks[i].taskName << "\n";
    }
}
void viewLists() {
    for (int i = 0; i < tasks.size(); i++) {
        std::cout << i + 1 << " - " << tasks[i].listName << "\n";
    }
}
void modifyTasks(std::string name, char status, int id) {
    tasks[currentList].tasks[id].taskName = name;
    if (status == 'y') {
        tasks[currentList].tasks[id].status = 1;
    } else if (status == 'n') {
        tasks[currentList].tasks[id].status = 0;
    } else {
        tasks[currentList].tasks[id].status = 2;
    }
}
void deleteTask(int id) {
    tasks[currentList].tasks.erase(tasks[currentList].tasks.begin() + id);
}

int main() {
    // load();
    TaskList n;
    n.listName = "placeholder";
    tasks.push_back(n);
    std::string cmd;
    int id;
    std::string name;
    char status;
    while (true) {
        std::cout << tasks[currentList].listName << ": ";
        std::cin >> cmd;
        if (cmd == "new") {
            std::cin >> status;
            std::cin >> name;
            addTask(name, status);
        } else if (cmd == "view") {
            viewTasks();
        } else if (cmd == "viewLists") {
            viewLists();
        } else if (cmd == "modify") {
            std::cin >> id;
            std::cin >> status;
            std::cin >> name;
            modifyTasks(name, status, id - 1);
        } else if (cmd == "delete") {
            std::cin >> id;
            deleteTask(id);
        } else if (cmd == "newList") {
            std::cin >> name;
            TaskList newList;
            newList.listName = name;
            tasks.push_back(newList);
        } else if (cmd == "switch") {
            std::cin >> id;
            currentList = id - 1;
        } else if (cmd == "clear") {
            std::cout << "\033[2J\033[H";
        }
    }
    return 0;
}