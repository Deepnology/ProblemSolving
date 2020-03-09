#ifndef VECTOR_H_
#define VECTOR_H_
#include <algorithm>
#include <iostream>
/*
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/Vector.h
*/
template <typename Object>
class Vector
{
private:
	int m_size;
	int m_capacity;
	Object * m_objects;
public:
	static const int SPARE_CAPACITY = 2;
	//ctor
	explicit Vector(int initSize = 0): m_size(initSize), m_capacity(initSize + SPARE_CAPACITY)
	{
		m_objects = new Object[m_capacity];
	}
	//copy ctor: deep copy
	Vector(const Vector & rhs): m_size(rhs.m_size), m_capacity(rhs.m_capacity), m_objects(nullptr)
	{
		m_objects = new Object[m_capacity];
		for (int k = 0; k < m_size; ++k)
			m_objects[k] = rhs.m_objects[k];
	}
	//copy ctor: move
	Vector(Vector && rhs) : m_size(rhs.m_size), m_capacity(rhs.m_capacity), m_objects(rhs.m_objects)
	{
		rhs.m_objects = nullptr;
		rhs.m_size = 0;
		rhs.m_capacity = 0;
	}
	//assignment: deep copy
	Vector & operator=(const Vector & rhs)
	{
		Vector copy = rhs;//copy ctor: deep copy
		std::swap(*this, copy);
		return *this;
	}
	//assignment: move
	Vector & operator=(Vector && rhs)
	{
		std::swap(m_size, rhs.m_size);
		std::swap(m_capacity, rhs.m_capacity);
		std::swap(m_objects, rhs.m_objects);
		return *this;
	}
	//dtor
	~Vector()
	{
		delete[] m_objects;
	}


	bool empty() const
	{
		return this->size() == 0;
	}
	int size() const
	{
		return m_size;
	}
	int capacity() const
	{
		return m_capacity;
	}

	Object & operator[](int index)
	{
#ifndef NO_CHECK
		if (index < 0 || index >= size())
			throw std::runtime_error("");
#endif
		return m_objects[index];
	}

	const Object & operator[](int index) const
	{
#ifndef NO_CHECK
		if (index < 0 || index >= size())
			throw std::runtime_error("");
#endif
		return m_objects[index];
	}

	void resize(int newSize)
	{
		if (newSize > m_capacity)
			this->reserve(newSize * 2);
		m_size = newSize;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity < m_size)
			return;

		Object * newArray = new Object[newCapacity];
		for (int k = 0; k < m_size; ++k)
			newArray[k] = std::move(m_objects[k]);

		m_capacity = newCapacity;
		std::swap(m_objects, newArray);
		delete[] newArray;
	}

	// Stacky stuff
	void push_back(const Object & x)
	{
		if (m_size == m_capacity)
			this->reserve(2 * m_capacity + 1);
		m_objects[m_size++] = x;
	}
	// Stacky stuff
	void push_back(Object && x)
	{
		if (m_size == m_capacity)
			this->reserve(2 * m_capacity + 1);
		m_objects[m_size++] = std::move(x);
	}

	void pop_back()
	{
		if (this->empty())
			throw std::runtime_error("");
		--m_size;
	}

	const Object & back() const
	{
		if (this->empty())
			throw std::runtime_error("");
		return m_objects[m_size - 1];
	}

	// Iterator stuff: not bounds checked
	typedef Object * iterator;
	typedef const Object * const_iterator;

	iterator begin()
	{
		return &m_objects[0];
	}
	const_iterator begin() const
	{
		return &m_objects[0];
	}
	iterator end()
	{
		return &m_objects[size()];
	}
	const_iterator end() const
	{
		return &m_objects[size()];
	}

};
#endif