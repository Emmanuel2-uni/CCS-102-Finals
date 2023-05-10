#include <iostream>
#include <iomanip>
#include <string>
#include <vector> 
#include <fstream> 
#include <random>
#include "sort_vector.h"


//global variables
bool program_run = false;
bool login_run = true;
bool first_run = true;
int choice_menu;
int employee_number;

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
	//These declarations allow the constructor to "construct" the object using the code below it
	// This can also be seen as a *function* inside the struct/class. Where if you call for the object/class employee_Details, it will construct an object with those entries immediately.
	// With the current parameters: name, position, salary, etc. -- whenever we use a proper STL function like emplace_back, we can update all of the parameters at once
	// simultaneously without having to use backups or additional overhead/declarations.
	// Benefit is that when this type (employee_Details) is used as a vector type. The entire structure is "stored" in 1 index, and we only need to enter the required data.
	// Example: if the struct's member called "employee_name" is called i.e employee 
	//{} the brackets at the end are needed.
	
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
void inspect_Employee(int pos);
void sort_Employee(int foo_mode);
void first_start();

int generate_ID();
int read_params();

	//Short documentation:
	// read_Employee contains code that will clear all vectors first and then populate the "employee" vector
	// list_Employee contains the code that will list down the data inside the vectors.
	// inspect_Employee will enable editing employee details
	// input_employeeWorkDetails enable adding/appending new employees
	// write_Employee is for writing to a file
	// update_Employee updates/overwrites the text file with the changed information (which should never be called before read_Employee)


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
		employee_number = read_params();
		read_Employee("Names");
		list_Employee("Names");

		std::cout << "\n\nNumber of Employees: " << employee_number << std::endl;
		std::cout << "========Menu========\n\n";
		std::cout << "1. Show list of all employees again." << std::endl;
		std::cout << "2. Add an employee." << std::endl;
		std::cout << "3. Inspect an employee and edit details." << std::endl;
		std::cout << "4. Search employee." << std::endl;
		std::cout << "5. Remove employee." << std::endl;
		std::cout << "6. Sort employees." << std::endl;
		std::cout << "\n345. Reset all wages and clocked hours." << std::endl;
		
		
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
		
		
		
	switch(choice_menu){
		case 10:
			{	
				system("CLS");
				std::cin.ignore(256, '\n');
				write_Employee(0);
			break;
			}
		
		case 1:
			{
				system("CLS");
				std::cout << "List of Employees: " << std::endl;
				std::cin.ignore(256, '\n');	
					read_Employee("Names");
					list_Employee("Names");
				std::cout << "\n\n";
			break;
			}
			
		case 2:
			{
				system("CLS");
				std::cin.ignore(256, '\n');
					write_Employee(2);
			break;
			}
			
			
		case 3:
			{
				system("CLS");
				std::string name_inspect;
				int save_position=0;
			
				std::cin.ignore(256, '\n');
	
					read_Employee("Names"); //to populate the vector
					list_Employee("Names");
					std::cout << "Input name or ID: ";
					getline(std::cin, name_inspect);
					for(int i=0; i<employee.size(); i++){
						if(name_inspect==employee[i].name || name_inspect==employee[i].ID){
							save_position=i;
						}
					}
					
					inspect_Employee(save_position);
					std::cout << "\nUpdated the employee: " << employee[save_position].name << "\n\n";
					update_Employee();
					system("PAUSE");
					system("CLS");
				break;
			}
			
		case 4:{
			
			break;
		}
		
		case 5:
			{
				std::cin.ignore(256, '\n');
				std::string remove_employee;
				system("CLS");
				read_Employee("Names"); //to populate the employee vector
				list_Employee("Names");
				std::cout << "\nWhich employee do you want to remove [input ID or Name]? ";
				getline(std::cin, remove_employee);
					for(int i=0; i<employee.size(); i++){
						if(remove_employee==employee[i].name || remove_employee==employee[i].ID){
							employee.erase(employee.begin()+i);
						}
					}
					
				update_Employee();
				employee_number--;
				
					write_Text.open("Params.txt");
					write_Text << employee_number;
					write_Text.close();
				
				std::cout << "\n\nEmployee removed.\n\n";
				system("PAUSE");
				system("CLS");
				break;
			}
			
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
				
		case 345:
			{
				std::cin.ignore(256, '\n');
				system("CLS");
					read_Employee("Names"); //to populate and clear the employee vector
					list_Employee("Names");
				for(int i=0; i<employee.size(); i++){
					employee[i].salary = 0;
					employee[i].workTime = 0;
					employee[i].totalPayment = 0;
				}
				update_Employee();
				system("CLS");
				break;
			}
		
		
		case 8:
			{
				program_run=false;
				return 0;
			}
			
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
	std::cout << std::setw(20) << "1. Name: " <<  employee[pos].name << std::endl;
	std::cout << std::setw(20) << "2. ID: " <<  employee[pos].ID << std::endl;
	std::cout << std::setw(20) << "3. Position: " << employee[pos].position << std::endl;
	std::cout << std::setw(20) << "4. Salary: " <<  employee[pos].salary << std::endl;
	std::cout << std::setw(20) << "5. Hours Worked: " << employee[pos].workTime << std::endl;
	std::cout << std::setw(20) << "6. Wage due: " << employee[pos].totalPayment << std::endl;
	std::cout << std::setw(20) << "7. Leave Status: " << employee[pos].leaveStatus << std::endl;
	std::cout << "\nWhich information do you want to update [0 to exit]: ";
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
			std::cin.ignore(256, '\n');
			std::cout << "\nID cannot be edited.";
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
			write_Text << employee[i].ID << std::endl;	//ID
			write_Text << employee[i].position << std::endl;		//position
			write_Text << employee[i].salary << std::endl;		//salary
			write_Text << employee[i].workTime << std::endl;						//workTime
			write_Text << employee[i].totalPayment << std::endl;						//totalPayment
			write_Text << employee[i].leaveStatus << std::endl;					//Leavestatus
	}
	write_Text.close();
}


void write_Employee(int foo_mode){
	//inputs for relevant, new hire details
	std::string input_textName;
	std::string input_textPosition;
	std::string input_hourlySalary;
	
	int choice_add;
	int write_run=1;
	
	
		
	switch(foo_mode){
	
	//case 0, overwrite entire file
	case 0:
		{
			write_Text.open("Employees.txt");
			
			employee_number = 0;
			//To write the very first employee, we need to have an existing parameter "0". So we write 0 into Params.txt.
			write_Text2.open("Params.txt");
			write_Text2 << 0;
			write_Text2.close();
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
		std::cout << std::left << std::setw(5) << "No." << std::setw(20) << "Name" << std::setw(15) << "ID" << std::setw(15) << "Position";
		std::cout << std::setw(10) << "Hourly" << std::setw(10) << "Clock-in" << std::setw(10) << "Payment" << std::setw(10) << "Leave Status" << "\n";
		for(int i = 0; i < employee_number; i++){
			employee[i].totalPayment = employee[i].salary * employee[i].workTime;
			
			std::cout << std::left << std::setw(5) << i+1 << std::setw(20) << employee[i].name << std::setw(15) << employee[i].ID << std::setw(15) << employee[i].position;
			std::cout << std::setw(10) << employee[i].salary << std::setw(10) << employee[i].workTime << std::setw(10) << employee[i].totalPayment << std::setw(10) << employee[i].leaveStatus << std::endl;
					
					
					
					
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
			write_Text << "A23-" << generate_ID() << std::endl;	//ID
			write_Text << input_textPosition << std::endl;		//position
			write_Text << input_hourlySalary << std::endl;		//salary
			write_Text << "0" << std::endl;						//workTime
			write_Text << "0" << std::endl;						//totalPayment
			write_Text << "No." << std::endl;					//Leavestatus
			
			//parameter updating
			write_Text2.open("Params.txt");
			write_Text2 << employee_number;
			write_Text2.close();
			
			
			std::cin.ignore(256, '\n');
			
		}while(flag_inputDetails==true);
	

	
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


int read_params(){
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