#include "./ReportManager.h"

ReportManager::ReportManager() {
    this->reports.resize(0);
}

vector <Report*> ReportManager::get_reports() {
    return this->reports;
}

void ReportManager::add(Report* a) {
    this->reports.push_back(a);
}