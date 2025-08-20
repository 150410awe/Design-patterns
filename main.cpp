#include <iostream>
#include <thread>
#include "抽象工厂.h"



using namespace std;

namespace level {
	inline const string v4 = "v4";
}

class engine_v4 : public engine {
public:
	void run() override {
		cout << "engine_v4 run" << endl;
	}

	engine_v4() = default;
	~engine_v4() = default;
};

class fuel_tank_v4 : public fuel_tank {
public:
	void come_on() override {
		cout << "fuel_tank_v4 come_on" << endl;
	}

	fuel_tank_v4() = default;
	~fuel_tank_v4() = default;
};

class transmission_v4 : public transmission {
public:
	void change_gear() override {
		cout << "transmission_v4 change_gear" << endl;
	}

	transmission_v4() = default;
	~transmission_v4() = default;
};


class car_factory_v4 : public car_factory {
public:
	unique_ptr<car> create_car() const override {
		cout << "car_factory_v4 create_car" << endl;
		return make_unique<car>(make_unique<engine_v4>(),
			make_unique<fuel_tank_v4>(),
			make_unique<transmission_v4>());
	}
	
	static car_factory_v4& get_instance() {
		static car_factory_v4 instance;
		return instance;
	}

	car_factory_v4() = default;
	~car_factory_v4() = default;
private:
	car_factory_v4(const car_factory_v4&) = delete;
	car_factory_v4(const car_factory_v4&&) = delete;

	car_factory_v4& operator=(const car_factory_v4&) = delete;
	car_factory_v4& operator=(const car_factory_v4&&) = delete;
};


int main()
{
#if 0
#include "单例模式.h"
	starving_person* ptr = starving_person::get_instance();
	thread t1([=]() {
		for (size_t i = 0; i < 100; i++) {
			ptr->data_push_back(i + 100);
			cout << i << " insert:" << i + 100 << " ID " << this_thread::get_id() << endl;
			this_thread::sleep_for(chrono::milliseconds(500));
		}
		});

	thread t2([=](){
		this_thread::sleep_for(chrono::milliseconds(1000));
		for (size_t i = 0; i < 100; i++) {
			int32_t get_data = ptr->get_data_location_data(0);
			ptr->data_erase(0);
			cout << 0 << " erase:" << get_data << " ID " << this_thread::get_id() << endl;
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
		});
	t1.join();
	t2.join();
#elif 0
	#include "简单工厂.h"
	factory* f_ptr = factory::get_instance();
	unique_ptr<person> p_ptr = f_ptr->create(10, 1, "A", race::han_ethnicity);
	p_ptr->action();

	unique_ptr<person> p_ptr2 = f_ptr->create(12, 6, "B", race::yamato_people);
	p_ptr2->action();

	unique_ptr<person> p_ptr3 = f_ptr->create(10, 1, "na na", race::catgirl_clan);
	p_ptr3->action();
#elif 0
#include "工厂模式.h"
	auto f_ptr1 = factory_manager::get_manager();
	auto f_data1 = f_ptr1->create(10, 1, "A", race::han_ethnicity);
	f_data1.get()->action();

	auto f_ptr2 = factory_manager::get_manager();
	if (f_ptr2->add_factory(race::test, &test_factory::get_instance()) == false)
		std::cout << "add_factory error" << std::endl;
	else {
		auto f_data2 = f_ptr2->create(10, 1, "A", race::test);
		f_data2.get()->action();
	}

	auto f_data3 = factory_manager::get_manager()->create(10, 1, "A", race::test);
	auto f_data4 = MANAGER_PERSON->MANAGER_PERSON->MANAGER_PERSON->MANAGER_PERSON->MANAGER_PERSON->MANAGER_PERSON->create(10, 1, "na na",race::catgirl_clan);
	f_data4.get()->action();
#elif 1
	auto fm_data1 = MANAGER_CAR.add_new_car(level::v1);
	fm_data1.get()->get_engine();
	fm_data1.get()->get_fuel_tank();
	fm_data1.get()->get_transmission();

	auto fm_data2 = MANAGER_CAR.add_new_car(level::v2);
    fm_data2.get()->get_engine();
    fm_data2.get()->get_fuel_tank();
    fm_data2.get()->get_transmission();

	MANAGER_CAR.add_new_car_level(level::v4, &car_factory_v4::get_instance());
	auto fm_data3 = MANAGER_CAR.add_new_car(level::v4);

	fm_data3.get()->get_engine();
    fm_data3.get()->get_fuel_tank();
    fm_data3.get()->get_transmission();
#endif
	return 0;
}