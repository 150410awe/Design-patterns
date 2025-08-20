#pragma once
#include <cstdint>
#include <mutex>
#include <memory>
#include <unordered_map>
#include <string>


/*
* @brief �Բ�ͬ�ĵȼ�����������
* �����������ʹ��
* ��չ�Բ�
enum class level {
	v1,
	v2,
	v3
};
*/

/*
* @brief �����ȼ�,������һ��,ָ�������ȼ�
* �������չ�Բ��봫ͳʹ���������ַ������������
* @note ����ʹ��inline const
*/
namespace level {
	inline const std::string v1 = "v1";
	inline const std::string v2 = "v2";
	inline const std::string v3 = "v3";
}


/*
* @brief ��������
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
* @brief ��������
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
* @brief ����������
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
* @brief ����
*/
class car {
public:
	/*
	* @brief �ö�̬������ͬ�ȼ�������
	* @param engine 
	* @param fuel_tank
	* @param transmission
	* @note ʹ���ƶ�����,�����˿���,��������
	*/
	car(std::unique_ptr<engine>&& engine,
		std::unique_ptr<fuel_tank>&& fuel_tank,
		std::unique_ptr<transmission>&& transmission) : 
		engine_v(std::move(engine)),
		fuel_tank_v(std::move(fuel_tank)),
		transmission_v(std::move(transmission))	{
	}

	/*
	* @brief ʹ��������engine 
	* @note const ��Ա����
	*/
	void get_engine() const{
		engine_v->run();
	}
	/*
	* @brief ʹ��������fuel_tank
	* @note const ��Ա����
	*/
	void get_fuel_tank() const{
		fuel_tank_v->come_on();
	}
	/*
	* @brief ʹ��������transmission
	* @note const ��Ա����
	*/
	void get_transmission() const{
		transmission_v->change_gear();
	}
	

	/*
	* @brief �������� 
	* @note ����������ָ��,����Ҫ����
	*/
	~car() = default;
private:

	/*
	* @brief ���������
	* @note ʹ��ʹ�ö�̬
	*/
	std::unique_ptr<engine> engine_v;
	std::unique_ptr<fuel_tank> fuel_tank_v;
	std::unique_ptr<transmission> transmission_v;
};



/*
* @brief ��������,������ͬ�ȼ�������
* @note ����ģʽ
*/
class car_factory {
public:
	/*
	* @brief ������ͬ�ȼ�������
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
* @brief 1����������
* @note ����ģʽ,��������factory_managerʹ��
*/
class car_factory_v1 : public car_factory {
public:
	/*
	* @brief ����1��������
	* @return unique_ptr<car>
	*/
	std::unique_ptr<car> create_car() const override;
	/*
	* @brief ��ȡ����
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
* @brief 2����������
* @note ����ģʽ,��������factory_managerʹ��
*/
class car_factory_v2 : public car_factory {
public:
    /*
	* @brief ����2��������
	* @return unique_ptr<car>
	*/
	std::unique_ptr<car> create_car() const override;
	/*
	* @brief ��ȡ����
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
* @brief 3����������
* @note ����ģʽ,��������factory_managerʹ��
*/
class car_factory_v3 : public car_factory {
public:
	/*
	* @brief ����3��������
	* @return unique_ptr<car>
	*/
	std::unique_ptr<car> create_car() const override;
	/*
	* @brief ��ȡ����
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
* @brief ��������������
* @note ����ģʽ
* @note Ϊʲô����factory_manager,������������ȼ�Խ��Խ��,ʹ��ʱ��Ҫget��Ӧ�ù����ĵ���
̫�鷳,factory_manager��������д�����ˬ,ֱ����namespace levelָ��
*/
class factory_manager {
public:
	/*
	* @brief ���������ȼ�
	* @param l_version
	* @return const car_factory*
	* @note ����ʹ��const��Ա����,����ֵҲΪconst,��ֹ�޸�
	* @note ʹ�ø���������std::string_view ��������,���ⲻ��Ҫ���ַ�������
	*/
	const car_factory* find(std::string_view l_version) const;
	/*
	* @brief ����µ�����
	* @param l_version
	* @return std::unique_ptr<car>
	* @note ʹ��const��Ա����
	* @note ʹ��std::string_view ��������,���ⲻ��Ҫ���ַ�������
	*/
	std::unique_ptr<car> add_new_car(std::string_view l_version) const;
	/*
	* @brief ����µ������ȼ�
	* @param l_version
	* @param c_version
	* @return bool
	* @note c_version����Ĳ���������һ���Ĺ���,Ϊ�˸���,����factories��second �ظ����
	* @note ʹ��std::string_view ��������,���ⲻ��Ҫ���ַ�������
	*/
	bool add_new_car_level(std::string_view l_version, car_factory* c_version);
	/*
	* @brief ��ȡ����
	* @return factory_manager&
	*/
	static factory_manager& get_instance();

private:
	/*
	* @brief ���캯��,����һЩ�����ȼ�
	*/
	factory_manager();
	~factory_manager() = default;

	factory_manager(const factory_manager&) = delete;
	factory_manager(const factory_manager&&) = delete;

	factory_manager& operator=(const factory_manager&) = delete;
	factory_manager& operator=(const factory_manager&&) = delete;

	/*
	* @brief ���������ȼ�
	* @note ʹ��std::unordered_map
	ʹ��std::string�����е���,car_factory*ʹ�ö�̬,���������ȼ�������
	* @note ��ʹ������ָ��,��Ϊ��������ǵ���ģʽ,ֻ��һ��ʵ��,Ҳֻ��factories���ԺϷ�����
	* @note ���ڶ����ͬ����Ҳ��Ӱ��,��Ϊstaticֻ���ڽ�����ʱ��Żᱻ����,��˲�������ڴ����ͷŵ�����
	*/
	std::unordered_map<std::string, car_factory*> factories;
	/*
	* @brief ���Ͷ��̳߳��ֵ�����
	* @note mutable��const��Ա������,����
	* @note ������������,��һ����,����������
	*/
	mutable std::mutex revise_mutex;
};

/*
* @brief ����factory_manager�ĵ���
* @return factory_manager&
* @note ʹ�ú궨��,����ʹ��,�����д���
*/
#define MANAGER_CAR factory_manager::get_instance()