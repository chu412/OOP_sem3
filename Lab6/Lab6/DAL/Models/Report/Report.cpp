#include "Report.h"

Report::Report() {
    description = "";
}

void Report::addTask(Task task) {
    this->description += task.getName() + " - " + task.getLastChangeDate() + ",";
}

string Report::toString() {
    return description;
}