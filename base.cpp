#include <iostream>

using namespace std;

class Date
{
	private:
		int day;
		int month;
		int year;
		
	public:
		Date(){};
		Date(int day, int month, int year)
		{
			this->day = day;
			this->month = month;
			this->year = year;
		}
		
		int getDay(){	return day;	}
		int getMonth(){	return month;	}
		int getYear(){	return year;	}
		
		void showDate()
		{
			cout << day << "/" << month << "/" << year;
		}
};

class Medicine
{
	private:
		string company;
		string medicine;
		int quantity;
		int id;
		int price;
		Date d;
		
	public:
		Medicine();
		Medicine(string company, string medicine, int quantity, int id, int price, int day, int month, int year);
		
		void setQuantity(int);
		void setPrice(int);
		
		string getMedicine();
		string getCompany();
		int getQuantity();
		int getId();
		int getPrice();
		
		int getDay(){	d.getDay();	}
		int getMonth(){	d.getMonth();	}
		int getYear(){	d.getYear();	}
		void showDate(){	d.showDate(); }
		
		static int counter;
		static int sortFlag;
		virtual string getType(){	}
};

int Medicine::counter = 0;
int Medicine::sortFlag = 0;

//Definition
Medicine::Medicine()
{
	company="NULL";
	medicine="NULL";
	quantity=0;
	id=0;
	price=0;
}

Medicine::Medicine(string company, string name, int quantity, int id, int price, int day, int month, int year)
{
	this->company = company;
	this->medicine = name;
	this->quantity = quantity;
	this->id = id;
	this->price = price;
	d = Date(day,month,year);
	Medicine::counter++;

}

void Medicine::setQuantity(int q)
{
	this->quantity = q;
	
	cout << quantity;
}

void Medicine::setPrice(int p)
{
	this->price = p;
}

string Medicine::getCompany()
{
	return company;
}

string Medicine::getMedicine()
{
	return medicine;
}

int Medicine::getQuantity()
{
	return quantity;
}

int Medicine::getId()
{
	return id;
}

int Medicine::getPrice()
{
	return price;
}


class Liquid:public Medicine
{
	private:
		string type;
	public:
		Liquid(string company, string name, int quantity, int id, int price, int day, int month, int year);
		string getType()
		{
			return type;
		}
};
	
Liquid::Liquid(string company, string name, int quantity, int id, int price, int day, int month, int year) : Medicine(company, name, quantity, id, price, day, month, year)
{
	type = "LIQUID";
}

class Tablet:public Medicine
{
	private:
		string type;
	public:
		Tablet(string company, string name, int quantity, int id, int price, int day, int month, int year);
		string getType()
		{
			return type;
		}
};
	
Tablet::Tablet(string company, string name, int quantity, int id, int price, int day, int month, int year) : Medicine(company, name, quantity, id, price, day, month, year)
{
	type = "TABLET";
}

