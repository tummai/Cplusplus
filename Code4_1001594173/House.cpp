/* Tu Mai 
1001594173
*/
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <mutex>
#include <thread>
#include "House.h"


std::string House::ringDoorbell(std::ostringstream &path)
{
	door.lock();
	path << "*";
	std::this_thread::sleep_for(std::chrono::milliseconds(3));
	int randomnum = rand() % CandyRankingMap.size()+1;
	door.unlock();
	return CandyRankingMap.find(randomnum)->second;
	
}