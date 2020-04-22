/*Tu Mai 
1001594173*/

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <mutex>
#include <thread>
#include "TrickOrTreater.h"
#include "House.h"

House::House(std::string constructorHouseNames, std::map<int, std::string> constructorCandyMap)
		: houseName{constructorHouseNames}, CandyRankingMap{constructorCandyMap}
{
}

/*std::string House::ringDoorbell(std::ostringstream &path)
{
}*/

House::~House()
{
	std::cout << "HOUSE" << std::endl;
}