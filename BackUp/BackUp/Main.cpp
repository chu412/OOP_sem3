#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <Windows.h>
#include <vector>
#include <ctime> 
#include <algorithm>
#include <map>
#include <iostream>
#include <experimental/filesystem>
#include <string>
#pragma warning(disable : 4996)
namespace fs = std::experimental::filesystem;
using namespace std;
struct date
{
	int Day = 1;
	int Month = 1;
	int Year = 1970;
	int Hour = 0;
	int Minute = 0;
	bool operator==(const date& b) const {
		return (Day == b.Day) && (Month == b.Month) && (Year == b.Year) && (Hour == b.Hour) && (Minute == b.Minute);
	}
	bool operator <(const date& b) const {
		return (Day < b.Day) || (Month < b.Month) || (Year < b.Year) || (Hour < b.Hour) || (Minute < b.Minute);
	}
	date date_now() {
		date date_now;
		time_t now = time(0);
		tm* ltm = localtime(&now);
		date_now.Year = 1900 + ltm->tm_year;
		date_now.Month = 1 + ltm->tm_mon;
		date_now.Day = ltm->tm_mday;
		date_now.Hour = ltm->tm_hour;
		date_now.Minute = ltm->tm_min;
		return date_now;
	}
};
struct file
{
	string path; // File location
	DWORD size; // File size in bytes
	date file_date; // Last modified date of the file
	int file_id; // file id
	//ile(static string pa, DWORD s, date p, int id) : path(pa), size(s), file_date(p), file_id(id) {}; // Constructor for passing values to class members

	bool operator< (const file& a) const {  // Overloading the comparison operator
		return file_id < a.file_id;
	}
	file file_info(string path) {
		file file_i;  // Variable of the file structure into which information about the file will be saved
		SYSTEMTIME stUTC, stLocal;  // variables for time charting (stUTC - GMT time, stLocal - local time)
		file_i.path = path;
		FILETIME date;
		HANDLE hFile = CreateFileA((LPCSTR)path.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
			cout << "Can't open file" << endl;
		file_i.size = GetFileSize(hFile, NULL);
		if (file_i.size == INVALID_FILE_SIZE)
			cout << "Can't get size" << endl;
		GetFileTime(hFile, NULL, NULL, &date);
		if (GetFileTime(hFile, NULL, NULL, &date) == NULL)
			cout << "Can't get time" << endl;
		CloseHandle(hFile);

		FileTimeToSystemTime(&date, &stUTC);
		SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

		file_i.file_date.Day = stLocal.wDay;
		file_i.file_date.Month = stLocal.wMonth;
		file_i.file_date.Year = stLocal.wYear;
		file_i.file_date.Hour = stLocal.wHour;
		file_i.file_date.Minute = stLocal.wMinute;
		return file_i;
	}
	file() {}; // Default constructor
};
class save {
public:
	string all_in_one_folder(string path, int backup_id) {
		string path_folder;
		fs::create_directories("D:\\" + to_string(backup_id) + "\\");
		path_folder = "D:\\" + to_string(backup_id) + "\\";
		string dir = "copy " + path + " " + path_folder;
		system(dir.c_str());
		return path_folder;
	};
	string folders(string path, int backup_id, date point_date) {
		string path_folder;
		path_folder = "D:\\" + to_string(backup_id) + "\\" + to_string(point_date.Year) + "-" + to_string(point_date.Month) + "-" + to_string(point_date.Day) +
			"-" + to_string(point_date.Hour) + "-" + to_string(point_date.Minute) + "\\";
		fs::create_directories(path_folder);
		string dir = "copy " + path + " " + path_folder;
		system(dir.c_str());
		return path_folder;
	};
};
class backup_main {
public:
	struct backup
	{
		int id;  // id backup
		date backup_date; // backup creation date
		DWORD size;  // Backup size in bytes
		vector <file> files; // vector backup files
	};
	vector<backup> backups;
	file file;
	date date;
	void backup_add() {
		if (backups.empty()) {
			backups.push_back(backup());
			backups[0].id = 0;
			backups[0].backup_date = date.date_now();
		}
		else {
			backups.push_back(backup());
			backups[backups.size() - 1].id = backups.size() - 1;
			backups[backups.size() - 1].backup_date = date.date_now();
		}
	}
	void new_file_add_to_backup(string path) {
		if (backups[backups.size() - 1].files.empty()) {
			backups[backups.size() - 1].files.push_back(file.file_info(path));
			backups[backups.size() - 1].files[0].file_id = 0;
			cout << "File ID: " << backups[backups.size() - 1].files[backups[backups.size() - 1].files.size() - 1].file_id
				<< " File Path: " << backups[backups.size() - 1].files[backups[backups.size() - 1].files.size() - 1].path << " add to backup." << endl;
		}
		else {
			sort(backups[backups.size() - 1].files.begin(), backups[backups.size() - 1].files.end());
			backups[backups.size() - 1].files.push_back(file.file_info(path));
			backups[backups.size() - 1].files[backups[backups.size() - 1].files.size() - 1].file_id = backups[backups.size() - 1].files.size() - 1;
			cout << "File ID: " << backups[backups.size() - 1].files[backups[backups.size() - 1].files.size() - 1].file_id
				<< " File Path: " << backups[backups.size() - 1].files[backups[backups.size() - 1].files.size() - 1].path << " add to backup." << endl;
		}

	}
	void file_add_to_backup(string path, int backup_id) {
		if (backups[backup_id].files.empty()) {
			backups[backup_id].files.push_back(file.file_info(path));
			backups[backup_id].files[0].file_id = 0;
			cout << "File ID: " << backups[backup_id].files[backups[backup_id].files.size() - 1].file_id
				<< " File Path: " << backups[backup_id].files[backups[backup_id].files.size() - 1].path << " add to backup." << endl;
		}
		else {
			sort(backups[backup_id].files.begin(), backups[backup_id].files.end());
			backups[backup_id].files.push_back(file.file_info(path));
			backups[backup_id].files[backups[backup_id].files.size() - 1].file_id = backups[backup_id].files[backups[backup_id].files.size() - 2].file_id + 1;
			cout << "File ID: " << backups[backup_id].files[backups[backup_id].files.size() - 1].file_id
				<< " File Path: " << backups[backup_id].files[backups[backup_id].files.size() - 1].path << " add to backup." << endl;
		}

	}
	void delete_file_from_backup(int backup_id, int file_id) {
		for (auto i = 0; i < backups[backup_id].files.size(); i++) {
			if (backups[backup_id].files[i].file_id == file_id) {
				backups[backup_id].files.erase(backups[backup_id].files.begin() + i);
			}
		}

	}
	void show_backups() {
		for (auto i = 0; i < backups.size(); i++) {
			cout << "Files in backup with ID: " << i << endl;
			for (auto j = 0; j < backups[i].files.size(); j++) {
				cout << "File " << j << " file ID: " << backups[i].files[j].file_id << " file path: " << backups[i].files[j].path << endl;
			}
		}
	}
	void backup_update_size(DWORD RP_size, int backup_id) {
		backups[backup_id].size += RP_size;
	}


};
class restore_point {
public:
	restore_point() {};
	struct res_point
	{
		date restore_date; // Date when need to create a restore point
		string path = "No path";   // Path where to create a restore point
		vector <file> rp_files;  // Files contained in the restore point
		int RP_size = 0;
		int RP_type = 0;
	};
	vector<date> restore_points_dates;
	date last_date_in_rp;
	void last_date(date last_entered_date) {
		if (last_date_in_rp < last_entered_date) {
			last_date_in_rp = last_entered_date;
		}
	}
	void create_restore_point(date restorpoint_date) {
		if (restore_points_dates.empty()) {
			restore_points_dates.push_back(date());
			restore_points_dates[0] = restorpoint_date;
		}
		else {
			restore_points_dates.push_back(date());
			restore_points_dates[restore_points_dates.size() - 1] = restorpoint_date;
		}

	}
};
class restore_point_full : restore_point, save {
public:
	vector<date>* full_points_date;
	vector<res_point> full_points_ready;
	file file2;
	date date2;
	res_point res_point2;
	map<int, vector<res_point>> full_points_backup;
	restore_point_full(vector<date>* restore_points_dates) {
		full_points_date = *&restore_points_dates;
	}
	restore_point_full() {};
	DWORD create_full_point(int backup_id, vector<file> path) {
		for (auto j = 0; j < (*full_points_date).size(); j++) {
			if (date2.date_now() == (*full_points_date)[j]) {
				res_point2.restore_date = (*full_points_date)[j];
				full_points_ready.push_back(res_point2);
				full_points_ready[full_points_ready.size() - 1].rp_files = path;
				for (auto i = 0; i < path.size(); i++) {
					full_points_ready[full_points_ready.size() - 1].RP_size += file2.file_info(path[i].path).size;
					//save::all_in_one_folder(path[i].path, backup_id);
					save::folders(path[i].path, backup_id, full_points_ready[full_points_ready.size() - 1].restore_date);

				}
				if (full_points_backup.count(backup_id) == 0) {
					full_points_backup.insert(make_pair(backup_id, full_points_ready));

				}
				else {
					full_points_backup[backup_id] = full_points_ready;
				}
				return full_points_ready[full_points_ready.size() - 1].RP_size;


			}

		}

		return 0;

	};
};
class restore_point_incr : restore_point {
public:
	vector<date>* incr_points_dates;
	vector<res_point> incr_points_ready;
	file file2;
	date date2;
	res_point res_point2;
	map<int, vector<res_point>> incr_points_backup;
	restore_point_incr(vector<date>* restore_points_dates) {
		incr_points_dates = *&restore_points_dates;
	}
	restore_point_incr() {};
	DWORD create_incr_point(int backup_id, vector<file> path) {
		for (auto j = 0; j < (*incr_points_dates).size(); j++) {
			if ((date2.date_now() == ((*incr_points_dates)[j])) && (incr_points_backup.count(backup_id) == 0)) {
				res_point2.restore_date = (*incr_points_dates)[j];
				incr_points_ready.push_back(res_point2);
				incr_points_ready[incr_points_ready.size() - 1].rp_files = path;
				incr_points_ready[incr_points_ready.size() - 1].RP_type = 1;
				for (auto i = 0; i < path.size(); i++) {
					incr_points_ready[incr_points_ready.size() - 1].RP_size += file2.file_info(path[i].path).size;
				}
				incr_points_backup.insert(make_pair(backup_id, incr_points_ready));
				return incr_points_ready[incr_points_ready.size() - 1].RP_size;

			}
			else if ((date2.date_now()) == ((*incr_points_dates)[j])) {
				vector<file> temp;
				res_point2.restore_date = (*incr_points_dates)[j];
				incr_points_ready.push_back(res_point2);
				long int point_id = incr_points_ready.size() - 1;
				incr_points_ready[point_id].RP_type = 1;
				for (int i = 1; i < incr_points_ready.size(); i++) {
					if (temp.empty()) {
						for (int j = 0; j < incr_points_ready[point_id - i].rp_files.size(); j++) {
							temp.push_back(incr_points_ready[point_id - i].rp_files[j]);
						}

					}
					else if (temp.size() != path.size())
					{
						for (j = 0; j < incr_points_ready[point_id - i].rp_files.size() - 1; j++) {
							if (find_path_in_vector(temp, incr_points_ready[point_id - i].rp_files[j].path) == false) {
								temp.push_back(incr_points_ready[point_id - i].rp_files[j]);
							}

						}
					}

				}
				sort(temp.begin(), temp.end());
				for (int k = 0; k < temp.size(); k++) {
					if (temp[k].file_date < file2.file_info(path[k].path).file_date) {
						incr_points_ready[point_id].rp_files.push_back(file2.file_info(path[k].path));
						incr_points_ready[point_id].RP_size += file2.file_info(path[k].path).size;
					}
				}
				incr_points_backup[backup_id] = incr_points_ready;
				return incr_points_ready[incr_points_ready.size() - 1].RP_size;
			}

		}

		return 0;

	};
	bool find_path_in_vector(vector<file> temp, string path) {
		for (int i = 0; i < temp.size() - 1; i++) {
			if (temp[i].path == path) {
				return true;
			}
		}
		return false;

	};
};
class clear_points {
public:
	clear_points() {};

	int clear_point_size(backup_main::backup backup, map<int, vector<restore_point::res_point>> points_backup, int size) {
		int counter = 0;
		while (backup.size > size) {
			if ((points_backup[backup.id].size() == 1) && (points_backup[backup.id][0].RP_type == 1)) {
				cout << "Can't delete last incrimental point !" << endl;
				return counter;
			}
			else
			{
				points_backup[backup.id].erase(points_backup[backup.id].begin());
				backup.size = backup_size_update(backup, points_backup);
				counter++;
			}

		}
		return counter;
	}
	bool clear_point_date(size_t size, restore_point::res_point points_backup, date date) {
		if (points_backup.restore_date < date) {
			cout << "Point date: " << points_backup.restore_date.Day
				<< "." << points_backup.restore_date.Month
				<< "." << points_backup.restore_date.Year
				<< " " << points_backup.restore_date.Hour
				<< ":" << points_backup.restore_date.Minute
				<< " was deleted from backup !" << endl;
			return true;
		}
		else if ((points_backup.RP_type == 1) && (size == 1)) {
			cout << "Can't delete last incrimental point !" << endl;
			return false;
		}
		return false;
	}
	int clear_point_amount(backup_main::backup backup, map<int, vector<restore_point::res_point>> points_backup, int amount) {
		int counter = 0;
		while (points_backup[backup.id].size() > amount) {
			if ((points_backup[backup.id].size() == 1) && (points_backup[backup.id][0].RP_type == 1)) {
				return counter;
			}
			else
			{
				points_backup[backup.id].erase(points_backup[backup.id].begin());
				backup.size = backup_size_update(backup, points_backup);
				counter++;
			}
		}
		return counter;
	}
	date enter_date() {
		date date;
		cout << "Enter the date before which to delete" << endl;
		cout << "Enter year: "; // time is entered in 24-hour format
		cin >> date.Year;
		cout << "Enter month: ";
		cin >> date.Month;
		cout << "Enter day: ";
		cin >> date.Day;
		cout << "Enter hour: ";
		cin >> date.Hour;
		cout << "Enter minute: ";
		cin >> date.Minute;
		return date;
	}
	void del_points_rul(vector<backup_main::backup>* backup1, map<int, vector<restore_point::res_point>>* points_backup1) {
		vector<backup_main::backup> backups = *backup1;
		map<int, vector<restore_point::res_point>> points_backup = *points_backup1;
		int switch_on;
		cout << "-----------------------" << endl
			<< "          Menu         " << endl
			<< "-----------------------" << endl
			<< "Del by date - 0" << endl
			<< "Del by size - 1" << endl
			<< "Del by amount - 2" << endl
			<< "Comby del - 3" << endl;
		cin >> switch_on;
		date date_1;
		int size;
		int amount;
		int counter_1 = 0;
		int counter_2 = 0;
		switch (switch_on)
		{
		case 0:
			date_1 = enter_date();
			for (int i = 0; i < backups.size(); i++) {
				cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
				for (int j = 0; j < points_backup[i].size(); j++) {
					points_backup[i].erase(remove_if(points_backup[i].begin(), points_backup[i].end(), [this, &date_1, &points_backup, &i](auto& element) {return clear_point_date(points_backup[i].size(), element, date_1); }), points_backup[i].end());
					backups[i].size = backup_size_update(backups[i], points_backup);
				}
				cout << "New backup size: " << backups[i].size << endl;
			}
			*backup1 = backups;
			*points_backup1 = points_backup;
			break;
		case 1:
			cout << "Enter max size of backups in bytes: ";
			cin >> size;
			for (int i = 0; i < backups.size(); i++) {
				cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
				while (backups[i].size > size) {
					if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
						cout << "Can't delete last incrimental point !" << endl;
						break;
					}
					else
					{
						cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
						points_backup[i].erase(points_backup[i].begin());
						backups[i].size = backup_size_update(backups[i], points_backup);
					}

				}
				cout << "New backup size: " << backups[i].size << endl;
			}
			*backup1 = backups;
			*points_backup1 = points_backup;
			break;
		case 2:
			cout << "Enter max points in backups: ";
			cin >> amount;
			for (int i = 0; i < backups.size(); i++) {
				cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
				while (points_backup[i].size() > amount) {
					if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
						cout << "Can't delete last incrimental point !" << endl;
						break;
					}
					else
					{
						cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
						points_backup[i].erase(points_backup[i].begin());
						backups[i].size = backup_size_update(backups[i], points_backup);
					}

				}
				cout << "New backup size: " << backups[i].size << endl;
			}
			*backup1 = backups;
			*points_backup1 = points_backup;
			break;
		case 3:
			cout << "-----------------------" << endl
				<< "          Menu         " << endl
				<< "-----------------------" << endl
				<< "Del by date & size - 0" << endl
				<< "Del by date & amount - 1" << endl
				<< "Del by amount & size - 2" << endl
				<< "Del by date | size - 3" << endl
				<< "Del by amount | date - 4" << endl
				<< "Del by amount | size - 5" << endl;
			cin >> switch_on;

			switch (switch_on)
			{
			case 0:
				date_1 = enter_date();
				cout << "Enter max size of backups in bytes: ";
				cin >> size;
				for (int i = 0; i < backups.size(); i++) {
					for (int j = 0; j < points_backup[i].size(); j++) {
						if (clear_point_date(points_backup[i].size(), points_backup[i][j], date_1)) {
							counter_1++;
						}
					}
					counter_2 = clear_point_size(backups[i], points_backup, size);
					if ((counter_1 > 0) && (counter_2 > 0)) {
						int choise = 0;
						cout << "del by max or min" << endl;
						cout << "max - 1" << endl;
						cout << "min - 2" << endl;
						cin >> choise;
						if (choise == 1) {
							if (counter_1 > counter_2) {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									for (int j = 0; j < points_backup[i].size(); j++) {
										points_backup[i].erase(remove_if(points_backup[i].begin(), points_backup[i].end(), [this, &date_1, &points_backup, &i](auto& element) {return clear_point_date(points_backup[i].size(), element, date_1); }), points_backup[i].end());
										backups[i].size = backup_size_update(backups[i], points_backup);
									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
							else {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (backups[i].size > size) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
						}
						else {
							if (counter_1 < counter_2) {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									for (int j = 0; j < points_backup[i].size(); j++) {
										points_backup[i].erase(remove_if(points_backup[i].begin(), points_backup[i].end(), [this, &date_1, &points_backup, &i](auto& element) {return clear_point_date(points_backup[i].size(), element, date_1); }), points_backup[i].end());
										backups[i].size = backup_size_update(backups[i], points_backup);
									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
							else {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (backups[i].size > size) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
						}
					}
				}
				break;
			case 1:
				date_1 = enter_date();
				cout << "Enter max points in backups: ";
				cin >> amount;
				for (int i = 0; i < backups.size(); i++) {
					for (int j = 0; j < points_backup[i].size(); j++) {
						if (clear_point_date(points_backup[i].size(), points_backup[i][j], date_1)) {
							counter_1++;
						}
					}
					counter_2 = clear_point_amount(backups[i], points_backup, amount);
					if ((counter_1 > 0) && (counter_2 > 0)) {
						int choise = 0;
						cout << "del by max or min" << endl;
						cout << "max - 1" << endl;
						cout << "min - 2" << endl;
						cin >> choise;
						if (choise == 1) {
							if (counter_1 > counter_2) {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									for (int j = 0; j < points_backup[i].size(); j++) {
										points_backup[i].erase(remove_if(points_backup[i].begin(), points_backup[i].end(), [this, &date_1, &points_backup, &i](auto& element) {return clear_point_date(points_backup[i].size(), element, date_1); }), points_backup[i].end());
										backups[i].size = backup_size_update(backups[i], points_backup);
									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
							else {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (points_backup[i].size() > amount) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
						}
						else {
							if (counter_1 < counter_2) {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									for (int j = 0; j < points_backup[i].size(); j++) {
										points_backup[i].erase(remove_if(points_backup[i].begin(), points_backup[i].end(), [this, &date_1, &points_backup, &i](auto& element) {return clear_point_date(points_backup[i].size(), element, date_1); }), points_backup[i].end());
										backups[i].size = backup_size_update(backups[i], points_backup);
									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
							else {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (points_backup[i].size() > amount) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
						}
					}
				}
				break;
			case 2:
				cout << "Enter max points in backups: ";
				cin >> amount;
				cout << "Enter max size of backups in bytes: ";
				cin >> size;
				for (int i = 0; i < backups.size(); i++) {
					counter_1 = clear_point_size(backups[i], points_backup, size);
					counter_2 = clear_point_amount(backups[i], points_backup, amount);
					if ((counter_1 > 0) && (counter_2 > 0)) {
						int choise = 0;
						cout << "del by max or min" << endl;
						cout << "max - 1" << endl;
						cout << "min - 2" << endl;
						cin >> choise;
						if (choise == 1) {
							if (counter_1 > counter_2) {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (backups[i].size > size) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
							else {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (points_backup[i].size() > amount) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
						}
						else {
							if (counter_1 < counter_2) {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (backups[i].size > size) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
							else {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (points_backup[i].size() > amount) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
						}
					}
				}
				break;
			case 3:
				date_1 = enter_date();
				cout << "Enter max size of backups in bytes: ";
				cin >> size;
				for (int i = 0; i < backups.size(); i++) {
					for (int j = 0; j < points_backup[i].size(); j++) {
						if (clear_point_date(points_backup[i].size(), points_backup[i][j], date_1)) {
							counter_1++;
						}
					}
					counter_2 = clear_point_size(backups[i], points_backup, size);
					if ((counter_1 > 0) || (counter_2 > 0)) {
						int choise = 0;
						cout << "del by max or min" << endl;
						cout << "max - 1" << endl;
						cout << "min - 2" << endl;
						cin >> choise;
						if (choise == 1) {
							if (counter_1 > counter_2) {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									for (int j = 0; j < points_backup[i].size(); j++) {
										points_backup[i].erase(remove_if(points_backup[i].begin(), points_backup[i].end(), [this, &date_1, &points_backup, &i](auto& element) {return clear_point_date(points_backup[i].size(), element, date_1); }), points_backup[i].end());
										backups[i].size = backup_size_update(backups[i], points_backup);
									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
							else {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (backups[i].size > size) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
						}
						else {
							if (counter_1 < counter_2) {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									for (int j = 0; j < points_backup[i].size(); j++) {
										points_backup[i].erase(remove_if(points_backup[i].begin(), points_backup[i].end(), [this, &date_1, &points_backup, &i](auto& element) {return clear_point_date(points_backup[i].size(), element, date_1); }), points_backup[i].end());
										backups[i].size = backup_size_update(backups[i], points_backup);
									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
							else {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (backups[i].size > size) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
						}
					}
				}
				break;
			case 4:
				date_1 = enter_date();
				cout << "Enter max points in backups: ";
				cin >> amount;
				for (int i = 0; i < backups.size(); i++) {
					for (int j = 0; j < points_backup[i].size(); j++) {
						if (clear_point_date(points_backup[i].size(), points_backup[i][j], date_1)) {
							counter_1++;
						}
					}
					counter_2 = clear_point_amount(backups[i], points_backup, amount);
					if ((counter_1 > 0) || (counter_2 > 0)) {
						int choise = 0;
						cout << "del by max or min" << endl;
						cout << "max - 1" << endl;
						cout << "min - 2" << endl;
						cin >> choise;
						if (choise == 1) {
							if (counter_1 > counter_2) {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									for (int j = 0; j < points_backup[i].size(); j++) {
										points_backup[i].erase(remove_if(points_backup[i].begin(), points_backup[i].end(), [this, &date_1, &points_backup, &i](auto& element) {return clear_point_date(points_backup[i].size(), element, date_1); }), points_backup[i].end());
										backups[i].size = backup_size_update(backups[i], points_backup);
									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
							else {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (points_backup[i].size() > amount) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
						}
						else {
							if (counter_1 < counter_2) {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									for (int j = 0; j < points_backup[i].size(); j++) {
										points_backup[i].erase(remove_if(points_backup[i].begin(), points_backup[i].end(), [this, &date_1, &points_backup, &i](auto& element) {return clear_point_date(points_backup[i].size(), element, date_1); }), points_backup[i].end());
										backups[i].size = backup_size_update(backups[i], points_backup);
									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
							else {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (points_backup[i].size() > amount) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
						}
					}
				}
				break;
			case 5:
				cout << "Enter max points in backups: ";
				cin >> amount;
				cout << "Enter max size of backups in bytes: ";
				cin >> size;
				for (int i = 0; i < backups.size(); i++) {
					counter_1 = clear_point_size(backups[i], points_backup, size);
					counter_2 = clear_point_amount(backups[i], points_backup, amount);
					if ((counter_1 > 0) || (counter_2 > 0)) {
						int choise = 0;
						cout << "del by max or min" << endl;
						cout << "max - 1" << endl;
						cout << "min - 2" << endl;
						cin >> choise;
						if (choise == 1) {
							if (counter_1 > counter_2) {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (backups[i].size > size) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
							else {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (points_backup[i].size() > amount) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
						}
						else {
							if (counter_1 < counter_2) {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (backups[i].size > size) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
							else {
								for (int i = 0; i < backups.size(); i++) {
									cout << "Backup ID: " << backups[i].id << " Backup old size: " << backups[i].size << endl;
									while (points_backup[i].size() > amount) {
										if ((points_backup[i].size() == 1) && (points_backup[i][0].RP_type == 1)) {
											cout << "Can't delete last incrimental point !" << endl;
										}
										else
										{
											cout << "Point size: " << points_backup[i][0].RP_size << " was deleted from backup !" << endl;
											points_backup[i].erase(points_backup[i].begin());
											backups[i].size = backup_size_update(backups[i], points_backup);
										}

									}
									cout << "New backup size: " << backups[i].size << endl;
								}
								*backup1 = backups;
								*points_backup1 = points_backup;
							}
						}
					}
				}
				break;
			default:
				cout << "Choise number from menu!" << endl;
				break;
			}
			break;
		default:
			cout << "Choise number from menu!" << endl;
			break;
		}





	}
	int backup_size_update(backup_main::backup backup, map<int, vector<restore_point::res_point>> points_backup) {
		backup.size = 0;
		for (int i = 0; i < points_backup[backup.id].size(); i++) {
			backup.size += points_backup[backup.id][i].RP_size;
		}
		return backup.size;
	}
};


int main()
{
	backup_main backup_main_incr;
	backup_main backup_main_full;
	clear_points clear_points;
	restore_point restore_point;
	restore_point_full restore_point_full(&restore_point.restore_points_dates);
	restore_point_incr restore_point_incr(&restore_point.restore_points_dates);
	while (true) {
		string path;
		int backup_id = 0;
		int switch_on = 0;
		int file_id = 0;
		date test;
		bool exit = true;
		date date;
		cout << "-----------------------" << endl
			<< "          Menu         " << endl
			<< "-----------------------" << endl
			<< "Create backup - 0" << endl // creating a backu
			<< "Start program - 1" << endl // Starting the work of the program for working out points
			<< "Edit backup - 2" << endl
			<< "Restore point edit - 3" << endl
			<< "Create restore point - 4" << endl;
		date.date_now();
		cin >> switch_on;
		switch (switch_on)
		{
		case 0:
			backup_main_full.backup_add();
			backup_main_incr.backup_add();
			while (true) {
				cout << "---------------" << endl
					<< "Add new file ?" << endl
					<< "---------------" << endl
					<< "Yes - 0" << endl
					<< "No - 1" << endl;
				cin >> switch_on;
				switch (switch_on)
				{
				case 0:
					cout << "Enter path to file: ";
					cin >> path;
					backup_main_full.new_file_add_to_backup(path);
					backup_main_incr.new_file_add_to_backup(path);
					break;
				case 1:
					exit = false;
					break;
				default:
					cout << "Choise number from menu!" << endl;
					break;
				}
				if (!exit) {
					break;
				}
			}
			break;
		case 1:

			while (true) {

				for (auto i = 0; i < backup_main_full.backups.size(); i++) {
					backup_main_full.backups[i].size += restore_point_full.create_full_point(i, backup_main_full.backups[i].files);
				}
				for (auto i = 0; i < backup_main_incr.backups.size(); i++) {
					backup_main_incr.backups[i].size += restore_point_incr.create_incr_point(i, backup_main_incr.backups[i].files);
				}
				if (restore_point.last_date_in_rp < date.date_now()) {
					break;
				}
				Sleep(60000);
			}

			break;
		case 2:
			while (true) {
				backup_main_incr.show_backups();
				cout << "-------------------------------" << endl
					<< "Delete or add file to backup ?" << endl
					<< "-------------------------------" << endl
					<< "Delete - 1" << endl
					<< "Add - 2" << endl
					<< "No - 3" << endl;
				cin >> switch_on;
				switch (switch_on) {
				case 1:
					cout << "Enter backup ID to delete file: ";
					cin >> backup_id;
					cout << "Enter file ID to del: ";
					cin >> file_id;
					backup_main_incr.delete_file_from_backup(backup_id, file_id);
					backup_main_full.delete_file_from_backup(backup_id, file_id);
					break;
				case 2:
					cout << "Enter backup ID to add file: ";
					cin >> backup_id;
					cout << "Enter path to file: ";
					cin >> path;
					backup_main_incr.file_add_to_backup(path, backup_id);
					backup_main_full.file_add_to_backup(path, backup_id);
					break;
				case 3:
					exit = false;
					break;
				default:
					cout << "Choise number from menu!" << endl;
					break;
				}
				break;
			}
		case 3:
			clear_points.del_points_rul(&backup_main_full.backups, &restore_point_full.full_points_backup);
			clear_points.del_points_rul(&backup_main_incr.backups, &restore_point_incr.incr_points_backup);
			break;
		case 4:
			while (true) {
				cout << "------------------------" << endl
					<< "Add new restore point ?" << endl
					<< "------------------------" << endl
					<< "Yes - 1" << endl
					<< "No - 2" << endl;
				cin >> switch_on;
				switch (switch_on)
				{
				case 1:
					cout << "Enter year: "; // time is entered in 24-hour format
					cin >> date.Year;
					cout << "Enter month: ";
					cin >> date.Month;
					cout << "Enter day: ";
					cin >> date.Day;
					cout << "Enter hour: ";
					cin >> date.Hour;
					cout << "Enter minute: ";
					cin >> date.Minute;
					restore_point.last_date(date);
					restore_point.create_restore_point(date);
					break;
				case 2:
					exit = false;
					break;
				default:
					cout << "Choise number from menu!" << endl;
					break;
				}
				if (!exit) {
					break;
				}
			}
		default:
			cout << "Choise number from menu!" << endl;
			break;
		}
	}
};