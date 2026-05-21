#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

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

bool idCheck(int id) {
    if (id >= tasks[currentList].tasks.size() || id < 0) {
        std::cout << "Returning.\n";
        return false;
    }
    return true;
}
bool listIdCheck(int id) {
    return id >= 0 && id < tasks.size();
}
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
    if (!idCheck(id)) {
        return;
    }
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
    if (!idCheck(id)) {
        return;
    }
    tasks[currentList].tasks.erase(tasks[currentList].tasks.begin() + id);
}
void deleteList(int id) {
    if (!listIdCheck(id)) {
        return;
    }
    tasks.erase(tasks.begin() + id);
    currentList = 0;
}
void deleteTxt() {
    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        if (entry.path().extension() == ".txt") {
            std::filesystem::remove(entry.path());
        }
    }
}

void save() {
    deleteTxt();
    for (const auto& list : tasks) {
        std::string filename = list.listName + ".txt";
        std::ofstream out(filename);
        for (const auto& t : list.tasks) {
            out << t.status << "|" << t.taskName << "\n";
        }
    }
}
void load() {
    tasks.clear();
    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        if (entry.path().extension() == ".txt") {
            TaskList list;
            list.listName = entry.path().stem().string();
            std::ifstream in(entry.path());
            std::string line;
            while (std::getline(in, line)) {
                size_t sep = line.find('|');
                if (sep != std::string::npos) {
                    Task t;
                    t.status = std::stoi(line.substr(0, sep));
                    t.taskName = line.substr(sep + 1);
                    list.tasks.push_back(t);
                }
            }
            tasks.push_back(list);
        }
    }
    if (!tasks.empty()) currentList = 0;
}
void renameList(std::string name) {
    tasks[currentList].listName = name;
}
void help() {
    std::cout << "\nThe current TODO-list you're using will be displayed to the left.\n";
    std::cout << "new         y|n|/   TASKNAME\n";
    std::cout << "modify  ID  y|n|/   TASKNAME\n";
    std::cout << "delete  ID                  \n";
    std::cout << "view                      \n\n";

    std::cout << "newList             LISTNAME\n";
    std::cout << "switch              LISTNAME\n";
    std::cout << "delList             LIST ID \n";
    std::cout << "viewLists                   \n";
    std::cout << "rename              LISTNAME\n\n";
    
    std::cout << "exit                        \n";
    std::cout << "clear                     \n\n";
}
int main() {
    load();
    if (tasks.empty()) {
        TaskList n;
        n.listName = "To-Do";
        tasks.push_back(n);
    }
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
            deleteTask(id - 1);
        } else if (cmd == "newList") {
            std::cin >> name;
            TaskList newList;
            newList.listName = name;
            tasks.push_back(newList);
        } else if (cmd == "delList") {
            std::cin >> id;
            deleteList(id - 1);
        } else if (cmd == "switch") {
            std::cin >> id;
            currentList = id - 1;
        } else if (cmd == "clear") {
            std::cout << "\033[2J\033[H";
        } else if (cmd == "rename") {
            std::cin >> name;
            renameList(name);
        } else if (cmd == "exit") {
            save();
            break;
        } else if (cmd == "help") {
            help();
        } else {
            std::cout << "\n";
        }
    }
    return 0;
}