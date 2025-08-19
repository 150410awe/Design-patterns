#pragma once
#include <memory>
#include <mutex>
#include <vector>
#include <cstdint>
#include <atomic>


class starving_person {
public:
	/*
	* Ϊ�˷�ֹ���vector���·����ڴ�֮ǰ��ָ��ʧЧ������,ֱ�Ӳ�����
	const vector<int32_t>& get_data() const {
		if (data.empty())
			throw std::logic_error("data is empty");
		return data;
	}
	*/
	std::vector<int32_t> get_data() const {
		std::lock_guard<std::mutex> lock(data_revise_mutex);
		return data;
	}
	static starving_person* get_instance() {
		if (instance == nullptr) //���ʹ�����ط���ʹinstanceΪnullptr.���Լ���
			throw std::logic_error("instance is nullptr");

		return instance;
	}


	/*
	* ʹ����get_data_location(location + 1)�����ɶ��Կ���û��ô��
	* ��operator[]���ܸ���
	*/
	void data_insert(const size_t location,const int32_t data) {
		std::lock_guard<std::mutex> lock(data_revise_mutex);
		data_scope(location);
		this->data.insert(this->data.begin() + location, data);

		//return get_data_location(location + 1);
	}

	void data_erase(const size_t location) {
		std::lock_guard<std::mutex> lock(data_revise_mutex);
		data_data_scope(location);

		this->data.erase(this->data.begin() + location);

		// return get_data_location(location + 1);
	}


	//���vector���·����ڴ�,����������
	//ֱ�Ӳ��ø���
	int32_t get_data_location_data(const int32_t location) const {
		std::lock_guard<std::mutex> lock(data_revise_mutex);
		data_scope(location);
		return this->data[location];
	}
	

	/*
	* ����Ϊû�б�Ҫ�������,ֱ�Ӳ�����
	int32_t operator[](const size_t location) const {
		std::lock_guard<std::mutex> lock(data_revise_mutex);
		data_data_scope(location);
		return this->data[location];
	}
	*/
	
	void data_revise(const size_t location , const int32_t get_data) {
		std::lock_guard<std::mutex> lock(data_revise_mutex);
		data_scope(location);
		this->data[location] = get_data;
	}

	/*
	* ��location������Χ���Ǵ���,��ʲôbool,��void����ȷ
	* ��location�Ƿ���this->data���ݷ�Χ��
	*/
	void data_data_scope(const size_t location) const {
		if (location >= this->data.size())
			throw std::out_of_range("location out of range");
	}
	/*
	* ����ķ�Χ,Ӧ�Բ�������
	*/
	void data_scope(const size_t location) const {
		if (location > this->data.size())
			throw std::out_of_range("location out of range");
	}

	void data_push_back(const int32_t data) {
		this->data.push_back(data);
	}

	/*
	starving_person(const starving_person&& other) : data(std::move(other.data)){
		
		// ����instance && other.instance ��û�п�����nullptr
		// �����ǲ�̫����,���Ǿ����ܱ�����,����Ϊ�˰�ȫ���Ǽ��ϰ�
		//
		if (other.instance == nullptr) 
			throw std::logic_error("other instance is nullptr");

		instance = this;
		other.instance = nullptr;
	}
	*/


private:

	starving_person() = default;
	~starving_person() = delete;	// ����ģʽ�Ķ���Ӧ�ñ�����

	starving_person(const starving_person&) = delete;
	starving_person(starving_person&&) = delete;
	
	starving_person& operator=(const starving_person&) = delete;
	starving_person& operator=(starving_person&&) = delete;

	mutable std::mutex data_revise_mutex;
	static starving_person* instance;
	std::vector<int32_t> data;
};

starving_person* starving_person::instance = new starving_person;

class lazy_person {
public:
	/*
	static const lazy_person* get_instance() {
		if (instance == nullptr) {
			std::lock_guard<std::mutex> lock(instance_mutex);
			if (instance == nullptr) {
				std::atomic<lazy_person*> temp(new lazy_person);
				instance = temp;
			}
		}
		return instance;
	}
	*/
	//c++11������
	static lazy_person* get_instance() {
		static lazy_person instance;
		return &instance;
	}
private:
	lazy_person() = default;
	~lazy_person() = default;

	lazy_person(const lazy_person&) = delete;
	lazy_person(lazy_person&&) = delete;

	lazy_person& operator=(const lazy_person&) = delete;
	lazy_person& operator=(lazy_person&&) = delete;

	//static std::mutex instance_mutex;
	mutable std::mutex data_revise_mutex;
	//static lazy_person* instance;
};