#include "./TaskManager.h"

TaskManager::TaskManager() {
    this->tasks.resize(0);
}

vector <Task*> TaskManager::get_tasks() {
    return this->tasks;
}

void TaskManager::add(Task* a) {
    this->tasks.push_back(a);
}

Task* TaskManager::getTaskById(int id) {
    for (Task* t : this->tasks) {
        if (t->getId() == id) {
            return t;
        }
    }
    return nullptr;
}