#include <iostream>
#include "单例模式.h"
#include <thread>
//#include "简单工厂.h"
#include "工厂模式.h"

using namespace std;


int main()
{
#if 0
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
	factory* f_ptr = factory::get_instance();
	unique_ptr<person> p_ptr = f_ptr->create(10, 1, "A", race::han_ethnicity);
	p_ptr->action();

	unique_ptr<person> p_ptr2 = f_ptr->create(12, 6, "B", race::yamato_people);
	p_ptr2->action();

	unique_ptr<person> p_ptr3 = f_ptr->create(10, 1, "na na", race::catgirl_clan);
	p_ptr3->action();
#elif 0
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


#endif
	return 0;
}