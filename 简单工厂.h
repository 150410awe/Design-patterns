#pragma once
#include <cstdint>
#include <string>
#include <iostream>
#include <memory>


enum class race : int8_t {
	han_ethnicity,
	yamato_people,
	korean,
	catgirl_clan
};

class person {
public:
	person(const uint8_t gender, const uint8_t age, const std::string& name)
		: gender(gender), age(age), name(name) {
	}
	uint8_t get_gender() const {
		return gender;
	}
	uint8_t get_age() const {
		return age;
	}
	const std::string& get_name() const {
		return name;
	}
	virtual void action() = 0;
	~person() = default;
private:
	uint8_t gender;
	uint8_t age;
	std::string name;
};


class han_ethnicity : public person{
public:
	han_ethnicity(const uint8_t gender, const uint8_t age, const std::string& name)
		: person(gender, age, name) {
	}
	void action() override {
		std::cout << "I'm a han ethnicity" << std::endl;
	}
};


class yamato_people : public person {
public:
    yamato_people(const uint8_t gender, const uint8_t age, const std::string& name)
		: person(gender, age, name) {
	}
	void action() override {
		std::cout << "I'm a yamato people" << std::endl;
	}
};

class korean : public person {
public:
	korean(const uint8_t gender, const uint8_t age, const std::string& name)
		: person(gender, age, name) {
	}
	void action() override {
		std::cout << "I'm a korean" << std::endl;
	}
};


class catgirl_clan : public person {
public:
	catgirl_clan(const uint8_t gender, const uint8_t age, const std::string& name)
		: person(gender, age, name) {
	}
	void action() override {
		std::cout << "喵喵喵~ \t // 喵喵不会说人话喵" << std::endl;
	}
};


class factory {
public:
	std::unique_ptr<person> create(uint8_t gender, uint8_t age, std::string name, race type) {
		switch (type) {
		case race::catgirl_clan:
			return std::make_unique<catgirl_clan>(gender, age, name);
		case race::han_ethnicity:
			return std::make_unique<han_ethnicity>(gender, age, name);
		case race::korean:
			return std::make_unique<korean>(gender, age, name);
		case race::yamato_people:
			return std::make_unique<yamato_people>(gender, age, name);
		}
	}
	static factory* get_instance() {
		return instance;
	}
private:
	factory() = default;
	~factory() = delete;

	factory(const factory&) = delete;
	factory(factory&&) = delete;

	factory& operator=(const factory&) = delete;
	factory& operator=(factory&&) = delete;

	static factory* instance;
};

factory* factory::instance = new factory();