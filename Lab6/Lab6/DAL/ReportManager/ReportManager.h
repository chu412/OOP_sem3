#ifndef ReportManager_H
#define ReportManager_H
#include <vector>
#include "../Models/Report/Report.h"
using namespace std;

class ReportManager {
public:
    ReportManager();
    vector <Report*> get_reports();
    void add(Report* a);

private:
    vector <Report*> reports;
};
#endif // !ReportManager_H
