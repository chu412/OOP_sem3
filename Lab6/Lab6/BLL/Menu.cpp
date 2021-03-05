#include "./Menu.h"
#include "../UI/Interface.h"

TaskManager task_mgr = TaskManager();
ReportManager report_mgr = ReportManager();
EmployeeManager employee_mgr = EmployeeManager();

void Menu::mainConsoleMenu() {
    mainHelp();
    int userInput;
    cin >> userInput;
    switch (userInput)
    {
    case 1: {
        taskConsoleMenu();
        break;
    }
    case 2: {
        employeeConsoleMenu();
        break;
    }
    case 3: {
        reportsConsoleMenu();
        break;
    }
    case 0: {
        exit(0);

    }
    default:
        cout << "Error input" << endl;
        break;
    }
}

void Menu::reportsConsoleMenu() {
    bool workFlag = true;

    while (workFlag) {
        reportsHelp();
        int userInput;
        cin >> userInput;
        switch (userInput)
        {
        case 1: {
            Report* report = new Report();

            for (Task* task : task_mgr.get_tasks()) {
                report->addTask(*task);
            }
            report_mgr.add(report);
            break;
        }
        case 2: {
            Report* report = new Report();

            for (Task* task : task_mgr.get_tasks()) {
                time_t now;
                time(&now);
                int secondsInDay = 24 * 60 * 60;
                if (difftime(now, mktime(task->getCreationDateRaw())) <= secondsInDay) {
                    report->addTask(*task);
                }
            }

            report_mgr.add(report);
            break;
        }
        case 0: {
            for (Report* report : report_mgr.get_reports()) {
                cout << report->toString() << endl;
            }
            break;
        }
        case -1: {
            mainConsoleMenu();
            workFlag = false;
            break;
        }
        default:
            workFlag = false;
            break;
        }
    }
}

void Menu::employeeConsoleMenu() {
    bool workFlag = true;

    while (workFlag) {
        employeeHelp();
        int userInput;
        cin >> userInput;
        switch (userInput)
        {
        case 1: {
            string name;
            cout << endl << "name:";
            cin >> name;
            employee_mgr.add(new Employee(name));
            break;
        }
        case 2: {
            string name;
            cout << endl << "name:";
            cin >> name;
            for (Employee* employee : employee_mgr.get_employees()) {
                if (employee->getName() == name) {
                    string newName;
                    cout << endl << "new name:";
                    cin >> newName;
                    employee->setName(newName);
                    break;
                }
            }
            break;
        }
        case 3: {
            cout << "Input name of employee, whose leader you want to change: ";
            string name;
            cin >> name;

            Employee* e = employee_mgr.findEmployee(name);
            if (e == nullptr) {
                cout << "No such employee\n";
                break;
            }

            if (e->getBossName() == "NULL") {
                cout << "Current employee doesn't have leader\n";
            }
            else {
                cout << "Current boss of this employee: " << e->getBossName() << endl;
            }

            cout << "Input boss name: ";
            string bossName;
            cin >> bossName;

            Employee* boss = employee_mgr.findEmployee(bossName);
            if (boss == nullptr) {
                cout << "No such employee\n";
                break;
            }

            e->setBoss(boss);
            cout << "Successfuly set new boss for employee\n";
            break;
        }
        case 0: {
            for (Employee* employee : employee_mgr.get_employees()) {
                cout << employee->getName() << endl;
            }
            break;
        }
        case -1: {
            mainConsoleMenu();
            workFlag = false;
            break;
        }
        default:
            workFlag = false;
            break;
        }
    }
}

void Menu::taskConsoleMenu() {
    bool workFlag = true;

    while (workFlag) {
        taskHelp();
        int userInput;
        cin >> userInput;
        switch (userInput)
        {
        case 1: {
            int id;
            string name;
            string description;
            string employeeName;
            cout << "id:";
            cin >> id;
            cout << endl << "name:";
            cin >> name;
            cout << endl << "description:";
            cin >> description;
            cout << endl << "employee name:";
            cin >> employeeName;

            if (employee_mgr.findEmployee(employeeName)) {
                cout << "Successfuly added task\n";
                task_mgr.add(new Task(id, name, description, employeeName));
            }
            else {
                cout << "No such employee\n";
            }

            break;
        }
        case 2: {
            int id;
            cout << "id:";
            cin >> id;
            for (Task* task : task_mgr.get_tasks()) {
                if (task->getId() == id) {
                    string newName;
                    string newDescription;
                    string newEmployeeName;
                    cout << endl << "new name:";
                    cin >> newName;
                    cout << endl << "new description:";
                    cin >> newDescription;
                    cout << endl << "new employee name:";
                    cin >> newEmployeeName;

                    cout << "Successfuly changed name\n";
                    task->setName(newName);
                    cout << "Successfuly changed description\n";
                    task->setDescription(newDescription);

                    if (employee_mgr.findEmployee(newEmployeeName)) {
                        cout << "Successfully changed employee on task\n";
                        task->setEmployee(newEmployeeName);
                    }
                    else {
                        cout << "Couldn't change employee on task: no such employee\n";
                    }

                    break;
                }
            }
            break;
        }
        case 3: {
            cout << "Input creation date in format dd-mm-yy hh:mm:ss: ";
            string date;
            getline(cin, date);
            getline(cin, date);
            int d, m, y, h, mm, s;
            int res = sscanf(date.c_str(), "%d-%d-%d %d:%d:%d", &d, &m, &y, &h, &mm, &s);
            if (res == 6) {
                bool exists = false;

                for (Task* t : task_mgr.get_tasks()) {
                    if (t->getCreationDate() == date) {
                        cout << t->toString() << endl;
                        exists = true;
                    }
                }

                if (!exists) {
                    cout << "No such tasks\n";
                }
            }
            else {
                cout << "Incorrect date\n";
            }
            break;
        }
        case 4: {
            cout << "Input change date in format dd-mm-yy hh:mm:ss: ";
            string date;
            getline(cin, date);
            getline(cin, date);
            int d, m, y, h, mm, s;
            int res = sscanf(date.c_str(), "%d-%d-%d %d:%d:%d", &d, &m, &y, &h, &mm, &s);
            if (res == 6) {
                bool exists = false;

                for (Task* t : task_mgr.get_tasks()) {
                    if (t->getLastChangeDate() == date) {
                        cout << t->toString() << endl;
                        exists = true;
                    }
                }

                if (!exists) {
                    cout << "No such tasks\n";
                }
            }
            else {
                cout << "Incorrect date\n";
            }
            break;
        }
        case 5: {
            cout << "Input employee name: ";
            string name;
            cin >> name;

            if (!employee_mgr.findEmployee(name)) {
                cout << "No such employee\n";
                break;
            }

            bool exists = false;
            for (Task* t : task_mgr.get_tasks()) {
                if (t->getEmployee().getName() == name) {
                    cout << t->toString() << endl;
                    exists = true;
                }
            }

            if (!exists) {
                cout << "No such tasks\n";
            }
            break;
        }
        case 6: {
            bool exists = false;

            for (Task* t : task_mgr.get_tasks()) {
                if (t->getLastChangeDate() != "NULL") {
                    cout << t->toString() << endl;
                    exists = true;
                }
            }

            if (!exists) {
                cout << "No such tasks\n";
            }
            break;
        }
        case 7: {
            taskStatusMenu();
            break;
        }
        case 8: {
            int cnt = 1;
            for (Task* t : task_mgr.get_tasks()) {
                cout << cnt << ". " << t->toString() << endl;
                cnt++;
            }

            cout << "Input id of task, that you want to change: ";
            int id;
            cin >> id;

            Task* t = task_mgr.getTaskById(id);
            if (t == nullptr) {
                cout << "No such task\n";
                return;
            }

            cout << "Input your comment: ";
            string comm;
            cin >> comm;
            t->addComment(comm);
            cout << "Successfuly changed comment\n";
            break;
        }
        case 9: {
            cout << "Input ID of task: ";
            int id;
            cin >> id;

            Task* t = task_mgr.getTaskById(id);
            if (t == nullptr) {
                cout << "No such task\n";
            }
            else {
                cout << t->toString() << endl;
            }
            break;
        }
        case 0: {
            for (Task* task : task_mgr.get_tasks()) {
                cout << task->toString() << endl;
            }
            break;
        }
        case -1: {
            mainConsoleMenu();
            workFlag = false;
            break;
        }
        default:
            workFlag = false;
            break;
        }
    }
}

void Menu::taskStatusMenu() {
    bool workFlag = true;

    int cnt = 1;
    for (Task* t : task_mgr.get_tasks()) {
        cout << cnt << ". " << t->toString() << endl;
        cnt++;
    }

    cout << "Input id of task, that you want to change: ";
    int id;
    cin >> id;

    Task* t = task_mgr.getTaskById(id);
    if (t == nullptr) {
        cout << "No such task\n";
        return;
    }

    cout << t->toString() << endl;
    taskStatus();

    while (workFlag) {
        int userInput;
        cin >> userInput;
        switch (userInput)
        {
        case 1: {
            if (t->getStatus() == Task::TaskStatus::OPEN) {
                t->setStatus(Task::TaskStatus::ACTIVE);
                cout << "Successfuly started task\n";
            }
            else {
                cout << "Task is already started or closed\n";
            }
            workFlag = false;
            break;
        }
        case 2: {
            if (t->getStatus() == Task::TaskStatus::ACTIVE) {
                t->setStatus(Task::TaskStatus::RESOLVED);
                cout << "Successfuly ended task\n";
            }
            else {
                cout << "Task is not started or already closed\n";
            }
            workFlag = false;
            break;
        }
        case -1: {
            workFlag = false;
            break;
        }
        default: {
            workFlag = false;
            break;
        }
        }
    }
}