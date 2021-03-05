
#include "Interface.h"
using namespace std;

void taskHelp() {
    cout << "1. Add task" << endl;
    cout << "2. Change task data by ID" << endl;
    cout << "3. Find tasks by creation date" << endl;
    cout << "4. Find tasks by last change date" << endl;
    cout << "5. Find tasks by employee name" << endl;
    cout << "6. Find changed tasks" << endl;
    cout << "7. Change task status" << endl;
    cout << "8. Set comment for task" << endl;
    cout << "9. Find task by ID" << endl;
    cout << "0. Show all tasks" << endl;
    cout << "-1. Main menu" << endl;
}

void taskStatus() {
    cout << "1. Start task" << endl;
    cout << "2. Complete task" << endl;
    cout << "-1. Return to previous menu" << endl;
}

void employeeHelp() {
    cout << "1. Add employee" << endl;
    cout << "2. Change employee name" << endl;
    cout << "3. Set leader for employee" << endl;
    cout << "0. Show employees" << endl;
    cout << "-1. Main menu" << endl;
}

void reportsHelp() {
    cout << "1. Create report for all sprint" << endl;
    cout << "2. Create report for day" << endl;
    cout << "0. Show reports" << endl;
    cout << "-1. Main menu" << endl;
}

void mainHelp() {
    cout << "1. Tasks" << endl;
    cout << "2. Employees" << endl;
    cout << "3. Reports" << endl;
    cout << "0. Exit" << endl;
}