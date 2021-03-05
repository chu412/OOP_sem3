#ifndef Task_H
#define Task_H

#include <string>
#include <time.h>
#include "../Employee/Employee.h"
using namespace std;

class Task {
public:
    enum TaskStatus {
        OPEN,
        ACTIVE,
        RESOLVED
    };
    Task();
    Task(int id, string name, string description, Employee employee);
    string toString();
    int getId();
    string getName();
    void setName(string name);
    string getDescription();
    void setDescription(string description);
    Employee getEmployee();
    void setEmployee(Employee employee);
    TaskStatus getStatus();
    void setStatus(TaskStatus);
    string getCreationDate();
    struct tm* getCreationDateRaw();
    string getLastChangeDate();
    void addComment(string comm);
    void setTime();

private:
    int id;
    string name;
    string description;
    string comment;
    Employee employee;
    TaskStatus status;
    string creationDate;
    string lastChangeDate;
    string log;
    struct tm* creationDateRaw;
};
#endif