#include <fstream>
#include <sstream>
#include <string>
#include "SnackMachine.h"
#include "SnackLib.h"


using namespace std;


void get_command_line_params(char *argv[], int argc, string& inputFileName, string& outputFileName)
{
	if(argc == 3)
	{
		inputFileName = argv[1];
		outputFileName = argv[2];
	}
	else
		throw invalid_argument("Missing command line parameters - Usage : INPUTFILENAME OUTPUTFILENAME\n");
}

void validInputTest (int &choice)
{
	bool validInput = false;
	while (validInput == false)
	{
		cin >> choice;
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(32767,'\n');
			cout << "\nYou must enter a number. Please reenter you choice ";
		}
		else if ( choice < 0 || choice > 6)
		{
			cout << "\nYou must enter a value between 0 and 6. Reenter you choice ";
			validInput = false;
		}
		else
		{
			validInput = true;
		}
	}
	return;
}
void testChoice(int &choice, int newMachine)
{
	bool valid = false;
	newMachine++;
	while(valid == false)
	{
		cin >> choice;
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "\nYou must enter a number. Please reenter your choice ";
		}
		else if (choice < 0 || choice > newMachine)
		{
			cout << "\nYou must enter a value between 0 and " << newMachine << ". Reenter your choice ";
		}
		else
		{
			valid = true;
		}
	}
}
void set (SnackMachine &MySnackMachine, int newChange, int newInvent)
{
	MySnackMachine.changeLevel = newChange;
	MySnackMachine.inventoryLevel = newInvent;
}

int displayMenu(int choice, std::string machineName)
{
	cout << "\n\n" << machineName << "\n\n" << endl;
	cout << "0. Walk Away\n\n1. Buy a Snack\n\n2. Restock Machine\n\n3. Add Change\n\n4. Display Machine Info\n\n5. Update Machine Name\n\n6. Update Snack Price\n" << endl;
	cout << "Choice: ";
	validInputTest(choice);
	
	return choice;
}


string CreateSnackOutputLine(SnackMachine MySnackMachine)
{
	stringstream outputLine;
	outputLine << MySnackMachine.machineName << "|" << to_string(MySnackMachine.SnackPrice) << "|" << to_string(MySnackMachine.changeLevel) << "|" << to_string(MySnackMachine.inventoryLevel);
	return outputLine.str();
}

bool checkInventory(SnackMachine MySnackMachine)
{
	if(MySnackMachine.inventoryLevel < 1)
		return false;
	else
		return true;
}


int main(int argc, char *argv[])
{
	SnackMachine MySnackMachine;
	string inFile;
	string outFile;
	
	try
	{
		get_command_line_params(argv, argc, inFile, outFile);
	}
	catch(invalid_argument& ex)
	{
		cout << "Exiting program - \n\n\n" << ex.what() << endl;
		exit(0);
	}
	
	ifstream SnackInputFile{inFile};
	ofstream SnackOutputFile{outFile, ios::out};
	string SnackMachineLine;
	
	vector<SnackMachine> SetOfSnackMachines;
	vector <string> ConstructorValues(4);
	
	SnackMachine tempMachine;
	int newMachine = 0;
	
	if(SnackInputFile.is_open())
	{
		while(getline(SnackInputFile, SnackMachineLine))
		{
			if(ParseSnackLine(SnackMachineLine, ConstructorValues) == true)
			{
				tempMachine.setMachineName(ConstructorValues.at(0));
				tempMachine.setSnackPrice(stoi(ConstructorValues.at(1)));
				set(tempMachine, stoi(ConstructorValues.at(2)), stoi(ConstructorValues.at(3)));
				
				SetOfSnackMachines.push_back(tempMachine);
				newMachine++;
			}
			else
			{
				cout << "\nUnable to open file" << endl;
				exit(0);
			}
		}
	}
	
	int choice;
	int machineChoice = 1;
	int i;

	int payment;
	string change;
	status machineStatus;
	int machineStatusNum = (int)machineStatus;
  
	int restockNum;
	bool restockSuccess;
	bool inventoryInputValid = false;
	
	int changeNum;
	bool changeSuccess;
	bool changeInputValid = false;

	string newMachineName;
	int newSnackPrice;
	
	do
	{
		cout << "\nPick a Snack Machine\n\n0. Exit\n" << endl;
		for(i = 1; i < (SetOfSnackMachines.size()+1); i++)
		{
			cout << i << ". " << (SetOfSnackMachines.at(i-1)).getMachineName() << endl << endl;
		}
		cout << i << ". Add a new machine" << endl;
		cout << "\nEnter choice ";
		testChoice(machineChoice, newMachine);
		machineChoice--;
		choice = 1;
		
		if(machineChoice == newMachine)
		{
			SnackMachine NewSnackMachine;
			SetOfSnackMachines.push_back(NewSnackMachine);
			
			cout << "\nNew Machine Added" << endl << endl;
			newMachine++;
			choice = 0;
		}
		
		if(machineChoice == -1)
		{
			choice = 0;
			if(SnackOutputFile.is_open())
			{
				for(auto it : SetOfSnackMachines)
					SnackOutputFile << CreateSnackOutputLine(it) << endl;
			}	
			return 0;
		}

		SnackMachine currentMachine = SetOfSnackMachines.at(machineChoice);
		
		while(choice != 0)
		{
			choice = displayMenu(choice, currentMachine.getMachineName());
			if(choice == 0)
			{
				cout << "Are you sure you aren't really HUNGRY and need a snack?" << endl;
			}
			else if(choice == 1)
			{
				if(checkInventory(currentMachine) == false)
					cout << "\n\nOut of snacks - call 1800RESTOCK to request a restock...returning your payment" << endl;
				else
				{
					cout << "A snack costs " << currentMachine.getSnackPrice() << endl << endl;
					cout << "Insert payment ";
					cin >> payment;
					
					currentMachine.buyASnack(payment, change, machineStatusNum);
					if(machineStatusNum == 1)
					{
						cout << "\n\nHere's your Snack. Thank you for exact payment." << endl;
					}
					else if (machineStatusNum == 2)
					{
						cout << "\n\nHere's your Snack and your change of " << change << endl;
					}
					else if (machineStatusNum == 3)
					{
						cout << "\n\nUnable to give change at this time...returning your payment" << endl;
					}
					else if (machineStatusNum == 4)
					{
						cout << "\n\nOut of snacks - call 1800RESTOCK to request a restock...returning your payment" << endl;
					}
					else if (machineStatusNum == 5)
					{
						cout << "\n\nThere are no more snacks available...returning your payment";
					}
				}
			}
			else if(choice == 2)
			{
				inventoryInputValid = false;
				while(!inventoryInputValid)
				{
					cout << "\nHow much product are you adding to the machine? ";
					cin >> restockNum;
					if(restockNum <= 0)
					{
						cout << "You must add at least one product." << endl;
					}
					else
						inventoryInputValid = true;
				}
				
				restockSuccess = currentMachine.incrementInventory(restockNum);
				if(restockSuccess)
					cout << "\n\nYour machine has been restocked" << endl;
				else
					cout << "\n\nYou have exceeded your machine's max capacity" << endl;
				cout << "\nYour inventory level is now " << currentMachine.getInventoryLevel() << endl;
			}
			else if(choice == 3)
			{
				changeInputValid = false;
				while(!changeInputValid)
				{
					cout << "\nHow much change are you adding to the machine? ";
					cin >> changeNum;
					if(changeNum <= 0)
					{
						cout << "Your input must be greater than 0." << endl;
					}
					else
						changeInputValid = true;
				}
				
				changeSuccess = currentMachine.incrementChangeLevel(changeNum);
				if(changeSuccess)
					cout << "\n\nYour change has been updated" << endl;
				else
					cout << "\n\nYou have exceeded your machine's max capacity" << endl;
				cout << "\nYour change level is now " << currentMachine.getChangeLevel() << endl;
			}
			else if(choice == 4)
			{
				cout << currentMachine;
			}
			else if(choice == 5)
			{
				cout << "\nEnter a new machine name: ";
				cin.ignore(32767, '\n');
				getline(cin, newMachineName);
				currentMachine.setMachineName(newMachineName);
				cout << "\nMachine name has been updated." << endl;
			}
			else if(choice == 6)
			{
				cout << "\nEnter a new Snack price: ";
				cin >> newSnackPrice;
				currentMachine.setSnackPrice(newSnackPrice);
				cout << "\nSnack price has been updated." << endl;
			}
			
			SetOfSnackMachines.at(machineChoice) = currentMachine;
		}
	}
	while(machineChoice != -1);
	
	return 0;
}