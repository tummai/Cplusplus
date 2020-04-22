/* Final exam Review */ 

/*1, Given an input file of people names (which contain spaces), 
read in file 
store values in a vector, 
display the values from the vector, 
sort the vector 
write out the vector again 
write the sorted strings from the vector to a file 
*/ 

#include <iostream> 
#include <fstream>
#include <vector>
#include <algorithm> 

using namespace std; 

int main()
{
	ifstream MyInFile{"infile.txt"};
	ofstream MyOutFile{"outfile.txt",ios::out};
	string FileLine; 
	vectore <string> Roster; 
	
	if (MyFile.is_open())
	{
		while(!MyInFile.oef())
		{
			getline(MyInFile,FileLine);
			Roster.push_back(FileLine);
		}
	}
	else
	{
		cout << " Cannot open file " << endl;
		exit(0);
	}
	MyInFile.close();
	cout << " Roster before sorting" << endl;
	
	for (auto it : Roster)
	{
		cout << it << endl;
	}
	
	sort(Roster.begin(),Roster.end());
	cout << "\n\n Roster after sorting " << endl;
	
	for ( auto it : Roster )
		cout << it << endl;
	
	for ( auto it : Roster )
		MyOutFile << it << endl;
	
	MyOutFile.close();
	
	return 0; 
}

//-----------------------------------

/* 2. Two RGB color may be mixed by averaaging their corresponding red, green, and ble values. Given the interface to class Color below 
implement the constructor, operator + method, and operator << friend function 
such that the main will print " Puroke is ( 127, 0, 127)"
*/

//The given code 

#include <iostream>
#include <ostream>

class Color
{
	public:
		Color (int red, int green, int blue);
		Color operator+(const color &rhs);
		friend std::ostream& operator << (std::ostream& ost, const Color& c);
	
	private:
		int _red;
		int _green;
		int _blue;
			
};

int main()
{
	Color red{250,0,0};
	Color blue{0,0,255};
	std::cout << "Purple is " << (red+blue) << std::endl;
}

//Answer 
//constructor 
Color::Color (int red, int green, int blue) : _red{red}, _green{green}, _blue{blue} 
{
	
}

//overload the + operator 
Color Color::operator+ (const Color& rhs)
{
	return Color{(_red+rhs._red) / 2, (_green+rhs._green) / 2, (_blue+rhs._blue) /2};
}

//overload the << operator 

std::ostream& operator<<(std::ostream& ost, const Color& c)
{
	ost << '(' << c._red << ',' << c._green << ',' << c._blue << ')';
	return ost;
}

/* 3. Given classes, add/fill in the information 
Orangelo -> Orange, Grapefruit -> Fruit 
Fruit should be virtual 
create vetor named Basker that hold Orange, Grapefrit and Orangelo
use loop call member function whoamI for each element in vector 

*/

#include <iostream>
#include <vector>

using namespace std;

class Fruit
{
	public:
		virtual void whoamI() = 0; //make it pure virtual
};

class Orange : vitural public Fruit
{
	public:
		void whoamI() 
		{
       		cout << "Orange";
    	}
};

class Grapefruit : virtual public Fruit
{
    public:
        void whoamI()
        {
            cout << "Grapefruit";
		} 
};

class Orangelo : public Orange, Grapefruit 
{
    public:
        void whoamI()
        {
            cout << "Orangelo";
		} 
};

int main(void) 
{
     vector<Fruit*>Basket;
     Basket.push_back(new Orangelo());
     Basket.push_back(new Orange());
     Basket.push_back(new Grapefruit());
	 
	 for (auto it : Basket) 
	 {
		 it->whoamI(); 
		 cout << endl; 
		 delete it;
	 }
	 
	 return 0; 
}


/* 5. Consider the following code segment. 
make main function creates 2 threads of some_function and joins them back to the main 
*/ 

#include <iostream>
#include <thread>

void some_function (std::string message)
{
	std::cout << message << std::endl;
}

int main () 
{
	thread t1(some_function, "Message 1");
	thread t2(some_function, "Message 2");
	
	t1.join();
	t2.join();
	
	return 0;
}


//make 100 threads and join them, using mutex to stop print and ... 

/* 6. Given the following program, write the function maximum() using templates 

*/ 
template <typename> T 




