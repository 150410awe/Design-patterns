#pragma once
#include <cstdint>
#include <mutex>
#include <memory>
#include <unordered_map>



enum class level {
	v1,
	v2,
	v3
};



class engine {
public:
	virtual void run() = 0;

	engine() = default;
	virtual ~engine() = default;
};



class engine_v1 : public engine {
public:
	void run() override;

	engine_v1() = default;
	~engine_v1() = default;
};

class engine_v2 : public engine {
public:
	void run() override;

	engine_v2() = default;
	~engine_v2() = default;
};

class engine_v3 : public engine {
public:
	void run() override;

	engine_v3() = default;
	~engine_v3() = default;
private:
};






class fuel_tank {
public:
	virtual void come_on() = 0;

	fuel_tank() = default;
	virtual ~fuel_tank() = default;
};




class fuel_tank_v1 : public fuel_tank {
public:
	void come_on() override;

	fuel_tank_v1() = default;
	~fuel_tank_v1() = default;
};

class fuel_tank_v2 : public fuel_tank {
public:
	void come_on() override;

	fuel_tank_v2() = default;
	~fuel_tank_v2() = default;
};

class fuel_tank_v3 : public fuel_tank {
public:
	void come_on() override;

	fuel_tank_v3() = default;
	~fuel_tank_v3() = default;
};





class transmission {
public:
	virtual void change_gear() = 0;

	transmission() = default;
	virtual ~transmission() = default;
};



class transmission_v1 : public transmission {
public:
	void change_gear() override;

	transmission_v1() = default;
	~transmission_v1() = default;
};

class transmission_v2 : public transmission {
public:
	void change_gear() override;

	transmission_v2() = default;
	~transmission_v2() = default;
};

class transmission_v3 : public transmission {
public:
	void change_gear() override;

	transmission_v3() = default;
	~transmission_v3() = default;
};




class car {
public:
	car(std::unique_ptr<engine>&& engine,
		std::unique_ptr<fuel_tank>&& fuel_tank,
		std::unique_ptr<transmission>&& transmission) : 
		engine_v(std::move(engine)),
		fuel_tank_v(std::move(fuel_tank)),
		transmission_v(std::move(transmission))	{
	}

	
	void get_engine() const{
		engine_v->run();
	}
	void get_fuel_tank() const{
		fuel_tank_v->come_on();
	}
	void get_transmission() const{
		transmission_v->change_gear();
	}
	

	//有智能指针，不用自己在写了
	~car() = default;
private:
	std::unique_ptr<engine> engine_v;
	std::unique_ptr<fuel_tank> fuel_tank_v;
	std::unique_ptr<transmission> transmission_v;
};




class car_factory {
public:
	virtual std::unique_ptr<car> create_car() const = 0;

	car_factory() = default;
	~car_factory() = default;
private:
	car_factory(const car_factory&) = delete;
	car_factory(const car_factory&&) = delete;
	
	car_factory& operator=(const car_factory&) = delete;
	car_factory& operator=(const car_factory&&) = delete;
};



class car_factory_v1 : public car_factory {
public:
	std::unique_ptr<car> create_car() const override;

	static car_factory_v1& get_instance();

	car_factory_v1() = default;
	~car_factory_v1() = default;
private:
	car_factory_v1(const car_factory_v1&) = delete;
	car_factory_v1(const car_factory_v1&&) = delete;

	car_factory_v1& operator=(const car_factory_v1&) = delete;
	car_factory_v1& operator=(const car_factory_v1&&) = delete;
};

class car_factory_v2 : public car_factory {
public:
	std::unique_ptr<car> create_car() const override;

	static car_factory_v2& get_instance();

	car_factory_v2() = default;
	~car_factory_v2() = default;
private:
	car_factory_v2(const car_factory_v2&) = delete;
	car_factory_v2(const car_factory_v2&&) = delete;

	car_factory_v2& operator=(const car_factory_v2&) = delete;
	car_factory_v2& operator=(const car_factory_v2&&) = delete;
};

class car_factory_v3 : public car_factory {
public:
	std::unique_ptr<car> create_car() const override;

	static car_factory_v3& get_instance();

	car_factory_v3() = default;
	~car_factory_v3() = default;
private:
	car_factory_v3(const car_factory_v3&) = delete;
	car_factory_v3(const car_factory_v3&&) = delete;

	car_factory_v3& operator=(const car_factory_v3&) = delete;
	car_factory_v3& operator=(const car_factory_v3&&) = delete;
};




class factory_manager {
public:
	const car_factory* find(level l_version) const;

	std::unique_ptr<car> add_new_car(level l_version) const;

	bool add_new_car_level(level l_version, car_factory* c_version);

	static factory_manager& get_instance();

private:
	factory_manager();
	~factory_manager() = default;

	factory_manager(const factory_manager&) = delete;
	factory_manager(const factory_manager&&) = delete;

	factory_manager& operator=(const factory_manager&) = delete;
	factory_manager& operator=(const factory_manager&&) = delete;

	std::unordered_map<level, car_factory*> factories;
	mutable std::mutex revise_mutex;
};


#define MANAGER_CAR factory_manager::get_instance()