#ifndef LIST_H_
#define LIST_H_
#include <algorithm>
/*
http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/List.h
*/
template <typename Object>
class List
{
private:
	// The basic doubly linked list node.
	// Nested inside of List, can be public
	// because the Node is itself private
	struct Node
	{
		Object  data;
		Node   * prev;
		Node   * next;

		Node(const Object & d = Object(), Node * p = nullptr, Node * n = nullptr): data(d), prev(p), next(n)
		{ }
		Node(Object && d, Node * p = nullptr, Node * n = nullptr): data(std::move(d)), prev(p), next(n)
		{ }
	};

public:
	//base class of iterator
	class const_iterator
	{
	protected:
		Node * current;

	public:
		// Public constructor for const_iterator.
		const_iterator() : current(nullptr)
		{ }

		// Return the object stored at the current position.
		// For const_iterator, this is an accessor with a
		// const reference return type.
		const Object & operator*() const
		{
			return this->retrieve();
		}
		//pre-increment operator
		const_iterator & operator++()
		{
			current = current->next;
			return *this;
		}
		//post-increment operator
		const_iterator operator++(int)
		{
			const_iterator old = *this;
			++(*this);//pre-increment
			return old;
		}
		//pre-decrement
		const_iterator & operator--()
		{
			current = current->prev;
			return *this;
		}
		//post-decrement
		const_iterator operator--(int)
		{
			const_iterator old = *this;
			--(*this);//pre-decrement
			return old;
		}

		bool operator==(const const_iterator & rhs) const
		{
			return current == rhs.current;
		}

		bool operator!=(const const_iterator & rhs) const
		{
			return !(*this == rhs);
		}

	protected:
		// Protected helper in const_iterator that returns the object
		// stored at the current position. Can be called by all
		// three versions of operator* without any type conversions.
		Object & retrieve() const
		{
			return current->data;
		}

		// Protected constructor for const_iterator.
		// Expects a pointer that represents the current position.
		const_iterator(Node * p) : current(p)
		{ }

		friend class List<Object>;
	};

	//derived class of const_iterator
	class iterator : public const_iterator
	{
	public:
		// Public constructor for iterator.
		// Calls the base-class constructor.
		// Must be provided because the private constructor
		// is written; otherwise zero-parameter constructor
		// would be disabled.
		iterator()
		{ }

		Object & operator*()
		{
			return const_iterator::retrieve();
		}

		// Return the object stored at the current position.
		// For iterator, there is an accessor with a
		// const reference return type and a mutator with
		// a reference return type. The accessor is shown first.
		const Object & operator*() const
		{
			return const_iterator::operator*();
		}

		//pre-increment
		iterator & operator++()
		{
			this->current = this->current->next;
			return *this;
		}
		//post-increment
		iterator operator++(int)
		{
			iterator old = *this;
			++(*this);//pre-increment
			return old;
		}
		//pre-decrement
		iterator & operator--()
		{
			this->current = this->current->prev;
			return *this;
		}
		//post-decrement
		iterator operator--(int)
		{
			iterator old = *this;
			--(*this);//pre-decrement
			return old;
		}

	protected:
		// Protected constructor for iterator.
		// Expects the current position.
		iterator(Node * p) : const_iterator(p)
		{ }

		friend class List<Object>;
	};


private:
	int   m_size;
	Node * m_head;
	Node * m_tail;

	void init()
	{
		m_size = 0;
		m_head = new Node;
		m_tail = new Node;
		m_head->next = m_tail;
		m_tail->prev = m_head;
	}
public:
	//ctor
	List()
	{
		this->init();
	}
	//dtor
	~List()
	{
		this->clear();
		delete m_head;
		delete m_tail;
	}
	//copy ctor: deep copy
	List(const List & rhs)
	{
		this->init();
		for (auto & x : rhs)
			this->push_back(x);
	}
	//copy ctor: move
	List(List && rhs) : m_size(rhs.m_size), m_head(rhs.m_head), m_tail(rhs.m_tail)
	{
		rhs.m_size = 0;
		rhs.m_head = nullptr;
		rhs.m_tail = nullptr;
	}
	//assignment: deep copy
	List & operator=(const List & rhs)
	{
		List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	//assignment: move
	List & operator=(List && rhs)
	{
		std::swap(m_size, rhs.m_size);
		std::swap(m_head, rhs.m_head);
		std::swap(m_tail, rhs.m_tail);

		return *this;
	}

	// Return iterator representing beginning of list.
	// Mutator version is first, then accessor version.
	iterator begin()
	{
		return iterator(m_head->next);
	}

	const_iterator begin() const
	{
		return const_iterator(m_head->next);
	}

	// Return iterator representing endmarker of list.
	// Mutator version is first, then accessor version.
	iterator end()
	{
		return iterator(m_tail);
	}

	const_iterator end() const
	{
		return const_iterator(m_tail);
	}

	// Return number of elements currently in the list.
	int size() const
	{
		return m_size;
	}

	// Return true if the list is empty, false otherwise.
	bool empty() const
	{
		return this->size() == 0;
	}

	void clear()
	{
		while (!this->empty())
			this->pop_front();
	}

	// front, back, push_front, push_back, pop_front, and pop_back
	// are the basic double-ended queue operations.
	Object & front()
	{
		return *this->begin();
	}

	const Object & front() const
	{
		return *this->begin();
	}

	Object & back()
	{
		return *--this->end();
	}

	const Object & back() const
	{
		return *--this->end();
	}

	void push_front(const Object & x)
	{
		this->insert(this->begin(), x);
	}

	void push_back(const Object & x)
	{
		this->insert(this->end(), x);
	}

	void push_front(Object && x)
	{
		this->insert(this->begin(), std::move(x));
	}

	void push_back(Object && x)
	{
		this->insert(this->end(), std::move(x));
	}

	void pop_front()
	{
		this->erase(this->begin());
	}

	void pop_back()
	{
		this->erase(--this->end());
	}

	// Insert x before itr.
	iterator insert(iterator itr, const Object & x)
	{
		Node *p = itr.current;
		++m_size;
		return iterator(p->prev = p->prev->next = new Node(x, p->prev, p));
	}

	// Insert x before itr.
	iterator insert(iterator itr, Object && x)
	{
		Node *p = itr.current;
		++m_size;
		return iterator(p->prev = p->prev->next = new Node(std::move(x), p->prev, p));
	}

	// Erase item at itr.
	iterator erase(iterator itr)
	{
		Node * p = itr.current;
		iterator retVal(p->next);
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		--m_size;

		return retVal;
	}

	iterator erase(iterator from, iterator to)
	{
		for (iterator itr = from; itr != to;)
			itr = this->erase(itr);

		return to;
	}


};
#endif