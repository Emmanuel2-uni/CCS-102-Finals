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
//int foo_mode;


//global vectors
std::vector<std::string> employee_Names;
//work details
std::vector<std::string> employee_ID;
std::vector<float> employee_hourlySalaries;
std::vector<std::string> employee_Position;
//work status
std::vector<float> employee_totalPayment;
std::vector<float> employee_Overtime;
std::vector<int> employee_workTimes;
std::vector<std::string> employee_leaveStatus;

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


int main(){
	
	do{
		//main menu
		std::cout << "========Menu========\n\n";
		std::cout << "1. List all employees." << std::endl;
		std::cout << "2. Add an employee." << std::endl;
		std::cout << "3. Inspect an employee." << std::endl;
		std::cout << "4. Search employee." << std::endl;
	
		std::cout << "\n\n";
		std::cout << "7. Exit." << std::endl;
		std::cout << "0. Overwrite entire employee files" << std::endl;
		
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
		write_Text.open("Employees_Names.txt");
		write_Text2.open("Employees_workDetails.txt");
		
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
		write_Text2.close();
		break;
		}



	//case 2, add names;
	case 2:
		{ //append names
		write_Text.open("Employees_Names.txt", std::ios::app);
		write_Text2.open("Employees_workDetails.txt", std::ios::app);
		
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
		write_Text2.close();
		break;
		} //Overwrite file end

	
	
	}
	
	
	
}


void read_Employee(std::string foo_mode){
	std::string input_name;
	std::string input_workDetails;
	clear_vectors();
	
	//if we only need Names, ID, Position and Hourly Salary
	if(foo_mode=="Names"){
		read_Text.open("Employees_Names.txt");
		read_Text2.open("Employees_workDetails.txt");
		
		while(getline(read_Text, input_name)){
			employee_Names.push_back(input_name);
		}
	
		for(int i=0; i<employee_Names.size(); i++){
			getline(read_Text2, input_workDetails);
				employee_ID.push_back(input_workDetails);
			getline(read_Text2, input_workDetails);
				employee_Position.push_back(input_workDetails);
			getline(read_Text2, input_workDetails);
				std::stof(input_workDetails);
				float input_hourly = std::stof(input_workDetails);
				employee_hourlySalaries.push_back(input_hourly);
		}
		
		
		read_Text.close();
		read_Text2.close();
	}
	
	//for inspecting
	if(foo_mode=="Inspect"){
		
	}
	
}


void list_Employee(std::string foo_mode){
	
	
	
	if(foo_mode=="Names"){
		std::cout << std::left << std::setw(5) << "No." << std::setw(25) << "Name" << std::setw(15) << "ID" << std::setw(15) << "Position" << std::setw(10) << "Salary per hour" << "\n";
		for(int i = 0; i < employee_Names.size(); i++){
		
			std::cout << std::left << std::setw(5) << i+1 << std::setw(25) << employee_Names[i] << std::setw(15) << employee_ID[i] << std::setw(15) << employee_Position[i] << std::setw(10) << employee_hourlySalaries[i] << std::endl;
			
			
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
			std::cout << "\nInput new Employee Name [input 0 to exit]: ";
			getline(std::cin, input_textName);
					if(input_textName=="0"){
						flag_inputDetails=false;
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
						break;
					}
					
					
			std::cin.ignore(256, '\n');
			std::cout << "\nInput new Employee's hourly salary [input 0 to exit]: ";
			std::cin >> input_hourlySalary;
					if(input_hourlySalary==0){
						flag_inputDetails=false;
						break;
					}
			
			
			write_Text << input_textName << std::endl;
			write_Text2 << "A23-" << generate_ID() << std::endl;
			write_Text2 << input_textPosition << std::endl;
			write_Text2 << input_hourlySalary << std::endl;
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
	
employee_ID.clear();
employee_Names.clear();

employee_hourlySalaries.clear();
employee_totalPayment.clear();
employee_Overtime.clear();
employee_workTimes.clear();
employee_leaveStatus.clear();
employee_Position.clear();

}




/* asdasd
			cout << left << setw(5) << "No." << setw(25) << "Name" << setw(15) << "Price" << setw(15) << "Quantity" << "\n";
			
			for (int i=0; i<=imax; i++){
				cout << left << setw(5) << i+1 << setw(25) << item[i];
				cout << fixed << setprecision(2) << setw(15) << prc[i] << setw(15) << qty[i]  << setw(15) << trtotal[i] <<"\n";
				}
				
*/
