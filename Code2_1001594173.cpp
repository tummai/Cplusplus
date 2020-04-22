/*Tu Mai 
1001594173*/

#include "SnackMachine.h"

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
		else if ( choice < 0 || choice > 4)
		{
			cout << "\nYou must enter a value between 0 and 4. Reenter you choice ";
			validInput = false;
		}
		else
		{
			validInput = true;
		}
	}
	return;
}
int displayMenu (int choice)
{
	cout << "\n\n0. Walk away\n1. Buy a snack\n2. Restock Machine\n3. Add change\n4. Display Machine Info\n\n";
	cout << "Choice : ";
	validInputTest(choice);
	
	return choice; 
}


int main ()
{
	SnackMachine MySnackMachine {"CSE 1325 Snack Machine", 50, 500, 100};
	int end = 0; 
	int choice; 
	int payment; 
	string change = "";
	int status = 0;
	int amount;
	
	while (end == 0)
	{
		cout << "\n\n" << MySnackMachine.getMachineName() << "\n" << endl;
		choice = displayMenu(choice);
		
		if(choice == 0)
		{
			cout << "\nAre you sure you aren't really HUNGRY and need a Snack?"<<endl;
			end = 1;
		}
		else if ( choice == 1)
		{
			cout << "A snack costs " << MySnackMachine.getSnackPrice() << endl;
			cout << "Insert Payment ";
			cin >> payment;
			
			if (MySnackMachine.buyASnack(payment, change, status))
			{
				if (status == exactChange)
				{
					cout << "Thank you for exact change\n Here's your snack" << endl;
				}
				else
				{
					cout << "Here's your Snack and your change of " << change << endl;
					end = 0;
				}
				
			}
			else 
			{
				if (status == badPay)
				{
					cout << "Insufficient payment...returning your payment" << endl;
					end = 0;
				}
				else if (status == badChange)
				{
					cout << "Unable to give change at this time...returning your payment" << endl;
					end = 0;
				}
				else 
				{
					cout << "Unable to give a Snack at this time...returning your payment" << endl;
				}
			}
		}
		else if (choice == 2)
		{
			cout << "How much product are you adding to the machine? ";
			cin >> amount;
			
			if (MySnackMachine.incrementInventoryCapacity(amount))
			{
				cout << "\nYour machine has been restocked" << endl;
				cout << "\nYour inventory level is now " << MySnackMachine.getInventoryLevel() << endl;
				end = 0;
			}
			else 
			{
				cout << "\nYou have exceeded your machine's max capacity" << endl;
				cout << "\nYour inventory is now " << MySnackMachine.getInventoryLevel() << endl;
				end = 0;
			}
		}
		else if (choice == 3)
		{
			cout << "How munch change are you adding to the machine? ";
			cin >> amount;
			if ( MySnackMachine.incrementChangeLevel(amount))
			{
				cout << "\nYour change has been updated" << endl;
				cout << "\nYour change level is now " << MySnackMachine.getChangeLevel() << endl;
				end = 0;
			}
			else 
			{
				cout << "You have exceeded your machine's max capacity" << endl;
				cout << "Your change level is now " << MySnackMachine.getChangeLevel() << endl;
				end = 0;
			}
		}
		else 
		{
			cout << "Current Inventory Level\t" << MySnackMachine.getInventoryLevel() << endl;
			cout << "Max Inventory Capacity\t" << MySnackMachine.getMaxInventoryCapacity() << endl;
			cout << "Current Change Level\t" << MySnackMachine.getChangeLevel() << endl;
			cout << "Max Change Capacity\t" << MySnackMachine.getMaxChangeCapacity() << endl;
			cout << "Current Snack price is\t" << MySnackMachine.getSnackPrice() << endl;
			end = 0;
		}
	}
	return 0;
}
