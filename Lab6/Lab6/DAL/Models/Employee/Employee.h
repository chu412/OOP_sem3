#ifndef Employee_H
#define Employee_H
#include <string>
#include <vector>
using namespace std;
class Employee {
public:
    Employee();
    Employee(string name);
    Employee(string name, vector<Employee> subordinatesList);
    string getName();
    void setName(string name);
    string getBossName();
    void setBoss(Employee* boss);
private:
    string name;
    Employee* boss;
    vector<Employee> subordinatesList;
};

#endif 