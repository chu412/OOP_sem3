#ifndef TaskManager_H
#define TaskManager_H
#include <vector>
#include "../Models/Task/Task.h"
using namespace std;

class TaskManager {
public:
    TaskManager();
    vector <Task*> get_tasks();
    void add(Task* a);
    Task* getTaskById(int id);
private:
    vector <Task*> tasks;
};
#endif // !TaskManager_H
