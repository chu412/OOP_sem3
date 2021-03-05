#include "Task.h"

string getCurrentTime() {
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
    string str(buffer);
    return str;
}

void Task::setTime() {
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    this->creationDateRaw = timeinfo;
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
    string str(buffer);
    this->creationDate = str;
}

struct tm* Task::getCreationDateRaw() {
    return this->creationDateRaw;
}

Task::Task() {

}
Task::Task(int id, string name, string description, Employee employee) {
    this->lastChangeDate = "NULL";
    this->id = id;
    this->name = name;
    this->description = description;
    this->status = TaskStatus::OPEN;
    this->employee = employee;
    this->log = "";

    this->setTime();
}


string Task::toString() {
    string str = "---------------------------\n";
    str += "Id: %d\n";
    str += "Name: %s\n";
    str += "Description: %s\n";
    str += "Comment: %s\n";
    str += "Employee: %s\n";
    str += "Status: %s\n";
    str += "Creation date: %s\n";
    str += "Log: %s\n";
    str += "-----------------------\n";

    string status_string;
    if (status == Task::ACTIVE) {
        status_string = "Active";
    }
    else if (status == TaskStatus::OPEN) {
        status_string = "Open";
    }
    else {
        status_string = "Closed";
    }

    char* new_buf = nullptr;
    while (new_buf == nullptr) {
        new_buf = (char*)malloc(1000);
    }

    memset(new_buf, 0, 1000);
    sprintf(new_buf, str.c_str(), id, name.c_str(), description.c_str(), comment.c_str(), employee.getName().c_str(), status_string.c_str(), creationDate.c_str(), log.c_str());

    string str1(new_buf);
    return str1;
}

int Task::getId() {
    return id;
}

string Task::getName() {
    return name;
}

void Task::setName(string name) {
    this->name = name;

    this->lastChangeDate = getCurrentTime();
    this->log += "name changed ";
    this->log += getCurrentTime();
    this->log += "\n";
}

string Task::getDescription() {
    return description;
}

void Task::setDescription(string description) {
    this->description = description;

    this->lastChangeDate = getCurrentTime();
    this->log += "description changed ";
    this->log += getCurrentTime();
    this->log += "\n";
}

Employee Task::getEmployee() {
    return employee;
}

void Task::setEmployee(Employee employee) {
    this->employee = employee;

    this->lastChangeDate = getCurrentTime();
    this->log += "employee changed ";
    this->log += getCurrentTime();
    this->log += "\n";
}

Task::TaskStatus Task::getStatus() {
    return status;
}

void Task::setStatus(TaskStatus status) {
    this->status = status;

    this->lastChangeDate = getCurrentTime();
    this->log += "status changed ";
    this->log += this->lastChangeDate;
    this->log += "\n";
}

string Task::getCreationDate() {
    return creationDate;
}

string Task::getLastChangeDate() {
    return lastChangeDate;
}

void Task::addComment(string comm) {
    this->comment = comm;

    this->lastChangeDate = getCurrentTime();
    this->log += "comment changed ";
    this->log += this->lastChangeDate;
    this->log += "\n";
}