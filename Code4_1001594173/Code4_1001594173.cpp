/*Tu Mai
1001594173
CA4 */

#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <thread>
#include <utility>
#include <mutex>
#include <chrono>
#include "House.h"
#include "TrickOrTreater.h"



using namespace std;
void get_command_line_params(char *argv[], int argc, string& TOTFile, string& HouseFile, string& CandyFile)
{
	if(argc == 4)
	{
		TOTFile = argv[1];
		HouseFile = argv[2];
		CandyFile = argv[3];
	}
	else
		throw invalid_argument("Missing command line parameters - Usage : TRICKORTREATERNAMES HOUSENAMES CANDYRANKINGS\n");
}

House::House(std::string houseNames, std::map<int, std::string> CandyMap)
{
	houseName = houseNames;
	CandyRankingMap = CandyMap;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	string TOTFile;
	string HouseFile;
	string CandyFile;
	
	try
	{
		get_command_line_params(argv, argc, TOTFile, HouseFile, CandyFile);
	}
	catch(invalid_argument& ex)
	{
		cout << "Exiting program - \n\n\n" << ex.what() << endl;
		exit(0);
	}
	
	ifstream trickOrTreaterNames{TOTFile};
	ifstream houseNames{HouseFile};
	ifstream candyRanking{CandyFile};
	


	map <int,string> CandyMap;
	
	string line;
	//char * ptr[2];
	char *token;
	char delim[] = "|\t\n";
	char* candy;
	char* number;
	int key;
	//printf("Before open file");
	if(candyRanking.is_open()) 
	{
		//printf("Test");
		while(getline(candyRanking, line))
		{
			char* str = const_cast <char*> (line.c_str());
			candy = strtok(str,delim);
			number = strtok(NULL," ");
			key = atoi(number);
			CandyMap.insert(pair<int,string>(key,candy));
		}
		candyRanking.close();
	}
	else 
	{
		cout << " Unable to open CANDY.txt " << endl;
	}
	
	for (auto mapItem: CandyMap)
	{
		cout<< mapItem.first<< '\t' << mapItem.second<< endl;
	}
	//step 6	
	vector<House*> HVec;
	ostringstream houseF;
	houseF << setw(10) << "";
	if (houseNames.is_open())
	{
		
		while(getline(houseNames,line))
		{
			houseF << line;
			int i = 0;
			while (i<(11 - line.size()))
			{
				houseF << " ";
				i++;
			}
			HVec.push_back(new House(line,CandyMap));
		}
		//printf("TEST");
		cout << endl;
		
		//houseNames.close();
	}
	else
	{
		cout << " Unable to open HOUSE.txt " << endl;
	}
	//Step 8
	//printf("Out");
	cout << "OUT";
	vector<TrickOrTreater> TOTS;
	
	if(trickOrTreaterNames.is_open())
	{
		printf("Test");
		while(getline(trickOrTreaterNames, line))
		{
			printf("opened");
			TOTS.push_back(TrickOrTreater{line, HVec});
		}
		trickOrTreaterNames.close();
	}
	else
	{
		cout << " Unable to open TOT.txt " << endl;
	}
	
	//Step 9: 
	//vector<TrickOrTreater>TOTs;
	for (auto& it:TOTS)
	{
		it.startThread();
	};
	
	//10
	
	//11
	while (TrickOrTreater::ImDone != TOTS.size())
	{
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		cout << houseF.str() << "\n\n";
		for(auto &it : TOTS)
		{
			cout << it.getPath() << it.getName() << endl;
		}
		//TrickOrTreater::ImDone++;
		this_thread::sleep_for(chrono::milliseconds(5));
	}

	// Step 12
	for (auto&it : TOTS)
	{
		cout << it.getName() << "'s - ";
		cout << it;
	}
	for (auto& it:TOTS)
	{
		it.joinThread();
	}
	
	return 0;
}