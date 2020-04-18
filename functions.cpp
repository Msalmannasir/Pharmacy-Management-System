#include <iostream>
#include <string>
#include <fstream>
#include "windows.h"
#include <sstream>

//Prototype
void gotoxy(int x, int y);
void showList(Medicine *ob[]);
void showList(Medicine *ob, int found);
void entry(Medicine *ob[], string op);
void save(Medicine *ob[]);
void load(Medicine *ob[]);
void upercase(string &na);
int searchByID(int id, Medicine *ob[]);
int searchByName(string name, Medicine *ob[]);
void edit(Medicine *ob, int found);
bool idCheck(Medicine *ob[],int id);
bool inputDate(int &day, int &month, int &year);
bool isLeap(int year);
bool isValidDate(int d, int m, int y);
void positive(int &input);
int castToInt(string x);
bool checkInt(string x);
bool dateInput(int &date, int &month , int &year);


void gotoxy(int x, int y) 
{ 
    COORD coord;
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showList(Medicine *ob[], int found)
{
	gotoxy(0,3);
	cout << "Medcine Name";
	gotoxy(20,3);
	cout << "Company Name";
	gotoxy(40,3);
	cout << "ID";
	gotoxy(50,3);
	cout << "Price";
	gotoxy(65,3);
	cout << "Quantity";
	gotoxy(80,3);
	cout << "Type";
	gotoxy(95,3);
	cout << "Expiry Date";
	
	gotoxy(0,5);
	cout << ob[found]->getMedicine();
	gotoxy(20,5);
	cout << ob[found]->getCompany();
	gotoxy(40,5);
	cout << ob[found]->getId();
	gotoxy(50,5);
	cout << "Rs." << ob[found]->getPrice();
	gotoxy(65,5);
	cout << ob[found]->getQuantity();
	gotoxy(80,5);
	cout << ob[found]->getType();
	gotoxy(95,5);
	ob[found]->showDate();
	
	cout << endl << endl;
}

void showList(Medicine *ob[])
{
	if(Medicine::counter!=0)
	{
		cout << "Medcine Name";
		gotoxy(20,0);
		cout << "Company Name";
		gotoxy(40,0);
		cout << "ID";
		gotoxy(50,0);
		cout << "Price";
		gotoxy(65,0);
		cout << "Quantity";
		gotoxy(80,0);
		cout << "Type";
		gotoxy(95,0);
		cout << "Expiry Date";
		for(int i=0 ; i < Medicine::counter ; i++)
		{
			gotoxy(0,i+2);
			cout << ob[i]->getMedicine();
			gotoxy(20,i+2);
			cout << ob[i]->getCompany();
			gotoxy(40,i+2);
			cout << ob[i]->getId();
			gotoxy(50,i+2);
			cout << "Rs." << ob[i]->getPrice();
			gotoxy(65,i+2);
			cout << ob[i]->getQuantity();
			gotoxy(80,i+2);
			cout << ob[i]->getType();
			gotoxy(95,i+2);
			ob[i]->showDate();
		}
	}
	else
	{
		cout << "No Entry Found";
	}
	cout << endl << endl;
	system("pause");
}

void entry(Medicine *ob[], string op)
{
	int d,m,y;
	string company,name;
	int quantity,id,price;
	string temp;
	
	system("cls");
	cout << "Enter Company Name: ";
	cin.ignore();
	getline(cin,company);
	cout << "Enter Medicine Name: ";
	getline(cin,name);
	
	do{
		do{
			cout << "Enter ID: ";
			cin >> temp;
		}while(!checkInt(temp));
		id = castToInt(temp);
	}while(idCheck(ob,id));
	
	do{
		cout << "Enter Quantity: ";
		cin >> temp;
	}while(!checkInt(temp));
	quantity = castToInt(temp);
	
	do{
		cout << "Price: ";
		cin >> temp;
	}while(!checkInt(temp));
	price = castToInt(temp);
	
	int flag = 0;
	do
	{
		flag = dateInput(d,m,y);
	}while(flag == 0);
	positive(quantity);
	positive(id);
	positive(price);
	int count = Medicine::counter;
	upercase(company);
	upercase(name);
	if(op.compare("1")==0)
	{
		ob[count] = new Tablet(company,name,quantity,id,price,d,m,y);
	}
	else
	{
		ob[count] = new Liquid(company,name,quantity,id,price,d,m,y);
	}
	Medicine::sortFlag = 1;
}



void save(Medicine *ob[])
{
	ofstream myfile;
	myfile.open("data.bin", ios::out);
	
	for(int i=0 ; i<Medicine::counter ; i++)
	{
		myfile << ob[i]->getMedicine() << endl;
		myfile << ob[i]->getCompany() << endl;
		myfile << ob[i]->getId() << endl;
		myfile << ob[i]->getQuantity() << endl;
		myfile << ob[i]->getPrice() << endl;
		myfile << ob[i]->getType() << endl;
		myfile << ob[i]->getDay() << endl;
		myfile << ob[i]->getMonth() << endl;
		myfile << ob[i]->getYear() << endl;
	}
	myfile.close();
}

void load(Medicine *ob[])
{
	ifstream myfile;
	myfile.open("data.bin", ios::in);
	
	string company,name,type;
	int quantity,id,price;
	
	int day,month,year;
	
	int count = 0;
	if(!myfile.fail())
	{
		while(myfile>>name)
		{
			myfile>>company;
			myfile>>id;
			myfile>>quantity;
			myfile>>price;
			myfile>>type;
			myfile>>day;
			myfile>>month;
			myfile>>year;
			count = Medicine::counter;
			if(type == "TABLET")
			{
				ob[count] = new Tablet(company,name,quantity,id,price,day,month,year);
			}
			else
			{
				ob[count] = new Liquid(company,name,quantity,id,price,day,month,year);
			}
			count++;
		}
	}
	myfile.close();
}

void upercase(string &na)
{
	for(int i=0 ; i<na.length() ; i++)
	{
		if(na[i] >= 97 && na[i] <= 122 )
		{
			na[i]-=32;
		}
	}
}

int searchByID(int id, Medicine *ob[])
{
	for(int i=0 ; i<Medicine::counter ; i++)
	{
		if(id == ob[i]->getId())
		{
			return i;
		}
	}
	
	cout << "\nNo Medicine With Given ID was found...." << endl << endl;
	Sleep(600);
	return -1;
}


int searchByName(string name, Medicine *ob[])
{
	upercase(name);
	for(int i=0 ; i<Medicine::counter ; i++)
	{
		string name1 = ob[i]->getMedicine();
		if(name.compare(name1)==0)
		{
			return i;
		}
	}
	
	cout << "\nNo Medicine With Given Name was Found....." << endl << endl;
	Sleep(600);
	return -1;
}


void sortByName(Medicine *ob[])
{
	for(int i=0 ; i<Medicine::counter ; i++)
	{
		for(int j=i+1 ; j<Medicine::counter ; j++)
		{
			string name1 = ob[i]->getMedicine();
			string name2 = ob[j]->getMedicine();
 			if(name1.compare(name2)==1)
			{
				Medicine *temp = ob[i];
				ob[i] = ob[j];
				ob[j] = temp;
			}		
		}
	}
	Medicine::sortFlag = 0;
}

void edit(Medicine *ob[], int found)
{
	int op;
	cout << "\n1. Edit Quantity" << endl;
	cout << "2. Edit Price" << endl;
	cout << "3. Delete Product" << endl;
	cout << "0. Back To Main Menu" << endl;
	cout << "Select Option: ";
	cin >> op;
	
	if(op == 1)
	{
		int quantity;
		cout << "\nChange Quantity: ";
		cin >> quantity;
		ob[found]->setQuantity(quantity);
	}
	
	else if(op == 2)
	{
		int price;
		cout << "\nChange Price: ";
		cin >> price;
		ob[found]->setPrice(price);
	}
	
	else if(op == 3)
	{
		ob[found] = NULL;
		delete ob[found];
		while(found < Medicine::counter)
		{
			ob[found] = ob[found+1];
			found++;
		}
		ob[found] = NULL;
		delete ob[found];
		Medicine::counter--;
	}
	
	else if(op == 0){}
	
	else
	{
		cout << "\nWrong Input, Back to Main Menu...";
		Sleep(600);
	}
}

bool idCheck(Medicine *ob[],int id)
{
	for(int i=0 ; i<Medicine::counter ; i++)
	{
		if(id == ob[i]->getId())
		{
			cout << "Error : ID Already Exists" << endl;
			return true;
		}
	}
	return false;
}


void positive(int &input)
{
	if(input<0)
	{
		input *= -1;
	}
}

//Date Related Operations

const int MAX_VALID_YR = 9999; 
const int MIN_VALID_YR = 1800; 
  
bool isLeap(int year) 
{ 
	return (((year % 4 == 0) &&  (year % 100 != 0)) || (year % 400 == 0)); 
} 
  
 
bool isValidDate(int d, int m, int y) 
{ 
    if (y > MAX_VALID_YR ||  y < MIN_VALID_YR) 
    return false; 
    if (m < 1 || m > 12) 
    return false; 
    if (d < 1 || d > 31) 
    return false; 

    if (m == 2) 
    { 
        if (isLeap(y)) 
        return (d <= 29); 
        else
        return (d <= 28); 
    } 
  
    if (m == 4 || m == 6 || 
        m == 9 || m == 11) 
        return (d <= 30); 
  
    return true; 
}

int castToInt(string x)
{
	stringstream ss;
	ss << x;
	int casted;
	ss >> casted;
	return casted;
}

bool checkInt(string x)
{
	if(x[0] == '-' || (x[0] >= 48 && x[0] <= 57))
	{
		for(int i=1 ; i < x.length() ; i++)
		{
			if((x[i] >= 48 && x[i] <= 57));
			else
			{
				cout << "Not Valid Input, Retry..." << endl;
				Sleep(600);
				return false;
			}
		}
	}
	
	else
	{
		cout << "Not Valid Input, Retry..." << endl;
		Sleep(600);
		return false;
	}
	return true;
}

bool dateInput(int &day, int &month , int &year)
{
	string date;
	cin.sync();
	cout << "Enter Date (DD/MM/YYYY): ";
	getline(cin,date);
	
	int check = 0;
	
	for(int i = 0 ; i<date.length() ; i++)
	{
		if(date[i] == '/')
		{
			check++;
		}
	}
	
	if(check == 2)
	{
		for(int i=0 ; i < date.length() ; i++)
		{
			if((date[i] >= 48 && date[i] <= 57) || date[i] == '/');
			else
			{
				cout << "Invalid Date" << endl;
				return false;
			}
		}
	}
	else
	{
		cout << "Invalid Date" << endl;
		return false;
	}
	
	char flush;
	stringstream ss;
	
	ss << date;
	ss >> day;
	ss >> flush;
	ss >> month;
	ss >> flush;
	ss >> year;
	
	if(isValidDate(day,month,year))
	{
		return true;
	}
	else
	{
		cout << "Invalid Date" << endl;
		return false;
	}
}
