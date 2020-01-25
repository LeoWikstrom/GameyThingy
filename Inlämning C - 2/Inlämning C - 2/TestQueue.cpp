#include "Queue.h"
#include <iostream>
#include <string>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Test of Queue using std::string

	Queue<std::string> q1;		
	q1.enqueue("Kalle");		//Test of enqueue()
	q1.enqueue("Stina");
	q1.enqueue("Olle");
	q1.enqueue("Eva");
	q1.enqueue("Pelle");
	std::cout << "First element: " << std::endl;
	try
	{
		std::cout << q1.dequeue() << std::endl;		//Test av dequeue()
	}
	catch (std::string error)
	{
		std::cout << "An exception occured: " << error << std::endl;
	}
	std::cout << "New first element: " << std::endl;
	try
	{
		std::cout << q1.front() << std::endl;		//Test av front()
	}
	catch (std::string error)
	{
		std::cout << "An exception occured: " << error << std::endl;
	}

	std::cout << "------------------" << std::endl;
	q1.enqueue("Sven");				//Adding new element when reaching end of queue
	q1.enqueue("Kalle");			//Adding new element when queue is full - test of expand()
	Queue<std::string> q2(q1);		//Test of copy constructor
	std::cout << "First queue: " << std::endl;
	while (!q1.isEmpty())		//Utskrift av hela kön, testar isEmpty()
	{
		try 
		{
			std::cout << q1.dequeue() << std::endl;
		}
		catch (std::string error)
		{
			std::cout << "An exception occured: " << error << std::endl;
		}
	}
	std::cout << "------------------" << std::endl;
	std::cout << "Second queue - part 1: " << std::endl;
	for (int n = 0; n < 3; n++)			//Utskrift av de första tre i den kopierade kön
	{
		try
		{
			std::cout << q2.dequeue() << std::endl;
		}
		catch (std::string error)
		{
			std::cout << "An exception occured: " << error << std::endl;
		}
	}
	std::cout << "------------------" << std::endl;
	std::cout << "Second queue - part 2: " << std::endl;
	while (!q2.isEmpty())		//Utskrift av resten av den kopierade kön
	{
		try
		{
			std::cout << q2.dequeue() << std::endl;
		}
		catch (std::string error)
		{
			std::cout << "An exception occured: " << error << std::endl;
		}
	}

	std::cout << "------------------" << std::endl;
	try
	{
		std::cout << q1.front() << std::endl;			//Test av undantagshantering - försök att skriva ut tom kö
	}
	catch (const std::string error)
	{

		std::cout << "An exception occured: " << error << std::endl;
	}

	std::cout << "------------------" << std::endl;

	//Test of Queue using int

	Queue<int> q3;
	q3.enqueue(1);		//Test of enqueue()
	q3.enqueue(2);
	q3.enqueue(3);
	q3.enqueue(4);
	q3.enqueue(5);
	std::cout << "First element: " << std::endl;
	try
	{
		std::cout << q3.dequeue() << std::endl;		//Test av dequeue()
	}
	catch (std::string error)
	{
		std::cout << "An exception occured: " << error << std::endl;
	}
	std::cout << "New first element: " << std::endl;
	try
	{
		std::cout << q3.front() << std::endl;		//Test av front()
	}
	catch (std::string error)
	{
		std::cout << "An exception occured: " << error << std::endl;
	}

	std::cout << "------------------" << std::endl;
	q3.enqueue(6);			//Adding new element when reaching end of queue
	q3.enqueue(7);			//Adding new element when queue is full - test of expand()
	Queue<int> q4;
	q4 = q3;					//Test of assignment operator, also tests clear() which is used by the destructor
	
	std::cout << "First queue: " << std::endl;
	while (!q3.isEmpty())		//Utskrift av hela kön
	{
		try
		{
			std::cout << q3.dequeue() << std::endl;
		}
		catch (std::string error)
		{
			std::cout << "An exception occured: " << error << std::endl;
		}
	}
	std::cout << "------------------" << std::endl;
	std::cout << "Second queue: " << std::endl;
	while (!q4.isEmpty())		//Utskrift av den kopierade kön
	{
		try
		{
			std::cout << q4.dequeue() << std::endl;
		}
		catch (std::string error)
		{
			std::cout << "An exception occured: " << error << std::endl;
		}
	}

	//No memory leaks shows that the destructor is working as intended
	getchar();
	return 0;
}