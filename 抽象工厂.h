#pragma once
#include <cstdint>
#include <mutex>
#include <memory>
#include <unordered_map>
#include <string>


/*
* @brief 对不同的等级的汽车分类
* 用来方便管理使用
* 扩展性差
enum class level {
	v1,
	v2,
	v3
};
*/

/*
* @brief 汽车等级,和上面一样,指定汽车等级
* 解决了扩展性差与传统使用者输入字符串错误的问题
* @note 必须使用inline const
*/
namespace level {
	inline const std::string v1 = "v1";
	inline const std::string v2 = "v2";
	inline const std::string v3 = "v3";
}


/*
* @brief 汽车引擎
*/
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





/*
* @brief 汽车油箱
*/
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




/*
* @brief 汽车变速箱
*/
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



/*
* @brief 汽车
*/
class car {
public:
	/*
	* @brief 用多态创建不同等级的汽车
	* @param engine 
	* @param fuel_tank
	* @param transmission
	* @note 使用移动语义,避免了拷贝,提升性能
	*/
	car(std::unique_ptr<engine>&& engine,
		std::unique_ptr<fuel_tank>&& fuel_tank,
		std::unique_ptr<transmission>&& transmission) : 
		engine_v(std::move(engine)),
		fuel_tank_v(std::move(fuel_tank)),
		transmission_v(std::move(transmission))	{
	}

	/*
	* @brief 使用汽车的engine 
	* @note const 成员函数
	*/
	void get_engine() const{
		engine_v->run();
	}
	/*
	* @brief 使用汽车的fuel_tank
	* @note const 成员函数
	*/
	void get_fuel_tank() const{
		fuel_tank_v->come_on();
	}
	/*
	* @brief 使用汽车的transmission
	* @note const 成员函数
	*/
	void get_transmission() const{
		transmission_v->change_gear();
	}
	

	/*
	* @brief 析构函数 
	* @note 己经有智能指针,不需要管理
	*/
	~car() = default;
private:

	/*
	* @brief 汽车的组件
	* @note 使用使用多态
	*/
	std::unique_ptr<engine> engine_v;
	std::unique_ptr<fuel_tank> fuel_tank_v;
	std::unique_ptr<transmission> transmission_v;
};



/*
* @brief 汽车工厂,创建不同等级的汽车
* @note 单例模式
*/
class car_factory {
public:
	/*
	* @brief 创建不同等级的汽车
	* @return unique_ptr<car>
	*/
	virtual std::unique_ptr<car> create_car() const = 0;

	car_factory() = default;
	~car_factory() = default;
private:
	car_factory(const car_factory&) = delete;
	car_factory(const car_factory&&) = delete;
	
	car_factory& operator=(const car_factory&) = delete;
	car_factory& operator=(const car_factory&&) = delete;
};


/*
* @brief 1级汽车工厂
* @note 单例模式,方便下面factory_manager使用
*/
class car_factory_v1 : public car_factory {
public:
	/*
	* @brief 创建1级的汽车
	* @return unique_ptr<car>
	*/
	std::unique_ptr<car> create_car() const override;
	/*
	* @brief 获取单例
	* @return car_factory_v1&
	*/
	static car_factory_v1& get_instance();

	car_factory_v1() = default;
	~car_factory_v1() = default;
private:
	car_factory_v1(const car_factory_v1&) = delete;
	car_factory_v1(const car_factory_v1&&) = delete;

	car_factory_v1& operator=(const car_factory_v1&) = delete;
	car_factory_v1& operator=(const car_factory_v1&&) = delete;
};

/*
* @brief 2级汽车工厂
* @note 单例模式,方便下面factory_manager使用
*/
class car_factory_v2 : public car_factory {
public:
    /*
	* @brief 创建2级的汽车
	* @return unique_ptr<car>
	*/
	std::unique_ptr<car> create_car() const override;
	/*
	* @brief 获取单例
	* @return car_factory_v2&
	*/
	static car_factory_v2& get_instance();

	car_factory_v2() = default;
	~car_factory_v2() = default;
private:
	car_factory_v2(const car_factory_v2&) = delete;
	car_factory_v2(const car_factory_v2&&) = delete;

	car_factory_v2& operator=(const car_factory_v2&) = delete;
	car_factory_v2& operator=(const car_factory_v2&&) = delete;
};

/*
* @brief 3级汽车工厂
* @note 单例模式,方便下面factory_manager使用
*/
class car_factory_v3 : public car_factory {
public:
	/*
	* @brief 创建3级的汽车
	* @return unique_ptr<car>
	*/
	std::unique_ptr<car> create_car() const override;
	/*
	* @brief 获取单例
	* @return car_factory_v3&
	*/
	static car_factory_v3& get_instance();

	car_factory_v3() = default;
	~car_factory_v3() = default;
private:
	car_factory_v3(const car_factory_v3&) = delete;
	car_factory_v3(const car_factory_v3&&) = delete;

	car_factory_v3& operator=(const car_factory_v3&) = delete;
	car_factory_v3& operator=(const car_factory_v3&&) = delete;
};



/*
* @brief 汽车工厂管理器
* @note 单例模式
* @note 为什么创建factory_manager,如果后面汽车等级越来越多,使用时都要get对应该工厂的单例
太麻烦,factory_manager可以让我写代码更爽,直接用namespace level指定
*/
class factory_manager {
public:
	/*
	* @brief 搜索汽车等级
	* @param l_version
	* @return const car_factory*
	* @note 合理使用const成员函数,返回值也为const,防止修改
	* @note 使用更轻量级的std::string_view 提升性能,避免不必要的字符串拷贝
	*/
	const car_factory* find(std::string_view l_version) const;
	/*
	* @brief 添加新的汽车
	* @param l_version
	* @return std::unique_ptr<car>
	* @note 使用const成员函数
	* @note 使用std::string_view 提升性能,避免不必要的字符串拷贝
	*/
	std::unique_ptr<car> add_new_car(std::string_view l_version) const;
	/*
	* @brief 添加新的汽车等级
	* @param l_version
	* @param c_version
	* @return bool
	* @note c_version传入的参数可能是一样的工厂,为了更活,不对factories的second 重复简查
	* @note 使用std::string_view 提升性能,避免不必要的字符串拷贝
	*/
	bool add_new_car_level(std::string_view l_version, car_factory* c_version);
	/*
	* @brief 获取单例
	* @return factory_manager&
	*/
	static factory_manager& get_instance();

private:
	/*
	* @brief 构造函数,创建一些汽车等级
	*/
	factory_manager();
	~factory_manager() = default;

	factory_manager(const factory_manager&) = delete;
	factory_manager(const factory_manager&&) = delete;

	factory_manager& operator=(const factory_manager&) = delete;
	factory_manager& operator=(const factory_manager&&) = delete;

	/*
	* @brief 管理汽车等级
	* @note 使用std::unordered_map
	使用std::string可能有点慢,car_factory*使用多态,管理其他等级的汽车
	* @note 不使用智能指针,因为管理的类是单例模式,只有一个实例,也只有factories可以合法管理
	* @note 关于多个相同的类也不影响,因为static只有在结束的时候才会被销毁,因此不会出现内存多次释放的问题
	*/
	std::unordered_map<std::string, car_factory*> factories;
	/*
	* @brief 降低多线程出现的问题
	* @note mutable在const成员函数中,加锁
	* @note 关于死锁问题,就一个锁,不可能死锁
	*/
	mutable std::mutex revise_mutex;
};

/*
* @brief 返回factory_manager的单例
* @return factory_manager&
* @note 使用宏定义,方便使用,可能有错误
*/
#define MANAGER_CAR factory_manager::get_instance()