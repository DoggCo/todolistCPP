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

class real {
    private:
    int currentList = 0;
    std::vector<TaskList> tList;

    bool idCheck(int id) {
        return id <= 0 && id < tList[currentList].tasks.size();
    }
    bool listIdCheck(int id) {
        return id >= 0 && id < tList.size();
    }
    int charStatus(char n) {
        if (n == 'n') {
            return 0;
        } else if (n == 'y') {
            return 1;
        } else {
            return 2;
        }
    }

    public:
    void addTask(std::string name, char status) {
        Task newTask;
        newTask.taskName = name;
        newTask.status = charStatus(status);
        tList[currentList].tasks.push_back(newTask);
    }
    void viewTasks() {
        TaskList viewTask;
        for (int i = 0; i < tList[currentList].tasks.size(); i++) {
            char status = ' ';
            if (tList[currentList].tasks[i].status == 0) {
                status = ' ';
            } else if (tList[currentList].tasks[i].status == 1) {
                status = 'x';
            } else {
                status = '/';
            }
            std::cout << i + 1 << " [" << status << "] " << tList[currentList].tasks[i].taskName << "\n";
        }
    }
    void viewLists() {
        for (int i = 0; i < tList.size(); i++) {
            std::cout << i + 1 << " - " << tList[i].listName << "\n";
        }
    }
    void modifyTask(std::string name, char status, int id) {
        if (!idCheck(id)) {
            return;
        }
        tList[currentList].tasks[id].taskName = name;
        tList[currentList].tasks[id].status = (status);
    }
    void deleteTask(int id) {
        if (id == -2) {
            char yn;
            std::cout << "are u sure delete all (y/n): ";
            std::cin >> yn;
            if (yn == 'y') {
                tList[currentList].tasks.clear();
            }
            return;
        }
        if (!idCheck(id)) {
            return;
        }
        tList[currentList].tasks.erase(tList[currentList].tasks.begin() + id);
    }
    void deleteList(int id) {
        if (!listIdCheck(id)) {
            return;
        }
        tList.erase(tList.begin() + id);
        currentList = 0;
    }
    void renameList(std::string name) {
        tList[currentList].listName = name;
    }
    void printCurrentList() {std::cout << tList[currentList].listName << ": ";}
    real() {
        if (tList.empty()) {
            TaskList n;
            n.listName = "ToDo";
            tList.push_back(n);
        }
    }
};

void help() {
    std::cout << "\nThe current TODO-list you're using will be displayed to the left.\n";
    std::cout << "new          y|n|/   TASKNAME\n";
    std::cout << "modify  ID   y|n|/   TASKNAME\n";
    std::cout << "delete  ID (-1 for all tasks)\n";
    std::cout << "view                      \n\n";

    std::cout << "newList              LISTNAME\n";
    std::cout << "switch               LIST ID \n";
    std::cout << "delList              LIST ID \n";
    std::cout << "viewLists                    \n";
    std::cout << "rename     (current) LISTNAME\n\n";
    
    std::cout << "exit                         \n";
    std::cout << "clear                        \n";
    std::cout << "save                       \n\n";
}

int safe() {
    int number;
    if (std::cin >> number) {
        return number;
    }
    std::cin.clear();
    std::cin.ignore(100000, '\n');
    return -2;
}

int main() {
    real ez4ence;
    // load();
    std::string cmd;
    int id;
    std::string name;
    char status;
    std::cout << "welcome. run \"help\"";
    while (true) {
        ez4ence.printCurrentList();
        std::cin >> cmd;
        if (cmd == "new") {
            std::cin >> status;
            std::getline(std::cin >> std::ws, name);
            ez4ence.addTask(name, status);
        }
    }
}