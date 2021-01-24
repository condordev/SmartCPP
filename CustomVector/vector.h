#pragma once

#include <assert.h> 
#include <stdexcept>
#include <memory>
#include <algorithm>

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

// Tthe BIG THREE stuff
// https://stackoverflow.com/questions/3510662/vectors-within-classes-handling-copy-constructor-and-destructor-c
// By the way, the Big Three is in the context of managing resources(copyingand destroying resources), not created them.
// So it would be copy - constructor, copy - assignment, and destructor, not default constructor.
// you don't need to do anything because you aren't managing any resources. 
// You only write the Big Three when you're managing a resource, but vector is doing that. It's the one with the Big Three properly written, you just use it.
class Vector3 {
public:
	// c'tor and its overloads
	Vector3() : x(0), y(0), z(0) { 
		// IMPROVEMENT FIVE: what happens is you has to deal with resource managment in the class
		memoryBlock = new int[5];
		std::cout << "Vector3()" << "\n"; 
	}
	Vector3(float scalar) : x(scalar), y(scalar), z(scalar) { 
		memoryBlock = new int[5];
		std::cout << "Vector3(scalar)" << "\n"; 
	}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) { 
		memoryBlock = new int[5];
		std::cout << "Vector3(x,y,z)" << "\n"; 
	}
	
	/* IMPROVEMENT FIVE: not called anymore
	// copy-constructor example: Vector3 v2(v1);
	Vector3(const Vector3& other) : x (other.x), y(other.y), z(other.z) {
		this->memoryBlock = new int[5];
		std::copy(other.memoryBlock, other.memoryBlock + sizeof(int)*5, this->memoryBlock); // sizeof is compile time
		std::cout << "Copy c`tor" << "\n";
	}
	*/
	Vector3(const Vector3& other) = delete;


	// move-constructor
	Vector3(Vector3&& other) noexcept : x(other.x), y(other.y), z(other.z)
	{
		// IMPROVEMENT FIVE:
		this->memoryBlock = other.memoryBlock; // stealing others memoryBlock
		other.memoryBlock = nullptr;
		std::cout << "Move c'tor" << "\n";
	}

	/* IMPROVEMENT FIVE: not called anymore
	// copy-assigment operator example: v3 = v2;
	Vector3& operator=(const Vector3& other) {
		std::cout << "Copy operator=" << "\n";
		if (this == &other) return *this;
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	*/
	Vector3& operator=(const Vector3& other) = delete;

	// move-assigment operator
	Vector3& operator=(Vector3&& other) noexcept {
		std::cout << "Move operator=" << "\n";
		this->memoryBlock = other.memoryBlock; // stealing others memoryBlock
		other.memoryBlock = nullptr;
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	~Vector3() {
		std::cout << "Destroy" << "\n";
		// deleting here is bad because of Vector d'tor which also deletes data_ 
		delete[] memoryBlock;
	}

	float x, y, z;
	int* memoryBlock = nullptr;
};

template<typename T>
class Vector {
public:
	Vector() { 
		// capacity is important because of copying and reallocating memory for the vector 
		// causes destroy and several c'tor calls. It can be improved with moving and placement new features
		reAlloc(2);
	}

	~Vector() {
		// if Vector<Vector3*> vector; is created
		// its not the responsibility of the Vector class to free the memory you allocated 
		// and the pointers point to so this is OK:
		//delete[] data_;

		clear();  // IMP FIVE this will NOT call now any destructors
		::operator delete(data_, capacity_ * sizeof(T));
	}

	void pushBack(const T& value) {
		if (size_ >= capacity_) {
			reAlloc(capacity_ + capacity_ / 2);
		}
		data_[size_++] = value;
	}

	void popBack() {
		if (size_ > 0) {
			data_[--size_].~T();
		}
	}

	void clear() {
		for (size_t i = 0; i < size_; i++) {
			data_[i].~T();
		}
		size_ = 0;
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
		// but that is constructing a temporary and move it to vector (see with breakpoint)
		//old: data_[size_] = T(std::forward<Args>(args)...);  // ... unpack the arguments

		// FOURTH IMPROVEMENT placement new operator: you providing the memory to 'new' where the obj should be directly constructed
		new (&data_[size_]) T(std::forward<Args>(args)...);
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

		//T* newBlock = new T[newCapacity];
		T* newBlock = (T*)::operator new(newCapacity * sizeof(T));  // IMP FIVE

		if (newCapacity < size_)
			size_ = newCapacity;

		for (size_t i = 0; i < size_; i++) {
			// SECOND IMPROVEMENT cast this to be an r value reference and try to move it
			// note that realloc from 2 to 4 elements calls Vector3() 4 times
			// before improvement: newBlock[i] = data_[i];
			// now there should be no copy anymore (if there is no move c'tor for the given type type it will copy)
			newBlock[i] = std::move(data_[i]);
		}

		
		for (size_t i = 0; i < size_; i++) {
			data_[i].~T();
		} // IMP FIVE
		

		//delete[] data_;
		::operator delete(data_, capacity_ * sizeof(T));  // IMP FIVE
		data_ = newBlock;
		capacity_ = newCapacity;
	}

	T* data_ = nullptr;
	size_t size_ = 0;
	size_t capacity_ = 0;
};
