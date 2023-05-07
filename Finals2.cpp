#include <iostream>
#include <iomanip>
#include <string>
#include <vector> 
#include <fstream> 
#include <random>
#include "sort_vector.h"


//global variables
bool program_run = true;
int choice_menu;
int employee_number;



//int foo_mode;

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


//new streams
std::ofstream write_Text;
std::ofstream write_Text2;
std::ifstream read_Text;
std::ifstream read_Text2;
std::fstream update_Text;


//functions
void write_Employee(int foo_mode);
void read_Employee(std::string foo_mode);
void list_Employee(std::string foo_mode);
	//foo is just a "whatever" term in the programming community for naming various things.
void clear_vectors();
void input_employeeWorkDetails();
int generate_ID();
int read_params();



int main(){

	do{
		//main menu
		employee_number = read_params();
		read_Employee("Names");
		list_Employee("Names");

		std::cout << "\n\nNumber of Employees: " << employee_number << std::endl;
		std::cout << "========Menu========\n\n";
		std::cout << "1. List all employees." << std::endl;
		std::cout << "2. Add an employee." << std::endl;
		std::cout << "3. Inspect an employee." << std::endl;
		std::cout << "4. Search employee." << std::endl;
	
		std::cout << "\n\n";
		std::cout << "7. Exit." << std::endl;
		std::cout << "0. Overwrite/Make new entire employee files" << std::endl;
		
		std::cout << "\n\nEnter choice: ";
		std::cin >> choice_menu;	
		
		
	switch(choice_menu){
		case 0:
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
			std::cin.ignore(256, '\n');
			read_Employee("Inspect");
			}
			
			
			
			
			
		case 7:
			{
			program_run=false;
			return 0;
			}
		
	}
		
	}while(program_run==true);
	
	
	return 0;
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
			//To write the very first employee, we need to have an existing parameter "1". So we write 1 into Params.txt.
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
	
	
	clear_vectors();
	
	
	//if we only need Names, ID, Position and Hourly Salary
	if(foo_mode=="Names"){
		read_Text.open("Employees.txt");
		
		
		for(int i=0; i<employee_number; i++){
			getline(read_Text, read_name);
			getline(read_Text, read_ID);
			getline(read_Text, read_position);
			
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
	
	//for inspecting
	if(foo_mode=="Inspect"){
		
	}
	
}


void list_Employee(std::string foo_mode){
	
	
	if(foo_mode=="Names"){
		std::cout << std::left << std::setw(5) << "No." << std::setw(20) << "Name" << std::setw(15) << "ID" << std::setw(15) << "Position";
		std::cout << std::setw(10) << "Hourly" << std::setw(10) << "Clock-in" << std::setw(10) << "Payment" << std::setw(10) << "Leave Status" << "\n";
		for(int i = 0; i < employee_number; i++){
		
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
		std::string full_ID;
		
		std::random_device rd;
		//std::default_random_engine rand(rd()); //opinion: not "random" enough.
		std::mt19937 rand(rd()); //opinion: decently "random".
		std::uniform_int_distribution<int> random_number(10000, 99999); //for uniform distribution.
		random_ID = random_number(rand);

		return random_ID;
		
}

//handy function for clearing all vectors
void clear_vectors(){

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
