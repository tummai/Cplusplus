/* Tu Mai 
1001594173
*/

#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <chrono>
#include <vector>
#include <sstream>
#include <mutex>
#include "TrickOrTreater.h"
#include "House.h"

int TrickOrTreater::ImDone = 0;

TrickOrTreater::TrickOrTreater(std::string TTname, std::vector<House*> ConstructorHouseList)
		: name{TTname}, ListOfHouses{ConstructorHouseList}
{
}

std::string TrickOrTreater::getName()
{
	return name;
}

void TrickOrTreater::startThread()
{
	TOTThreadPtr = new std::thread(&TrickOrTreater::GoTrickOrTreating, this);
}

void TrickOrTreater::joinThread()
{
	this->TOTThreadPtr->join();
	delete TOTThreadPtr;
}

void TrickOrTreater::GoTrickOrTreating()
{	
	for(auto it : ListOfHouses)
	{
		int speed = rand() % 500 + 1;
		Walk(speed);
		std::string candy = it->ringDoorbell(path);
		Bucket[candy]++;
	}
	ImDone++;
}

void TrickOrTreater::Walk(int speed)
{
	for(int i = 0; i < 10; i++)
	{
		path << ".";
		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
	}
}

std::string TrickOrTreater::getPath()
{
	return path.str();
}

std::ostream& operator<<(std::ostream& output, TrickOrTreater &TrickOrTreater)
{
	output << TrickOrTreater.getName() << "'s - ";

	for(auto it : TrickOrTreater.Bucket)
		output << it.second << " " << it.first << ",";
		   
	return output;
}
