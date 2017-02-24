#pragma once

#include <functional>


//
// Ticket
//
// Calls a specified callback on destruction.
//

class Ticket
{
	std::function<void()> Destructor;
public:
	Ticket() = default;
	Ticket(std::function<void()> destructor) : Destructor(destructor) {}

	Ticket(const Ticket&) = delete;
	Ticket &operator=(const Ticket&) = delete;

	void move(Ticket &&rhs)
	{
		release();
		Destructor = std::move(rhs.Destructor);
	}

	Ticket(Ticket &&rhs)
	{
		move(std::move(rhs));
	}
	Ticket &operator=(Ticket &&rhs)
	{
		move(std::move(rhs));
		return *this;
	}

	void release()
	{
		if(Destructor)
			Destructor();
		Destructor = nullptr;
	}

	~Ticket()
	{
		if(Destructor)
			Destructor();
	}
};

