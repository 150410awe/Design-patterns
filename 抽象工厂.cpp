#include "³éÏó¹¤³§.h"
#include <iostream>

using namespace std;


void engine_v1::run() {
	cout << "engine_v1 run" << endl;
}

void engine_v2::run() {
	cout << "engine_v2 run" << endl;
}

void engine_v3::run() {
	cout << "engine_v3 run" << endl;
}


void fuel_tank_v1::come_on() {
	cout << "fuel_tank_v1 come_on" << endl;
}

void fuel_tank_v2::come_on() {
	cout << "fuel_tank_v2 come_on" << endl;
}

void fuel_tank_v3::come_on() {
	cout << "fuel_tank_v3 come_on" << endl;
}


void transmission_v1::change_gear() {
	cout << "transmission_v1 change_gear" << endl;
}

void transmission_v2::change_gear() {
	cout << "transmission_v2 change_gear" << endl;
}

void transmission_v3::change_gear() {
	cout << "transmission_v3 change_gear" << endl;
}



std::unique_ptr<car> car_factory_v1::create_car() const {
	cout << "car_factory_v1 create_car" << endl;
	return std::make_unique<car>(std::make_unique<engine_v1>(),
		std::make_unique<fuel_tank_v1>(),
		std::make_unique<transmission_v1>());
}

std::unique_ptr<car> car_factory_v2::create_car() const {
	cout << "car_factory_v2 create_car" << endl;
	return std::make_unique<car>(std::make_unique<engine_v2>(),
		std::make_unique<fuel_tank_v2>(),
		std::make_unique<transmission_v2>());
}

std::unique_ptr<car> car_factory_v3::create_car() const {
	cout << "car_factory_v3 create_car" << endl;
	return std::make_unique<car>(std::make_unique<engine_v3>(),
		std::make_unique<fuel_tank_v3>(),
		std::make_unique<transmission_v3>());
}



car_factory_v1& car_factory_v1::get_instance() {
	static car_factory_v1 instance;
	return instance;
}

car_factory_v2& car_factory_v2::get_instance() {
	static car_factory_v2 instance;
	return instance;
}


car_factory_v3& car_factory_v3::get_instance() {
	static car_factory_v3 instance;
	return instance;
}


factory_manager& factory_manager::get_instance() {
	static factory_manager instance;
	return instance;
}



const car_factory* factory_manager::find(level l_version) const {
	lock_guard<mutex> lock(revise_mutex);
	auto it = factories.find(l_version);
	return it != factories.end() ? (*it).second : nullptr;
}


bool factory_manager::add_new_car_level(level l_version, car_factory* c_version) {
	lock_guard<mutex> lock(revise_mutex);

	if (c_version == nullptr)
		return false;

	if (find(l_version) != nullptr)
		return false;


	factories.insert(std::make_pair(l_version, c_version));
	
	return true;
}


std::unique_ptr<car> factory_manager::add_new_car(level l_version) const {
	lock_guard<mutex> lock(revise_mutex);

	auto it = find(l_version);


	if (it == nullptr)
		return nullptr;

	return it->create_car();
}



factory_manager::factory_manager() {
	factories.insert(std::make_pair(level::v1, &car_factory_v1::get_instance()));
	factories.insert(std::make_pair(level::v2, &car_factory_v2::get_instance()));
	factories.insert(std::make_pair(level::v3, &car_factory_v3::get_instance()));
}
