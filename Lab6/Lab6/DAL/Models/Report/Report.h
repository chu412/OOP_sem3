#ifndef Report_H
#define Report_H
#include "../Task/Task.h"
using namespace std;

class Report {
public:
    Report();
    void addTask(Task task);
    string toString();

private:
    string description;
};


#endif // 
