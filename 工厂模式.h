#pragma once
#include <cstdint>
#include <string>
#include <iostream>
#include <memory>
//#include <vector>
#include <map>
#include <unordered_map>
//#include "race.h"


//不好扩展
//使用单独文件
//假设race在race.h中定义
enum class race : int8_t {
	han_ethnicity,
	yamato_people,
	korean,
	catgirl_clan,
	test
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


class han_ethnicity : public person {
public:
	han_ethnicity(const uint8_t gender, const uint8_t age, const std::string& name)
		: person(gender, age, name) {
	}
	void action() override {
		std::cout << "I'm a han ethnicity" << std::endl;
	}
	~han_ethnicity() {
		std::cout << "~han_ethnicity" << std::endl;
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
	~yamato_people() {
		std::cout << "~yamato_people" << std::endl;
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
	~korean() {
		std::cout << "~korean" << std::endl;
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
	~catgirl_clan() {
		std::cout << "~catgirl_clan" << std::endl;
	}
};


class factor {
public:
	factor() = default;
	~factor() = default;

	
	virtual std::unique_ptr<person> create(uint8_t gender, uint8_t age, std::string name) const = 0;
private:

	factor(const factor&) = delete;
	factor(factor&&) = delete;

	factor& operator=(const factor&) = delete;
	factor& operator=(factor&&) = delete;
};


/*
* 后面工厂越来越多,都写一个智能指针太麻烦了,正好都是继承factor不可以就用一个指针智能切换对应使用的工厂呢,模板工厂是不是更好的选择
* 如果后面要改,那也太傻逼了
*/


class han_ethnicity_factory : public factor {
public:
	han_ethnicity_factory() = default;
	~han_ethnicity_factory() = default;

	
	std::unique_ptr<person> create(uint8_t gender, uint8_t age, std::string name) const override {
		return std::make_unique<han_ethnicity>(gender, age, name);
	}
	


	static han_ethnicity_factory& get_instance() {
		static han_ethnicity_factory instance;
		return instance;
	}

private:
	han_ethnicity_factory(const han_ethnicity_factory&) = delete;
	han_ethnicity_factory(han_ethnicity_factory&&) = delete;

	han_ethnicity_factory& operator=(const han_ethnicity_factory&) = delete;
	han_ethnicity_factory& operator=(han_ethnicity_factory&&) = delete;
};

class yamato_people_factory : public factor {
public:
	yamato_people_factory() = default;
	~yamato_people_factory() = default;

	
	std::unique_ptr<person> create(uint8_t gender, uint8_t age, std::string name) const override {
		return std::make_unique<yamato_people>(gender, age, name);
	}
	

	static yamato_people_factory& get_instance() {
		static yamato_people_factory instance;
		return instance;
	}
private:
	yamato_people_factory(const yamato_people_factory&) = delete;
	yamato_people_factory(yamato_people_factory&&) = delete;

	yamato_people_factory& operator=(const yamato_people_factory&) = delete;
	yamato_people_factory& operator=(yamato_people_factory&&) = delete;
};


class korean_factory : public factor {
public:
	korean_factory() = default;
	~korean_factory() = default;

	
	std::unique_ptr<person> create(uint8_t gender, uint8_t age, std::string name) const override {
		return std::make_unique<korean>(gender, age, name);
	}
	

	static korean_factory& get_instance() {
		static korean_factory instance;
		return instance;
	}
private:
	korean_factory(const korean_factory&) = delete;
	korean_factory(korean_factory&&) = delete;

	korean_factory& operator=(const korean_factory&) = delete;
	korean_factory& operator=(korean_factory&&) = delete;
};


class catgirl_clan_factory : public factor {
public:
	catgirl_clan_factory() = default;
	~catgirl_clan_factory() = default;

	
	std::unique_ptr<person> create(uint8_t gender, uint8_t age, std::string name) const override {
		return std::make_unique<catgirl_clan>(gender, age, name);
	}
	

	static catgirl_clan_factory& get_instance() {
		static catgirl_clan_factory instance;
		return instance;
	}
private:
	catgirl_clan_factory(const catgirl_clan_factory&) = delete;
	catgirl_clan_factory(catgirl_clan_factory&&) = delete;

	catgirl_clan_factory& operator=(const catgirl_clan_factory&) = delete;
	catgirl_clan_factory& operator=(catgirl_clan_factory&&) = delete;
};


class factory_manager {
public:
	static factory_manager* get_manager() {
		static factory_manager manager;
		return &manager;
	}

	/*
	* 返回factory_manager*更活,
	*/
	bool add_factory(race type, factor* factory) {
		if (find(type) != nullptr)
			return false;
		
		factories.insert(std::make_pair(type, factory));

		return true;
	}

	/*
	* 
	*/
	std::unique_ptr<person> create(uint8_t gender, uint8_t age, std::string name, race type) {
		auto it = find(type);

		if (it == nullptr)
			return nullptr;

		return it->create(gender, age, name);
	}

	/*
	* 查询工厂,返回工厂指针
	*/
	factor* find(race type) {
		auto it = factories.find(type);

		if (it == factories.end())
			return nullptr;

		return (*it).second;
	}

private:
	factory_manager() {
		factories.insert(std::make_pair(race::han_ethnicity, &han_ethnicity_factory::get_instance()));
		factories.insert(std::make_pair(race::yamato_people, &yamato_people_factory::get_instance()));
		factories.insert(std::make_pair(race::korean, &korean_factory::get_instance()));
		factories.insert(std::make_pair(race::catgirl_clan, &catgirl_clan_factory::get_instance()));
	}
	~factory_manager() = default;

	factory_manager(const factory_manager&) = delete;
	factory_manager(factory_manager&&) = delete;

	factory_manager& operator=(const factory_manager&) = delete;
	factory_manager& operator=(factory_manager&&) = delete;

	std::unordered_map<race,factor*> factories;
};


class test : public person {
public:
	void action() override {
		std::cout << "test" << std::endl;
	}
	test(const uint8_t gender, const uint8_t age, const std::string& name)
		: person(gender, age, name) {
	}
	~test() {
		std::cout << "~test" << std::endl;
	}
private:
	test(const test&) = delete;
	test(test&&) = delete;

	test& operator=(const test&) = delete;
	test& operator=(test&&) = delete;
};

class test_factory : public factor {
public:
	test_factory() = default;
	~test_factory() = default;

	std::unique_ptr<person> create(uint8_t gender, uint8_t age, std::string name) const override {
		return std::make_unique<test>(gender, age, name);
	}

	static test_factory& get_instance() {
		static test_factory instance;
		return instance;
	}

private:
	test_factory(const test_factory&) = delete;
	test_factory(test_factory&&) = delete;

	test_factory& operator=(const test_factory&) = delete;
	test_factory& operator=(test_factory&&) = delete;
};



//为了方便factory_manager::get_manager()使用
#define MANAGER_PERSON factory_manager::get_manager()