#ifndef EmployeeManager_H
#define EmployeeManager_H
#include <vector>
#include "../Models/Employee/Employee.h"
using namespace std;

class EmployeeManager {
public:
    EmployeeManager();
    vector <Employee*> get_employees();
    void add(Employee* a);
    Employee* findEmployee(string name);

private:
    vector <Employee*> employees;
};
#endif // !EmployeeManager_H
