#include <iostream>
#include "IniParser.h"

using namespace std;
int main() 
{

    IniParser my_iniparser;

    my_iniparser.load("../test1.ini");
    cout << my_iniparser.get<string>("COMMON", "DiskCachePath") << endl;

    return 0;
}