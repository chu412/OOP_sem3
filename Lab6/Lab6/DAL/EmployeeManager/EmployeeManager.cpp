#include "./EmployeeManager.h"

EmployeeManager::EmployeeManager() {
    this->employees.resize(0);
}

vector <Employee*> EmployeeManager::get_employees() {
    return this->employees;
}

void EmployeeManager::add(Employee* a) {
    this->employees.push_back(a);
}

Employee* EmployeeManager::findEmployee(string name) {
    for (Employee* e : this->employees) {
        if (e->getName() == name) {
            return e;
        }
    }
    return nullptr;
}