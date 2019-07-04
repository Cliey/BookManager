#pragma once
#include <string>

class Publisher
{
public:
	bool operator<(Publisher rhs)
	{
		if((this->name.).compare(rhs.name) < 0)
			return true;
		return false;
	}

private:
	std::string name;
};