#include <iostream>

using namespace std;

void assign(Medicine *ob, Medicine *order[]);
int check(int id,Medicine *order[]);
int ptotal(Medicine *order[]);

class Order
{
	public:
		void take_order(Medicine *ob[], Medicine *order[]);
		void order_list(Medicine *order[]);
		void order_small(Medicine *order[]);
		void delete_order(Medicine *order[]);
		void print_recipt(Medicine *ob[], Medicine *order[]);
		static int order;
};

int Order::order = 0;

void Order::take_order(Medicine *ob[], Medicine *order[])
{
	string op3;
	system("cls");
	cout << "1. Search by ID: " << endl;
	cout << "2. Search by Medicine Name: " << endl;
	cout << "0. Back To Order Menu" << endl;
	cout << "Select Option: ";	
	cin >> op3;
				
	if(op3 == "1" || op3 == "2")
	{
		int found = -1;
		if(op3 == "1")
		{
			system("cls");
			int id;
			cout << "\nEnter ID You Wanna Search: ";
			cin >> id;
			found = searchByID(id,ob);
		}
						
		else if(op3 == "2")
		{
			system("cls");
			string name;
			cout << "\nEnter Medicine Name You Wanna Search: ";
			cin.ignore();
			getline(cin,name);
			found = searchByName(name,ob);
		}
		
		
		if(found != -1)
		{
			int forder = check(ob[found]->getId(),order);
			
			if(forder == -1)
			{
				cout << endl;
				showList(ob,found);
				int flag=0;
				do{
					string temp;
					do{
						cout << "Enter Quantity: ";
						cin >> temp;
					}while(!checkInt(temp));
					int quantity = castToInt(temp);
					positive(quantity);
					if(quantity != 0)
					{
						if(quantity <= ob[found]->getQuantity())
						{
							assign(ob[found],order);
							order[Order::order-1]->setQuantity(quantity);
							order[Order::order-1]->setPrice(quantity*order[Order::order-1]->getPrice());
							flag = 1;
						}
							
						else
						{
							cout << "Not Enough Quantity, Retry.." << endl;
							Sleep(400);
						}
					}
					
					else
					{
						flag = 1;
					}
				}while(flag==0);
			}
			
			else
			{
				cout << "Product Already Exist";
				Sleep(600);
			}
		}
	}	

	else if(op3 == "0"){}
						
	else
	{
		cout << "\nWrong Input, Back to Order Menu...";
		Sleep(600);
	}
}


void Order::order_list(Medicine *order[])
{
	system("cls");
	if(Order::order!=0)
	{
		cout << "Medcine Name";
		gotoxy(20,0);
		cout << "Company Name";
		gotoxy(40,0);
		cout << "ID";
		gotoxy(50,0);
		cout << "Expiry Date";
		gotoxy(66,0);
		cout << "Quantity";
		gotoxy(79,0);
		cout << "Type";
		gotoxy(90,0);
		cout << "Price";
		gotoxy(103,0);
		cout << "Total Price";
		for(int i=0 ; i < Order::order ; i++)
		{
			gotoxy(0,i+2);
			cout << order[i]->getMedicine();
			gotoxy(20,i+2);
			cout << order[i]->getCompany();
			gotoxy(40,i+2);
			cout << order[i]->getId();
			gotoxy(50,i+2);
			order[i]->showDate();
			gotoxy(66,i+2);
			cout << order[i]->getQuantity();
			gotoxy(79,i+2);
			cout << order[i]->getType();
			gotoxy(90,i+2);
			cout << "Rs." << order[i]->getPrice()/order[i]->getQuantity();
			gotoxy(103,i+2);
			cout << "Rs." << order[i]->getPrice();
		}
	}
	else
	{
		cout << "No Entry Found";
	}
	cout << endl << endl;
}

void Order::order_small(Medicine *order[])
{
	if(Order::order != 0)
	{
		gotoxy(55,0);
		cout << "S#";
		gotoxy(60,0);
		cout << "Medicine";
		gotoxy(80,0);
		cout << "Price/1";
		gotoxy(92,0);
		cout << "Quantity";
		gotoxy(104,0);
		cout << "Total Price";
		for(int i=0 ; i<Order::order ; i++)
		{
			gotoxy(55,i+2);
			cout << i;
			gotoxy(60,i+2);
			cout << order[i]->getMedicine();
			gotoxy(80,i+2);
			cout << "Rs." << order[i]->getPrice()/order[i]->getQuantity();
			gotoxy(92,i+2);
			cout << order[i]->getQuantity();
			gotoxy(104,i+2);
			cout << "Rs." << order[i]->getPrice();
		}
	}
}

void Order::delete_order(Medicine *order[])
{
	int del;
	
	if(Order::order != 0)
	{
		string temp;
		do
		{
			cout << "Enter S#: ";
			cin >> temp;	
		}while(!checkInt(temp));
		int del = castToInt(temp);
		positive(del);
		
		if(del < Order::order)
		{
			char op;
			cout << "Confirm Y/N: ";
			cin >> op;
			if(op == 'y' || op == 'Y')
			{
				order[del] = NULL;
				delete order[del];
				while(del < Medicine::counter)
				{
					order[del] = order[del+1];
					del++;
				}
				order[del] = NULL;
				delete order[del];
				Order::order--;
			}
		}
		else
		{
			cout << "No Entry Found";
			Sleep(600);
		}	
			
	}
	
	else
	{
		system("cls");
		cout << "Order Menu Is Empty";
		Sleep(600);
	}
}

void Order::print_recipt(Medicine *ob[], Medicine *order[])
{
	int total;
	if(Order::order!=0)
	{
		total = ptotal(order);
	}
	
	Order::order_list(order);
	gotoxy(0,Order::order+2);
	cout << "________________________________________________________________________________________________________________________";
	gotoxy(103,Order::order+4);
	cout << "Rs." << total << endl << endl;
	
	gotoxy(44,Order::order+7);
	string op;
	cout << "Bill Paid (Y/N): ";
	cin >> op;
	
	if(op == "Y" || op == "y")
	{
		for(int i=0 ; i<Order::order ; i++)
		{
			int found,id;
			id = order[i]->getId();
			found = searchByID(id,ob);
			ob[found]->setQuantity(ob[found]->getQuantity()-order[i]->getQuantity());
			order[i] == NULL;
			delete order[i];
		}
		Order::order = 0;
	}
	else
	{
		gotoxy(40,Order::order+7);
		cout << "Back to Order Menu...";
		Sleep(600);
	}
}

//Function
void assign(Medicine *ob, Medicine *order[])
{
	string company = ob->getCompany();
	string name = ob->getMedicine();
	int quantity = ob->getQuantity();
	int id = ob->getId();
	int price = ob->getPrice();
	int d = ob->getDay();
	int m = ob->getMonth();
	int y = ob->getYear();
	
	string type = ob->getType();
	
	int count = Order::order;
	if(type == "TABLET")
	{
		order[count] = new Tablet(company,name,quantity,id,price,d,m,y);
	}
	
	else
	{
		order[count] = new Liquid(company,name,quantity,id,price,d,m,y);
	}
	Order::order++;
	Medicine::counter--;
}

int check(int id,Medicine *order[])
{
	for(int i=0 ; i<Order::order ; i++)
	{
		if(id == order[i]->getId())
		{
			return i;
		}
	}
	return -1;
}

int ptotal(Medicine *order[])
{
	int total;
	for(int i=0 ; i < Order::order ; i++)
	{
		total+=order[i]->getPrice();
	}
	return total;
}
