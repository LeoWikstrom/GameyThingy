#ifndef IQUEUE_H
#define IQUEUE_H

template <typename T>
class IQueue
{
public:
	virtual void enqueue(const T & element) = 0;
	virtual T dequeue()throw(...) = 0;
	virtual T front() const throw(...) = 0;
	virtual bool isEmpty() const = 0;
};
#endif // !IQUEUE_H