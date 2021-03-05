#include "Employee.h"

Employee::Employee() {

}

Employee::Employee(string name) {
    this->name = name;
    this->boss = nullptr;
}

Employee::Employee(string name, vector<Employee> subordinatesList) {
    this->name = name;
    this->subordinatesList = subordinatesList;
    this->boss = nullptr;
}

string Employee::getName() {
    return name;
}

void Employee::setName(string name) {
    this->name = name;
}

string Employee::getBossName() {
    if (this->boss == nullptr) return "NULL";
    return this->boss->getName();
}

void Employee::setBoss(Employee* boss) {
    this->boss = boss;
}