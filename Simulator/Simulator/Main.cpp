#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

class Transport {
public:
	int Speed = 0;

	Transport() {
		Speed = 0;
	}
	Transport(int speed) {
		Speed = speed;
	}

	int get_Speed() {
		return Speed;
	}

	void set_Speed(int speed) {
		Speed = speed;
	}

	virtual void print_name() {};

	virtual bool get_type() { return 0; };

	virtual float getTime(int distance) = 0;
};


class AirTransport : public Transport {
public:
	bool type = false; // flag, that it is an airtransport
	int DistanceReducer = 0;

	AirTransport() : Transport(0) {
		DistanceReducer = 0;
		type = false;
	}
	AirTransport(int Speed, int distancereducer) : Transport(Speed) {
		DistanceReducer = distancereducer;
		type = false;
	}

	virtual float DistanceReduced(int distance) {
		float distance_for_air = distance;
		return distance_for_air;
	}
	bool get_type() override { return type; };

	float getTime(int distance) override {
		float distance_for_air = this->DistanceReduced(distance);
		float time_to_finish = (distance_for_air / this->get_Speed());
		return time_to_finish;
	};

};

class Magic_carpet : public AirTransport {
public:
	Magic_carpet() : AirTransport(10, 0) {
	}
	void print_name() {
		cout << "magic carpet\n";
	}
	float DistanceReduced(int distance) override {
		float distance_for_air = distance;
		if (distance >= 1000 && distance < 5000)
			DistanceReducer = 3;
		if (distance >= 5000 && distance < 10000)
			DistanceReducer = 10;
		if (distance >= 10000)
			DistanceReducer = 5;
		distance_for_air *= 1 - (DistanceReducer / 100);
		return distance_for_air;
	}

};

class Stupa : public AirTransport {
public:
	Stupa() : AirTransport(8, 6) {
	}
	void print_name() {
		cout << "stupa\n";
	}
	float DistanceReduced(int distance) override {
		float distance_for_air = distance;
		DistanceReducer = 6;
		distance_for_air *= 1 - (DistanceReducer / 100);
		return distance_for_air;
	}

};

class Broomstick : public AirTransport {
public:
	Broomstick() : AirTransport(20, 1) {
	}
	void print_name() {
		cout << "broomstick\n";
	}
	float DistanceReduced(int distance) override {
		float distance_for_air = distance;
		DistanceReducer = distance % 1000;
		distance_for_air *= 1 - (DistanceReducer / 100);
		return distance_for_air;
	}

};


class GroundTransport : public Transport {
public:
	bool type = true; // flag, that it is an groundtransport
	int RestInterval = 0;
	float RestDuration = 0;
	int Num_of_durations = 0;

	GroundTransport() : Transport(0) {
		RestInterval = 0;
		RestDuration = 0;
		Num_of_durations = 0;
	}

	GroundTransport(int Speed, int RestInterval, float RestDuration) : Transport(Speed) {
		this->RestInterval = RestInterval;
		this->RestDuration = RestDuration;
		this->Num_of_durations = 0;
		this->type = true;
	}

	virtual void increment_Num_of_durations() {
		this->Num_of_durations += 1;
	}
	bool get_type() override { return type; };
	virtual float getTime(int distance) {
		int Distance_without_rest = this->get_RestInterval() * this->get_Speed();
		int num_of_rests = floor(distance / Distance_without_rest);
		float rest_duration = 0;
		for (int j = 0; j < num_of_rests; j++) {
			rest_duration += this->get_RestDuration();
			this->increment_Num_of_durations();
		}
		float time_to_finish = (distance / this->get_Speed()) + rest_duration;
		return time_to_finish;
	};
	virtual int get_RestInterval() { return RestInterval; };
	virtual int get_RestDuration() { return RestDuration; };

};

class Bactrian_camel : public GroundTransport {
public:
	Bactrian_camel() : GroundTransport(10, 30, 5) {
	}
	void increment_Num_of_durations() override {
		if (this->Num_of_durations == 0)
			this->RestDuration += 3;
		this->Num_of_durations += 1;
	}
	void print_name() {
		cout << "Bactrian camel\n";
	}
};

class Fast_moving_camel : public GroundTransport {
public:
	Fast_moving_camel() : GroundTransport(40, 10, 5) {
	}
	void increment_Num_of_durations() override {
		if (this->Num_of_durations < 2)
			this->RestDuration += 1.5;
		this->Num_of_durations += 1;
	}
	void print_name() {
		cout << "fast-moving camel\n";
	}
};

class Centaur : public GroundTransport {
public:
	Centaur() : GroundTransport(15, 8, 2) {
	}
	void increment_Num_of_durations() override {
		this->Num_of_durations += 1;
	}
	void print_name() {
		cout << "Centaur\n";
	}
};

class All_terrain_vehicle_boots : public GroundTransport {
public:
	All_terrain_vehicle_boots() : GroundTransport(6, 60, 10) {
	}
	void increment_Num_of_durations() override {
		if (this->Num_of_durations == 0)
			this->RestDuration -= 5;
		this->Num_of_durations += 1;
	}
	void print_name() {
		cout << "all-terrain vehicle boots\n";
	}
};


class race {
public:
	int distance;
	int type;
	// 0 - air race
	// 1 - earth race
	// 2 - general race

	vector<Transport*> transports;

	race(int distance, int type) {
		this->distance = distance;
		this->type = type;
	}

	void addTransport(Transport* transport)
	{
		transports.push_back(transport);
	}

	void start() {
		cout << "\nRace started!\n";
		cout << "Distance - " << distance << endl;
		cout << "Type of race (0 - air, 1 - earth, 2 - general) - " << type << endl;
		cout << "Players: " << endl;

		vector<float> times_to_finish;

		for (int i = 0; i < transports.size(); i++) {
			(*transports[i]).print_name();
			if ((*transports[i]).get_type()) {
				if (type == 0) {
					cout << "In air race there are can't be earth transport!" << endl;
					return;
				}

				float time_to_finish = (*transports[i]).getTime(distance);
				times_to_finish.push_back(time_to_finish);
			}
			else {
				if (type == 1) {
					cout << "In earth race there are can't be air transport!" << endl;
					return;
				}
				float time_to_finish = (*transports[i]).getTime(distance);
				times_to_finish.push_back(time_to_finish);
			}
		}

		int minElementIndex = min_element(times_to_finish.begin(), times_to_finish.end()) - times_to_finish.begin();
		cout << "Race winned by: ";
		transports[minElementIndex]->print_name();
	}
};


int main() {
	setlocale(LC_ALL, "rus");

	Bactrian_camel TS1;
	Fast_moving_camel TS2;
	Centaur TS3;
	All_terrain_vehicle_boots TS4;

	Magic_carpet TS5;
	Stupa TS6;
	Broomstick TS7;

	race race1 = race(10000, 1);
	race race2 = race(20000, 0);
	race race3 = race(30000, 2);
	race race4 = race(30000, 0);

	race1.addTransport(&TS1);
	race1.addTransport(&TS2);
	race1.addTransport(&TS3);
	race1.addTransport(&TS4);

	race2.addTransport(&TS5);
	race2.addTransport(&TS6);
	race2.addTransport(&TS7);

	race3.addTransport(&TS1);
	race3.addTransport(&TS2);
	race3.addTransport(&TS7);

	race4.addTransport(&TS1);
	race4.addTransport(&TS7);

	race1.start();
	race2.start();
	race3.start();
	race4.start();

	cout << "End of programm!" << endl;
	return 0;
}