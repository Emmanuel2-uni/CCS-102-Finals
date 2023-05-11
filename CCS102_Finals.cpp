#include <iostream>
#include <iomanip>
#include <string>
#include <vector> 
#include <fstream> 
#include <random>
#include <chrono>
#include "date.h"

//
// Source and reference for date.h: https://github.com/HowardHinnant/date
//


//global variables
bool program_run = false;
bool login_run = true;
bool first_run = true;
std::string prefix_ID;
int choice_menu;
int employee_number;
std::string logged_in_user;

//structs
struct employee_Details{
	std::string name;
	std::string position;
	std::string ID;
	float salary;
	
	float workTime;
	float totalPayment;
	std::string leaveStatus;
	
	employee_Details(std::string employee_Name, std::string employee_ID, std::string employee_Position, float employee_Hourly, float employee_workTime, float employee_totalPayment, std::string employee_leavestatus):
		name(employee_Name),
		ID(employee_ID),
		position(employee_Position),
		salary(employee_Hourly),
		workTime(employee_workTime),
		totalPayment(employee_totalPayment),
		leaveStatus(employee_leavestatus)
		{}
	
};


//global vectors
std::vector<employee_Details> employee;
std::vector<employee_Details> employee_backup;

//new streams
std::ofstream write_Text;
std::ofstream write_Text2;
std::ifstream read_Text;
std::ifstream read_Text2;
std::fstream update_Text;


//functions
void account_sign_up();
bool account_login();

void write_Employee(int foo_mode);
void read_Employee(std::string foo_mode);
void list_Employee(std::string foo_mode);
	//foo is just a "whatever" term in the programming community for naming various things.
	
void clear_vectors();
void input_employeeWorkDetails();
void update_Employee();
void update_Params();
void inspect_Employee(int pos);
void sort_Employee(int foo_mode);
void first_start();
void erase_Employee(std::string remove_employee);
void search_Employee();
void export_reset_Employee();
int generate_ID();
int read_params_number();
std::string read_params_ID();

	//Short documentation:
	// read_Employee contains code that will clear all vectors first and then populate the "employee" vector
	// list_Employee contains the code that will list down the data inside the vectors.
	// inspect_Employee will enable editing employee details
	// input_employeeWorkDetails enable adding/appending new employees
	// write_Employee is for writing to a file
	// update_Employee updates/overwrites the text file with the changed information (which should never be called before read_Employee)
	// "params" related functions are for adjusting/reading universal settings for the program functionalities


int main(){
	int account_choice;
	first_start();
	
	do{
	
		system("CLS");
		std::cout << "===== Account Menu =====" << std::endl;
		std::cout << "1. Sign up" << std::endl;
		std::cout << "2. Log-in" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cout << "\nInput menu choice: ";
		std::cin >> account_choice;
			if(std::cin.fail()){
				std::cin.clear();
				std::cin.ignore(256, '\n');
				account_choice = 999; //neutral/dump switch case variable
				system("CLS");
			}
		
		switch(account_choice){
			
			case 1:
				{
					std::cin.ignore(256, '\n'); //this line is to prevent the cin stream from interfering with getline() functions;
						account_sign_up();
					system("PAUSE");
					system("CLS");
					break;	
				}
				
				
			case 2:
				{
					//std::cin.ignore(256, '\n');
					read_Text.open("users_ona.txt");
						if(!read_Text.is_open()){
							std::cout << "\nNo Existing file found, please sign up first.\n";
							read_Text.close();
						break;
						}
					read_Text.close();
						
						std::cin.ignore(256, '\n');
						if(account_login() == false){
							std::cout << "\nWrong Username or Password.\n";
							system("PAUSE");
							system("CLS");
							break;
						}else{
							std::cout << "\nSuccessfully logged in!\n";
								login_run=false;
								program_run=true;
							system("PAUSE");
							system("CLS");
							break;
						}	
				}
						
			case 3:
				{
					return 0;
				}
				
			default:{
				break;
			}
		}
		
	}while(login_run==true);
	
	
	do{	
		//main menu
		bool more_choices=false;
		employee_number = read_params_number();
		prefix_ID = read_params_ID();
		read_Employee("Names");
		list_Employee("Names");
		
		if(employee.size()==0){
			remove("Employees.txt");
		}
		
		read_Text.open("Employees.txt");
		std::cout << "\n\n\nNumber of Employees: " << employee_number << std::endl;
		std::cout << "========Menu========\n";
		std::cout << "Welcome, admin " << logged_in_user << "!\n";
		
		if(read_Text.is_open()){
			more_choices = true;
			std::cout << "1. Refresh list of employees." << std::endl;
			std::cout << "2. Add an employee." << std::endl;
			std::cout << "3. Inspect an employee and edit details." << std::endl;
			std::cout << "4. Search employee." << std::endl;
			std::cout << "5. Remove employee." << std::endl;
			std::cout << "6. Sort employees." << std::endl;
			std::cout << "7. Export current data for payment record." << std::endl;
			std::cout << "33. Quick add hours." << std::endl;
			std::cout << "\n345. Reset all wages and clocked hours." << std::endl;
			std::cout << "123. Current ID prefix: " << read_params_ID() << " [choose to change] " << std::endl;
		}
		read_Text.close();
		
		std::cout << "\n\n";
		std::cout << "8. Exit." << std::endl;
		std::cout << "9. Sign out." << std::endl;
		std::cout << "10. Overwrite/Make new entire employee files" << std::endl;
		
		std::cout << "\n\nEnter choice: ";
		std::cin >> choice_menu;	
		if(std::cin.fail()){
				std::cin.clear();
				std::cin.ignore(256, '\n');
				choice_menu = 999; //neutral/dump switch case variable
				system("CLS");
		}
		if(more_choices==false && (choice_menu > 10 || choice_menu < 8)){
			std::cin.clear();
			std::cin.ignore();
			choice_menu = 999;
			system("CLS");
		}
		
		
		
	switch(choice_menu){
		
		//Allows the user to create the text file and add their first employee
		case 10:
			{	
				system("CLS");
				std::cin.ignore(256, '\n');
				write_Employee(0);
			break;
			}
		
		//Refreshes the list, a force read/list option
		case 1:
			{
				system("CLS");
				std::cout << "List of Employees: " << std::endl;
				std::cin.ignore(256, '\n');	
					read_Employee("Names");
					list_Employee("Names");
				std::cout << "\n\n";
				system("CLS");
			break;
			}
			
		//For appending/adding more employees.
		case 2:
			{
				system("CLS");
				std::cin.ignore(256, '\n');
					write_Employee(2);
			break;
			}
			
		//For inspecting an employee and then editing their details
		case 3:
			{
				system("CLS");
				std::string name_inspect;
				int save_position=0;
				bool find_pos = true;
				
				std::cin.ignore(256, '\n');
	
					read_Employee("Names"); //to populate the vector
					list_Employee("Names");
					std::cout << "Input position, name or ID [input 0 to exit]: ";
					getline(std::cin, name_inspect);
					if(name_inspect=="0"){
						break;
					}
					for(int i=0; i<employee.size(); i++){
						if(name_inspect==employee[i].name || name_inspect==employee[i].ID){
							save_position=i;
							find_pos=false;
						}
					}
					if(find_pos==true && !name_inspect.empty()){
						int find_listposition = std::stoi(name_inspect) - 1;
						save_position = find_listposition;
					}
					
					inspect_Employee(save_position);
					std::cout << "\nUpdated the employee: " << employee[save_position].name << "\n\n";
					update_Employee();
					system("PAUSE");
					system("CLS");
				break;
			}
			
		//Search function that doesn't rely on exact strings, VERY PROUD OF THIS
		case 4:{
			std::cin.ignore(256, '\n');
			system("CLS");
				read_Employee("Names"); //to populate the employee vector
				list_Employee("Names");
				search_Employee();
				update_Employee();
			system("CLS");
			break;
		}
		
		//Allows the user to remove an employee
		case 5:
			{
				std::cin.ignore(256, '\n');
				std::string remove_employee;
				system("CLS");
				read_Employee("Names"); //to populate the employee vector
				list_Employee("Names");
				std::cout << "\nWhich employee do you want to remove [input ID or Name]? ";
				getline(std::cin, remove_employee);
				
					erase_Employee(remove_employee);
					update_Employee();
					
				employee_number--;
				
				update_Params();
				
				std::cout << "\n\nEmployee removed.\n\n";
				system("PAUSE");
				system("CLS");
				break;
			}
			
		//Sorts the list of employees
		case 6:
			{
				std::cin.ignore(256, '\n');
				system("CLS");
				int sort_choice;
					read_Employee("Names"); //to populate and clear the employee vector
					list_Employee("Names");
				std::cout << "\n1. By first name (Descending)" << std::endl;
				std::cout << "2. By first name (Ascending)" << std::endl;
				std::cout << "3. By Position (Descending)" << std::endl;
				std::cout << "4. By Salary (Descending)" << std::endl;
				std::cout << "5. By Wage due (Descending)" << std::endl;
				std::cout << "\nInput preference for sorting: ";
				std::cin >> sort_choice;
			
					sort_Employee(sort_choice);
					update_Employee();
				std::cout << "\n\nSorting employees...\n\n";
				system("PAUSE");
				system("CLS");
				break;
			}
				
		//exports the list into a human-readable format		
		case 7:{
			system("CLS");
			read_Employee("Names"); 
			list_Employee("Names");
			export_reset_Employee();
			system("CLS");
			break;
		}
		
		//for quickly adding hours to employees
		case 33:{
			system("CLS");
			std::string quick_add_search;
			int quick_add_hours;
			bool find_pos = true;
			int save_position;
			
			std::cin.ignore(256, '\n');
			read_Employee("Names"); 
			list_Employee("Names");
			std::cout << "\nInput position, name or ID to quick-add/remove clocked-in hours: ";
			getline(std::cin, quick_add_search);
				if(quick_add_search=="0"){
						break;
					}
			for(int i=0; i<employee.size(); i++){
					if(quick_add_search==employee[i].name || quick_add_search==employee[i].ID){
						save_position=i;
						find_pos=false;
					}
				}
			if(find_pos==true && !quick_add_search.empty()){
					int find_listposition = std::stoi(quick_add_search) - 1;
					save_position = find_listposition;
				}
			
			std::cout << "\nInput amount of hours to add or subtract: \n";
			std::cin >> quick_add_hours;
			
			employee[save_position].workTime += quick_add_hours;
			
			std::cout << "\nSuccessfully added hours to " << employee[save_position].name << "\n\n";
			update_Employee();
			system("PAUSE");
			system("CLS");
			
			break;
		}		
		
		//for clearing the entire list of hours and wages due
		case 345:
			{
				std::cin.ignore(256, '\n');
				system("CLS");
					read_Employee("Names"); //to populate and clear the employee vector
					list_Employee("Names");
				for(int i=0; i<employee.size(); i++){
					employee[i].workTime = 0;
					employee[i].totalPayment = 0;
				}
				update_Employee();
				system("CLS");
				break;
			}
		
		//allows changing the ID prefix
		case 123:
			{
				std::string new_prefix;
				
				std::cin.ignore(256, '\n');
				system("CLS");	
				std::cout << "\nInput new ID prefix: ";
				getline(std::cin, new_prefix);
				if(new_prefix.size()>3 || new_prefix.size()<3){
					std::cout << "\nOnly three character prefixes are accepted.\n";
					system("PAUSE");
					system("CLS");
				}else{
				write_Text.open("Params.txt");
					write_Text << employee_number << std::endl;
					write_Text << new_prefix + "-" << std::endl;
				write_Text.close();
				system("CLS");
				}
				
			break;
			}
		
		
		case 8:
			{
				program_run=false;
				return 0;
			}
		
		//allows the user to sign out and log in to a different account	
		case 9:
			{
				std::cin.ignore(256, '\n');
				login_run=true;
				program_run=false;
				return main(); //goes back to the beginning of the program
			}			
		default:
			{
				break;
			}
	}
		
	}while(program_run==true);
}

void first_start(){
	if(first_run==true){
		read_Text.open("users_ona.txt", std::ios::in);
			if(!read_Text.is_open()){
				std::cout << "No existing users_ona.txt file detected." << std::endl;
			}else{
			std::cout << "Existing users_ona.txt file detected." << std::endl;
			}
		first_run=false;
		read_Text.close();
		system("PAUSE");
		system("CLS");
	}
}


void account_sign_up(){
		std::string input_user;
		std::string input_pass;
		
		write_Text.open("users_ona.txt", std::ios::app); //use std::ios::out if you want to overwrite the entire file
			std::cout << "\n\n";
			
			std::cout << "Input new username: ";
				getline(std::cin, input_user);
			std::cout << "Inpue new password: ";
				getline(std::cin, input_pass);
			
			write_Text << input_user << std::endl;
			write_Text << input_pass << std::endl;
		write_Text.close();
		std::cout << "\nUser registered!\n";
}


bool account_login(){
			std::string input_user, read_user;
			std::string input_pass, read_pass;
			
			std::cout << "Input username: ";
			getline(std::cin, input_user);
			
			std::cout << "Input password: ";
			getline(std::cin, input_pass);
			
			read_Text.open("users_ona.txt");
			bool user_found = false;
			
			while(getline(read_Text, read_user)){
				if(read_user==input_user){
					getline(read_Text, read_pass);
					if(read_user==input_user && input_pass==read_pass){
						std::cout << "User found!" << std::endl;
							logged_in_user = input_user;
							user_found=true;
							read_Text.close();
							//system("PAUSE");
						return true;
						break;
					}
				}
			}
			
			if(user_found==false){
				std::cout << "\nUser not found.\n";
				//system("PAUSE");
				read_Text.close();
				return false;
			}
			
		
}


void sort_Employee(int foo_mode){
	employee_backup = employee;
	
	switch(foo_mode){
		case 1:{
		for(int i=0; i<employee.size(); i++){	
			for(int j=i; j<employee.size(); j++){
				if(employee[i].name >= employee[j].name){	
						employee[i] = employee_backup[j];
						employee[j] = employee_backup[i];
						employee_backup=employee;
					}
				}		
			}

		break;
		}	
		
		case 2:{
		for(int i=0; i<employee.size(); i++){	
			for(int j=i; j<employee.size(); j++){
				if(employee[i].name <= employee[j].name){	
						employee[i] = employee_backup[j];
						employee[j] = employee_backup[i];
						employee_backup=employee;
					}
				}		
			}

		break;
		}		
		
		case 3:{
		for(int i=0; i<employee.size(); i++){	
			for(int j=i; j<employee.size(); j++){
				if(employee[i].position >= employee[j].position){	
						employee[i] = employee_backup[j];
						employee[j] = employee_backup[i];
						employee_backup=employee;
					}
				}		
			}

		break;
		}	
		
		case 4:{
		for(int i=0; i<employee.size(); i++){	
			for(int j=i; j<employee.size(); j++){
				if(employee[i].salary <= employee[j].salary){	
						employee[i] = employee_backup[j];
						employee[j] = employee_backup[i];
						employee_backup=employee;
					}
				}		
			}

		break;
		}
		
		case 5:{
		for(int i=0; i<employee.size(); i++){	
			for(int j=i; j<employee.size(); j++){
				if(employee[i].totalPayment <= employee[j].totalPayment){	
						employee[i] = employee_backup[j];
						employee[j] = employee_backup[i];
						employee_backup=employee;
					}
				}		
			}

		break;
		}		
		
	}
	
}


void inspect_Employee(int pos){
	bool employee_inspect=true;
	int inspect_choice;
	
	std::string string_update;
	std::string new_textPosition;
	int choice_position;
	int update_int;
	float update_float;
	
	
	do{
	system("CLS");
	std::cout << std::setw(20) << "\n\n\t1. Name: " <<  employee[pos].name << std::endl;
	std::cout << std::setw(20) << "\t2. ID: " <<  employee[pos].ID << std::endl;
	std::cout << std::setw(20) << "\t3. Position: " << employee[pos].position << std::endl;
	std::cout << std::setw(20) << "\t4. Salary: " <<  employee[pos].salary << std::endl;
	std::cout << std::setw(20) << "\t5. Hours Worked: " << employee[pos].workTime << std::endl;
	std::cout << std::setw(20) << "\t6. Wage due: " << employee[pos].totalPayment << std::endl;
	std::cout << std::setw(20) << "\t7. Leave Status: " << employee[pos].leaveStatus << std::endl;
	std::cout << "\n\tWhich information do you want to update [0 to exit]: ";
	std::cin >> inspect_choice;
	
	switch(inspect_choice){
		case 1:{
			std::cin.ignore(256, '\n');
			std::cout << "\nInput new employee name: ";
			getline(std::cin, string_update);
			employee[pos].name = string_update;
			system("PAUSE");
			break;
		}
		
		case 2:{
			std::string new_ID = prefix_ID;
			int new_5numbers;
			
			std::cin.ignore(256, '\n');
			new_5numbers = generate_ID();
			std::string five_string = std::to_string(new_5numbers);
				new_ID.append(five_string);
			std::cout << "\nNew ID generated.";
			
			employee[pos].ID = new_ID;
			system("PAUSE");
			break;
		}
		case 3:{
			std::cin.ignore(256, '\n');
			std::cout << "\nAvailable Positions: \n"; 
			std::cout << "1. Entry-Level" << std::endl;
			std::cout << "2. Contributor" << std::endl;
			std::cout << "3. Manager" << std::endl;
			std::cout << "\nInput new employee position: ";
			std::cin >> choice_position;
				if(choice_position==1){
						new_textPosition = "Entry-Level";
					}else if(choice_position==2){
						new_textPosition = "Contributor";
					}else if(choice_position==3){
						new_textPosition = "Manager";
					}else{
						"\nInput Invalid. Keeping old position...\n";
						new_textPosition = employee[pos].position;
					}
						
			employee[pos].position = new_textPosition;
			system("PAUSE");
			break;
		}
		case 4:{
			std::cin.ignore(256, '\n');
			std::cout << "\nInput new employee salary: ";
			std::cin >> update_float;
			employee[pos].salary = update_float;
			system("PAUSE");
			break;
		}
		case 5:{
			std::cin.ignore(256, '\n');
			std::cout << "\nAdd/subtract clock-in hours for employee: ";
			std::cin >> update_int;
			employee[pos].workTime += update_int;
			system("PAUSE");
			break;
		}
		case 6:{
			std::cin.ignore(256, '\n');
			std::cout << "\nTotal wage payment being updated...";
			employee[pos].totalPayment = employee[pos].workTime * employee[pos].salary;
			system("PAUSE");
			break;
		}
		case 7:{
			std::cin.ignore(256, '\n');
			std::cout << "\nInput Leave Status: ";
			getline(std::cin, string_update);
			employee[pos].leaveStatus = string_update;
			system("PAUSE");
			break;
		}
		default:{
			employee_inspect = false;
			break;
		}
			
	}
	
	}while(employee_inspect==true);

}


void update_Employee(){
	write_Text.open("Employees.txt");
	for(int i=0; i < employee.size(); i++){
			write_Text << employee[i].name << std::endl;			//name
			write_Text << employee[i].ID << std::endl;				//ID
			write_Text << employee[i].position << std::endl;		//position
			write_Text << employee[i].salary << std::endl;			//salary
			write_Text << employee[i].workTime << std::endl;		//workTime
			write_Text << employee[i].totalPayment << std::endl;	//totalPayment
			write_Text << employee[i].leaveStatus << std::endl;		//Leavestatus
	}
	write_Text.close();
}


void write_Employee(int foo_mode){
	//inputs for relevant, new hire details

	
	int choice_add;
	int write_run=1;
	
	
		
	switch(foo_mode){
	
	//case 0, overwrite entire file
	case 0:
		{
			write_Text.open("Employees.txt");
			
			employee_number = 0;
			//To write the very first employee, we need to have an existing parameter "0". So we write 0 into Params.txt.
			update_Params();
			do{
				std::cout << "List of Employees: " << std::endl;
					read_Employee("Names");
					list_Employee("Names");
					input_employeeWorkDetails();
				system("CLS");
				
				std::cout << "List of Employees: " << std::endl;
					read_Employee("Names");
					list_Employee("Names");
					
				std::cout << "\nContinue adding new employees [1-Yes, 0-No]? ";
				std::cin >> choice_add;
					if(choice_add==0){
						write_run=0;
					}
				system("CLS");
				std::cin.ignore(256, '\n');
				
				
			}while(write_run==1);
			
			
			
		write_Text.close();
		//write_Text2.close();
		
		break;
		}



	//case 2, add names;
	case 2:
		{ //append names
		write_Text.open("Employees.txt", std::ios::app);
		//write_Text2.open("Params.txt");
		
			do{
				std::cout << "List of Employees: " << std::endl;
					read_Employee("Names");
					list_Employee("Names");
					
					input_employeeWorkDetails();
					
				system("CLS");
				
				std::cout << "List of Employees: " << std::endl;
					read_Employee("Names");
					list_Employee("Names");
					
				std::cout << "\nContinue adding new employees [1-Yes, 0-No]? ";
				std::cin >> choice_add;
					if(choice_add==0){
						write_run=0;
					}
				system("CLS");
				std::cin.ignore(256, '\n');
				
				
			}while(write_run==1);
			
			
			
		write_Text.close();
		//write_Text2.close();
		break;
		} //Overwrite file end

	
	
	}
	
	
	
}


void read_Employee(std::string foo_mode){
	std::string read_name;
	std::string read_ID;
	std::string read_position;
	std::string input_salary;
	std::string input_workTime;
	std::string input_totalPayment;
	std::string read_leaveStatus;
	
	
	
	//if we only need Names, ID, Position and Hourly Salary
	if(foo_mode=="Names"){
		clear_vectors();
		read_Text.open("Employees.txt");
		
		
		for(int i=0; i<employee_number; i++){
			getline(read_Text, read_name);
			getline(read_Text, read_ID);
			getline(read_Text, read_position);
			
			//the following code will be converting the input strings into struct readable float values.
			// if this is not done, the program will return an error.
			getline(read_Text, input_salary);
				float read_salary = std::stof(input_salary);
				
			getline(read_Text, input_workTime);
				float read_workTime = std::stof(input_workTime);
				
			getline(read_Text, input_totalPayment);
				float read_totalPayment = std::stof(input_totalPayment);
				
			getline(read_Text, read_leaveStatus);
			
			employee.emplace_back(read_name, read_ID, read_position, read_salary, read_workTime, read_totalPayment, read_leaveStatus);
		}
		
		
		read_Text.close();
	}
	
	
}


void list_Employee(std::string foo_mode){
	
	
	if(foo_mode=="Names"){
		std::cout << "\n\n\t-==List of Employees==- \n";
		
		std::cout << "\t" << std::left << std::setw(5) << "No." << std::setw(20) << "Name" << std::setw(15) << "ID" << std::setw(15) << "Position";
		std::cout << std::setw(10) << "Hourly" << std::setw(10) << "Clock-in" << std::setw(10) << "Payment" << std::setw(10) << "Leave Status" << "\n";
		
		for(int i = 0; i < employee_number; i++){
			employee[i].totalPayment = employee[i].salary * employee[i].workTime;
			
			std::cout << "\t" << std::left << std::setw(5) << i+1 << std::setw(20) << employee[i].name << std::setw(15) << employee[i].ID << std::setw(15) << employee[i].position;
			std::cout << std::setw(10) << employee[i].salary << std::setw(10) << employee[i].workTime << std::setw(10) << employee[i].totalPayment << std::setw(10) << employee[i].leaveStatus << std::endl;
						
					
		}
	}
	
	
}


void erase_Employee(std::string remove_employee){
			for(int i=0; i<employee.size(); i++){
				if(remove_employee==employee[i].name || remove_employee==employee[i].ID){
					employee.erase(employee.begin()+i);
				}
			}
}


void input_employeeWorkDetails(){
		
		std::string input_textName;
		int choice_position;
		std::string input_textPosition;
		float input_hourlySalary;
		
		bool flag_inputDetails = true;
		
	
		do{
			employee_number++;
			std::cout << "\nInput new Employee Name [input 0 to exit]: ";
			getline(std::cin, input_textName);
					if(input_textName=="0"){
						flag_inputDetails=false;
						employee_number--;
						break;
					}
					
			std::cout << "\nAvailable Positions: \n"; 
			std::cout << "1. Entry-Level" << std::endl;
			std::cout << "2. Contributor" << std::endl;
			std::cout << "3. Manager" << std::endl;
			std::cout << "Input new Employee's position [input 0 to exit]: "; 
			std::cin >> choice_position;
					if(choice_position==1){
						input_textPosition = "Entry-Level";
					}else if(choice_position==2){
						input_textPosition = "Contributor";
					}else if(choice_position==3){
						input_textPosition = "Manager";
					}else{
						flag_inputDetails=false;
						employee_number--;
						break;
					}
					
					
			std::cin.ignore(256, '\n');
			std::cout << "\nInput new Employee's hourly salary [input 0 to exit]: ";
			std::cin >> input_hourlySalary;
					if(input_hourlySalary==0){
						flag_inputDetails=false;
						employee_number--;
						break;
					}
			
			
			write_Text << input_textName << std::endl;			//name
			write_Text << prefix_ID << generate_ID() << std::endl;	//ID
			write_Text << input_textPosition << std::endl;		//position
			write_Text << input_hourlySalary << std::endl;		//salary
			write_Text << "0" << std::endl;						//workTime
			write_Text << "0" << std::endl;						//totalPayment
			write_Text << "No." << std::endl;					//Leavestatus
			
			//parameter updating
			update_Params();
			system("CLS");
			read_Employee("Names");
			list_Employee("Names");
			
			std::cin.ignore(256, '\n');
			
		}while(flag_inputDetails==true);
	

	
}


void search_Employee(){
	bool run_search=true;
	std::vector<std::string> searchname;
	std::vector<std::string> searchID;
	std::vector<int> strength;

	std::string search_term;
	std::vector<char> compare_term1;
	std::vector<char> compare_term2;
	std::vector<char> compare_ID;
	std::vector<char> compare_ID2;
	
	strength.clear();
	compare_term1.clear();
	compare_term2.clear();
	compare_ID.clear();
	compare_ID2.clear();
	searchID.clear();
	searchname.clear();
	search_term.clear();
	
	for(int i=0; i<employee.size(); i++){
		searchname.push_back(employee[i].name);
		searchID.push_back(employee[i].ID);
		strength.push_back(0);
	}
	
	
	do{
		std::string input_term;
		std::cout << "\nInput first name or partial/full ID to search for: ";
		getline(std::cin, input_term);
		search_term = input_term;
		
		compare_term1.clear();
		compare_ID.clear();
		std::copy(search_term.begin(), search_term.end(), std::back_inserter(compare_term1)); //copy allows us to insert a string, character by character, into a <char> container
		std::copy(search_term.begin(), search_term.end(), std::back_inserter(compare_ID));
		compare_term1[0] = std::tolower(compare_term1[0]); 		//prevents capitalized first letters from botching up the results
		
		for(int i = 0; i < employee.size(); i++){
			compare_term1.clear();
			compare_ID.clear();
			std::copy(search_term.begin(), search_term.end(), std::back_inserter(compare_term1)); //copy allows us to insert a string, character by character, into a <char> container
			std::copy(search_term.begin(), search_term.end(), std::back_inserter(compare_ID));
				//compare_term1[0] = std::tolower(compare_term1[0]); 	
				
				//prevents capitalized letters from botching up the results
				for(int x = 0; x<compare_term1.size(); x++){
					compare_term1[x] = std::tolower(compare_term1[x]); 
				}
				
			compare_term2.clear();
			compare_ID2.clear();
		
			std::copy(searchname[i].begin(), searchname[i].end(), std::back_inserter(compare_term2));
			std::copy(searchID[i].begin(), searchID[i].end(), std::back_inserter(compare_ID2));
			

				while(compare_term1.size() < compare_term2.size()){
					compare_term1.push_back(' ');
				}
				
				//prevents capitalized letters from botching up the results
				for(int x = 0; x<compare_term2.size(); x++){
				compare_term2[x] = std::tolower(compare_term2[x]);  
				}
				
			if(compare_term1==compare_term2){
				strength[i]+=9999;
			}
			
				for(int pos = 0; pos < compare_term2.size(); pos++){
					if(   (compare_term1[pos] == compare_term2[pos])  && (compare_term1[pos+1] == compare_term2[pos+1])  ){
						strength[i]++;
					}
					if(   (compare_term1[pos] == compare_term2[pos])  && (compare_term1[pos-1] == compare_term2[pos-1])  ){
						strength[i]++;
					}
					if( compare_term1[pos] == compare_term2[pos] ){
						strength[i] += 2;
					}
				}

			for(int pos = 0; pos < compare_ID.size(); pos++){
				if( compare_ID[pos] == compare_ID2[pos] ){
					strength[i]++;
				}
			}
			
				
		}
		
		run_search=false;
		//std::cout << "\n DEBUG: Code call reached here \n";
		
	}while(run_search==true);
	
	// Below is a debug test; for showing strength of result on screen
	// std::cout << std::endl;
	// for(int i = 0; i<strength.size(); i++){
	// 	 std::cout << strength[i] << std::endl;
	// }
	//	for(int x = 0; x<compare_term2.size(); x++){
	//		std::cout << compare_term2[x] ;
	//	}
	
	std::vector<int> strength_back;
	strength_back.clear();
	employee_backup.clear();
	strength_back = strength;
	employee_backup = employee;
	
		for(int i=0; i<employee.size(); i++){	
		
			for(int j=i; j<employee.size(); j++){
				
				if(strength[i] <= strength[j]){		
						strength[i] = strength_back[j];
						strength[j] = strength_back[i];
						strength_back = strength;
						
						employee[i] = employee_backup[j];
						employee[j] = employee_backup[i];
						employee_backup = employee;					
				}
				
			}
					
		}
		
	strength.clear();
	compare_term1.clear();
	compare_term2.clear();
	searchname.clear();
	employee_backup.clear();
	
	system("PAUSE");
}	


int generate_ID(){
		int random_ID;
		
		std::random_device rd; //declare a random device "rd"
		//std::default_random_engine rand(rd()); //opinion: not "random" enough.
		std::mt19937 rand(rd()); //opinion: decently "random". This declares/makes a new "seed" on runtime with the name "rand" based on the random device on runtime
		std::uniform_int_distribution<int> random_number(10000, 99999); //for uniform distribution of the results.
		random_ID = random_number(rand);

		return random_ID;
		
}

//handy function for clearing all vectors
void clear_vectors(){

	employee_backup.clear();
	employee.clear();

}


void export_reset_Employee(){
	//
	// line below is using date.h
	// Reference: https://stackoverflow.com/questions/34963738/c11-get-current-date-and-time-as-string
	//
	std::string date_now = date::format("%F", std::chrono::system_clock::now());
	date_now.append(".txt");
	write_Text.open(date_now.c_str());
	for(int i = 0; i<employee.size(); i++){
		write_Text << employee[i].name << "\tID: " << employee[i].ID << std::endl;
		write_Text << "Total payment: " << employee[i].totalPayment << std::endl;
	}
	write_Text.close();
	
			for(int i=0; i<employee.size(); i++){
					employee[i].workTime = 0;
					employee[i].totalPayment = 0;
				}
				update_Employee();
	
}


void update_Params(){
		write_Text2.open("Params.txt");
			write_Text2 << employee_number; //global variable
			write_Text2 << prefix_ID; 		//global variable
		write_Text2.close();
}


int read_params_number(){
	int number;
	read_Text2.open("Params.txt");
		if(!read_Text2.is_open()){
			number=0;
		}else{
			read_Text2 >> number;
		}
	read_Text2.close();
	
	return number;
	
}


std::string read_params_ID(){
	
	std::string copy_string;
	int dump;
	read_Text2.open("Params.txt");
		if(!read_Text2.is_open()){
			copy_string = "A23-";
		}else{
			read_Text2 >> dump;
			read_Text2 >> copy_string;
		}
	read_Text2.close();
	
	return copy_string;
	
}
	
	
