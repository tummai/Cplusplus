/* Tu Mai 
1001594173*/


#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <mutex>
#include <thread>

#ifndef _CANDYHOUSE_H
#define _CANDYHOUSE_H

class CandyHouse : public House
{
	public :
		CandyHouse(std::string, std::map<int, std::string>);
		std::string ringDoorbell(std::ostringstream &);
		~CandyHouse();
};

#endif	