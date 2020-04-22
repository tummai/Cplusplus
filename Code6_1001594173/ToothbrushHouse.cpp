/*Tu Mai 
1001594173
*/
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <mutex>
#include <thread>
#include "TrickOrTreater.h"
#include "House.h"
#include "ToothbrushHouse.h"

ToothbrushHouse::ToothbrushHouse(std::string constructorHouseNames, std::map<int, std::string> constructorCandyMap)
		: House(constructorHouseNames, constructorCandyMap)
{
}

ToothbrushHouse::~ToothbrushHouse()
{
	std::cout << "TOOTHBRUSHHOUSE" << std::endl;
}

std::string ToothbrushHouse::ringDoorbell(std::ostringstream &path)
{
	door.lock();
	path << "-";
	std::this_thread::sleep_for(std::chrono::seconds(3));
	int ranNum = rand() % CandyRankingMap.size() + 1;
	door.unlock();
	std::string randomCandy = "TOOTHBRUSH";
	
	return randomCandy;
}