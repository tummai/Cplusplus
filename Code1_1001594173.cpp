/* Tu Mai 
1001594173*/

#include<iostream>
using namespace std;
#define PRICE 60

enum class status
{
	Purchase_Change,
	Purchase_NoChange,
	NonPurchase_NoInventory,
	NonPurchase_NoChange,
	NonPurchase_NonPayment,
	NonPurchase_Error

	
};

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
			cout << "\nInput must be a number. Please reenter ";
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
	cout << "\n\nPlease choose from the following option\n\n0. No pencils for me today\n1. Purchase pencils\n2. Check inventory level\n3. Check change level\n\n";
	cout << "Choice : ";
	validInputTest(choice);
	
	return choice; 
}


//Convert money in cents to dollars, and display $xx.yy
string displayMoney (int amount)
{
	string dollars {to_string(amount/100)};
	string cents {to_string(abs(amount%100))};
	return "$"+ dollars + "." + (cents.size() == 1 ? "0" : "") + cents;
}

bool buyPencils( int pencilsInput, int paymentInput, int total, int &inventory, int&change, status &userStatus)
{
/*
	Status 0: Pencils sold and change given
	Status 1: Pencils sold and no change given (exact payment)
	Status 2: Not enough inventory
	Status 3: Not enough change
	Status 4: Insufficient Payment
	Status 5: Unknown Error
	*/
	if ((pencilsInput <= inventory) && ((paymentInput - total) <= change) && (paymentInput >= total))
	{
		change = change + paymentInput;
		inventory = inventory - pencilsInput;
		
		if (paymentInput == total)
		{
			userStatus = status::Purchase_NoChange;
			return true;
		}
		else
		{
			change = change - (paymentInput - total);
			userStatus = status::Purchase_Change;
			return true;
		}
		
	}
	else
	{
		if (pencilsInput > inventory)
		{
			userStatus = status::NonPurchase_NoInventory;
			return false;
		}
		else if ((paymentInput-total) > change)
		{
			userStatus = status::NonPurchase_NoChange;
			return false;
		}
		else if (paymentInput <total)
		{
			userStatus = status::NonPurchase_NonPayment;
			return false; 
		}
		else
		{
			userStatus = status::NonPurchase_Error;
			return false;
		}
	}
}

int main() 
{
	cout << "\n\nWellcome to my Pencil Machine" << endl;
	
	
	int inventory = 100;
	int changeLevel = 500; 
	// change level in cents
	int choice = 1 ;
	status userStatus;
	int pencilsInput;
	int paymentInput;
	int total; 
	
	
	while ( choice != 0)
		{
			choice = displayMenu(choice);
			if ((inventory <= 0) && (choice != 0))
			{
				cout << "\nThis Pencil Dispenser is out of inventory." << endl;
			}
			else if ( choice != 0)
			{
				switch(choice)
				{
					case 1:
						cout << "A pencil cost " << displayMoney(PRICE)<< endl;
						cout << "How many pencils would you like to purchase? ";
						validInputTest(pencilsInput);
						if (pencilsInput <= 0)
						{
							cout << "\nYou must purchase at least one pencil." << endl;
						}
						else if (pencilsInput > inventory)
						{
							cout << "\nThe machine does not have that many pencils - buy " << inventory << " or fewer." << endl;
						}
						else
						{
							total = pencilsInput*PRICE;
							cout << "\nYour total is " << displayMoney(total) << endl;
							cout << "\nEnter your payment (in cents): ";
							validInputTest(paymentInput);
							buyPencils (pencilsInput, paymentInput, total, inventory, changeLevel, userStatus);
							if(userStatus == status::Purchase_NoChange)
							{
								cout << "\nHere's your pencils. Thank you for exact payment." << endl;
							}
							else if (userStatus == status::Purchase_Change)
							{
								cout << "\nHere's your pencils and your change of " << displayMoney(paymentInput-total) << endl;
							}
							else if(userStatus == status::NonPurchase_NoChange)
							{
								cout << "\nThis Pencil Dispenser does not have enough change and cannot accept your payment" << endl;
							}
							else if(userStatus == status::NonPurchase_NonPayment)
							{
								cout << "\nYou did not enter a sufficient payment. No pencils for you." << endl;
							}
							else if(userStatus == status::NonPurchase_NoInventory)
							{
								cout << "\nThe machine does not have that many pencils - buy " << inventory << " or fewer." << endl;
							}
							else if(userStatus == status::NonPurchase_Error)
							{
								cout << "\nUnknown Error." << endl;
							}
						}
						break;
				
					case 2:
						cout << endl << inventory << endl << endl;
						break;
					case 3:
						cout << endl << changeLevel << endl << endl;
						break;
					default:
						cout << "\nInvalid menu choice. Please choose again. " << endl;
				}		
			
			}
		}
		return 0; 
}

