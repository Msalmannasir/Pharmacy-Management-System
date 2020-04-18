#include <iostream>
#include "./library/base.cpp"
#include "./library/functions.cpp"
#include "./library/order.cpp"

using namespace std;

int main()
{
	Medicine *stock[100];
	string op1;
	load(stock);
	do{
		system("cls");
		cout << "\t\t\t\t\t     Pharamacy Management System" << endl << endl;
		cout << "1. Product Managing" << endl;
		cout << "2. Product List" << endl;
		cout << "3. Order" << endl;
		cout << "0. Exit" << endl;
		cout << "Select Option: ";
		cin >> op1;

		if(op1 == "1")
		{
			string op2;
			system("cls");
			cout << "1. Add Product" << endl;
			cout << "2. Search/Edit Product" << endl;
			cout << "0. Back To Main Menu" << endl;
			cout << "Select Option: ";
			cin >> op2;
			
			if(op2 == "1")
			{
				system("cls");
				string op3;
				cout << "1. Tablet" << endl;
				cout << "2. Liquid" << endl;
				cout << "0. Back To Main Menu" << endl;
				cout << "Select Option: ";	
				cin >> op3;
				
				if(op3 == "1")
				{
					entry(stock,op3);
				}
				
				else if(op3 == "2")
				{
					entry(stock,op3);
				}
				
				else if(op3 == "0"){}
				
				else
				{
					cout << "\nWrong Input, Back to Main Menu...";
					Sleep(600);
				}
			}
			
			else if(op2 == "2")
			{
				string op3;
				system("cls");
				cout << "1. Search by ID: " << endl;
				cout << "2. Search by Medicine Name: " << endl;
				cout << "0. Back To Main Menu" << endl;
				cout << "Select Option: ";	
				cin >> op3;
				
				if(op3 == "1" || op3 == "2")
				{
					int found = -1;
					if(op3 == "1")
					{
						string temp;
						do
						{		
							system("cls");
							cout << "\nEnter ID You Wanna Search: ";
							cin >> temp;
						}while(!checkInt(temp));
						int id = castToInt(temp);
						found = searchByID(id,stock);
					}
					
					else if(op3 == "2")
					{
						system("cls");
						string name;
						cout << "\nEnter Medicine Name You Wanna Search: ";
						cin.ignore();
						getline(cin,name);
						
						found = searchByName(name,stock);
					}
					
					if(found != -1)
					{
						showList(stock,found);
						edit(stock,found);
					}
				}
				
				else if(op3 == "0"){}
				
				else
				{
					cout << "\nWrong Input, Back to Main Menu...";
					Sleep(600);
				}
			}
			
			else if(op2 == "0"){}
				
			else
			{
				cout << "\nWrong Input, Back to Main Menu...";
				Sleep(600);
			}
		}
		
		else if(op1 == "2")
		{
			system("cls");
			if(Medicine::sortFlag!=0)
			{
				sortByName(stock);
			}
			showList(stock);
		}
		
		else if(op1 == "3")
		{
			string op2;
			Medicine *order[100];
			Order odr;
			do
			{	
				system("cls");
				cout << "1. Add Order" << endl;
				cout << "2. Delete Order" << endl;
				cout << "3. Order List" << endl;
				cout << "4. Recipt" << endl;
				cout << "0. Back to Main Menu" << endl;
				odr.order_small(order);
				gotoxy(0,5);
				cout << "Selection Option: ";
				cin >> op2;
				
				if(op2 == "1")
				{
					odr.take_order(stock,order);
				}
				
				else if(op2 == "2")
				{
					system("cls");
					odr.order_small(order);
					gotoxy(0,0);
					odr.delete_order(order);
				}
				
				else if(op2 == "3")
				{
					odr.order_list(order);
					system("pause");
				}
				
				else if(op2 == "4")
				{
					odr.print_recipt(stock,order);
				}
				
				else if(op2 == "0"){}
						
				else
				{
					cout << "\nWrong Input, Back to Order Menu...";
					Sleep(600);
				}	
			}while(op2 != "0");
		}
		
		else if(op1 == "0")
		{
			char ch;
			cout << "\n\nSave Record (Y/N): ";
			cin.ignore();
			cin >> ch;
			if(ch == 'Y' || ch == 'y')
			{
				if(Medicine::sortFlag!=0)
				{
					sortByName(stock);
				}
				save(stock);
			}
		}
		
		else
		{
			cout << "Wrong Input, Please Try Again";
			Sleep(600);
		}
	}while(op1 != "0");
}
