/*Tu Mai
1001594173
CA6 - CanndyHouse.cpp
*/
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <mutex>
#include <thread>
#include "TrickOrTreater.h"
#include "House.h"
#include "CandyHouse.h"

CandyHouse::CandyHouse(std::string constructorHouseNames, std::map<int,std::string> constructorCandyMap)
		: House(constructorHouseNames, constructorCandyMap)
{
}

std::string CandyHouse::ringDoorbell(std::ostringstream &path)
{
	door.lock();
	path << "+";
	std::this_thread::sleep_for(std::chrono::seconds(3));
	int ranNum = rand() % CandyRankingMap.size() + 1;
	door.unlock();
	std::string randomCandy = CandyRankingMap.find(ranNum)->second;
	
	return randomCandy;
}

CandyHouse::~CandyHouse()
{
	std::cout << "CANDYHOUSE" << std::endl;
}												