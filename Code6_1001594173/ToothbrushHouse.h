/*Tu Mai 
1001594173
*/
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <mutex>
#include <thread>

#ifndef _TOOTHBRUSHHOUSE_H
#define _TOOTHBRUSHHOUSE_H

class ToothbrushHouse : public House
{
	public :
		ToothbrushHouse(std::string, std::map<int, std::string>);
		std::string ringDoorbell(std::ostringstream &);
		~ToothbrushHouse();
};

#endif	