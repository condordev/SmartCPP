#pragma once

#include <assert.h> 
#include <stdexcept>
#include <memory>

template<typename T, size_t S>
class Array {
public:
	constexpr size_t Size() const { return S; }
	T& operator[] (size_t index) {
		if ( !(index < S) )
			__debugbreak();
		return data_[index]; 
	}
	const T& operator[] (size_t index) const { return data_[index]; }

	const T* Data() const { return data_; }
	T* Data() { return data_; }

private:
	T data_[S];
};

class Vector3 {
public:
	Vector3() : x(0), y(0), z(0) { 
		std::cout << "Vector3()" << "\n"; 
	}
	Vector3(float scalar) : x(scalar), y(scalar), z(scalar) { 
		std::cout << "Vector3(scalar)" << "\n"; 
	}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) { 
		std::cout << "Vector3(x,y,z)" << "\n"; 
	}
	Vector3(const Vector3& other) : x (other.x), y(other.y), z(other.z) {
		std::cout << "Copy c`tor" << "\n";
	}

	Vector3(const Vector3&& other) noexcept : x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Move c'tor" << "\n";
	}

	Vector3& operator=(const Vector3& other) {
		std::cout << "Copy operator=" << "\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Vector3& operator=(const Vector3&& other) noexcept {
		std::cout << "Move operator=" << "\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	~Vector3() {
		std::cout << "Destroy" << "\n";
	}

	float x, y, z;
};

template<typename T>
class Vector {
public:
	Vector() { 
		reAlloc(2);
	}

	~Vector() {
		// if Vector<Vector3*> vector; is created
		// its not the responsibility of the Vector class to free the memory you allocated 
		// and the pointers point to
		// so this is OK:
		delete[] data_;
	}

	void pushBack(const T& value) {
		if (size_ >= capacity_) {
			reAlloc(capacity_ + capacity_ / 2);
		}
		data_[size_++] = value;
	}

	// FIRST IMPROVEMENT R Value refs for temporaries -> move instead of copy
	// use this overload
	void pushBack(T&& value) {
		if (size_ >= capacity_) {
			reAlloc(capacity_ + capacity_ / 2);
		}
		data_[size_++] = std::move(value);
	}

	// THIRD IMPROVEMENT variadic template
	template<typename... Args>
	T& emplaceBack(Args&&... args) {
		if (size_ >= capacity_) {
			reAlloc(capacity_ + capacity_ / 2);
		}
		// forward the arguments to the corresponding c'tors of T
		data_[size_] = T(std::forward<Args>(args)...);  // ... unpack the arguments
		return data_[size_++];
	}

	const T& operator[](size_t index) const {
		//assert(index < size_);  // behaupte: index immer kleiner als size_
		if (index >= size_) {
			throw std::overflow_error(std::string("index error"));
		}
		return data_[index];
	}

	size_t size() const {
		return size_;
	}

private:
	void reAlloc(size_t newCapacity) {

		if (newCapacity < size_)
			size_ = newCapacity;

		T* newBlock = new T[newCapacity];
		for (size_t i = 0; i < size_; i++) {
			// SECOND IMPROVEMENT cast this to be an r value reference and try to move it
			// note that realloc from 2 to 4 elements calls Vector3() 4 times
			// before improvement: newBlock[i] = data_[i];
			// now there should be no copy anymore (if there is no move c'tor for the given type type it will copy)
			newBlock[i] = std::move(data_[i]);

		}

		delete[] data_;
		data_ = newBlock;
		capacity_ = newCapacity;
	}

	T* data_ = nullptr;
	size_t size_ = 0;
	size_t capacity_ = 0;
};
