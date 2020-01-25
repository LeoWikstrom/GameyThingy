#ifndef QUEUE_H
#define QUEUE_H

#include "IQueue.h"

template <typename T>
class Queue : public IQueue<T>
{
private:
	T * arr;
	int nrOf;
	int capacity;
	int first;
	int last;

	void clear();
	void copy(const Queue & other);
	void expand();
public:
	Queue(int startingCapacity = 5);
	Queue(const Queue & other);
	~Queue();

	void enqueue(const T & element);
	T dequeue()throw(...);
	T front() const throw(...);
	bool isEmpty() const;

	Queue<T>& operator=(const Queue & other);
};

template<typename T>
void Queue<T>::clear()
{
	delete[] this->arr;
}

template<typename T>
inline void Queue<T>::copy(const Queue & other)
{
	this->capacity = other.capacity;
	this->nrOf = other.nrOf;
	this->first = other.first;
	this->last = other.last;
	this->arr = new T[this->capacity];
	for (int n = 0; n < this->capacity; n++)
	{
		this->arr[n] = other.arr[n];
	}
}

template<typename T>
inline void Queue<T>::expand()
{
	T * temp = new T[this->capacity * 2];
	int pos = first;
	for (int n = 0; n < this->nrOf; n++)
	{
		if (pos == this->capacity)
			pos = 0;
		temp[n] = this->arr[pos];
		pos++;
	}
	delete[] this->arr;
	this->arr = temp;
	this->last = this->capacity;
	this->first = 0;
	this->capacity *= 2;
}

template<typename T>
Queue<T>::Queue(int startingCapacity)
{
	if (startingCapacity <= 0)
		startingCapacity = 5;
	this->capacity = startingCapacity;
	this->nrOf = 0;
	this->arr = new T[this->capacity];
	this->first = 0;
	this->last = nrOf - 1;
}

template<typename T>
inline Queue<T>::Queue(const Queue & other)
{
	this->copy(other);
}

template<typename T>
Queue<T>::~Queue()
{
	this->clear();
}

template<typename T>
void Queue<T>::enqueue(const T & element)
{
	this->last++;
	if (this->last == this->capacity)
		this->last = 0;
	if (this->last == this->first && this->nrOf == this->capacity)
		this->expand();
	this->arr[this->last] = element;
	this->nrOf++;
}

template<typename T>
T Queue<T>::dequeue() throw(...)
{
	if (this->isEmpty())
	{
		throw (std::string)"Queue is empty";
	}

	T output = this->arr[this->first];
	this->first++;
	if (this->first == this->capacity)
		this->first = 0;
	this->nrOf--;
	return output;
}

template <typename T>
T Queue<T>::front() const throw(...)
{
	if (this->isEmpty())
	{
		throw (std::string)"Queue is empty";
	}
	return this->arr[this->first];
}

template<typename T>
bool Queue<T>::isEmpty() const
{
	bool empty = true;
	if (this->nrOf > 0)
		empty = false;
	return empty;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue & other)
{
	if (this != &other)
	{
		this->clear();
		this->copy(other);
	}
	return *this;
}

#endif // !QUEUE_H

