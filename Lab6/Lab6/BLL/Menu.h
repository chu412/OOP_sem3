#ifndef Menu_H
#define Menu_H
#include <iostream>

#include "../DAL/EmployeeManager/EmployeeManager.h"
#include "../DAL/TaskManager/TaskManager.h"
#include "../DAL/ReportManager/ReportManager.h"

using namespace std;
class Menu {
public:
    void mainConsoleMenu();
    void reportsConsoleMenu();
    void employeeConsoleMenu();
    void taskConsoleMenu();
    void taskStatusMenu();
};
#endif // !Menu_H
