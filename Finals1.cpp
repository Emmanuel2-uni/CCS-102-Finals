#include <iostream>
#include <iomanip>
#include <string>
#include <vector> 
#include <fstream> 



//global variables
int max_Size;
bool program_run = true;
int choice_menu;
//int foo_mode;


//global vectors
std::vector<int> employee_ID;
std::vector<std::string> employee_Names;

std::vector<float> employee_Salaries;
std::vector<float> employee_Overtime;
std::vector<int> employee_WorkTimes;
std::vector<int> employee_RealAge;
std::vector<int> employee_WorkAge;
std::vector<std::string> employee_LeaveStatus;
std::vector<std::string> employee_Recognitions;


//new streams
std::ofstream write_Text;
std::ifstream read_Text;
std::fstream update_Text;


//functions
void write_Employee(int foo_mode);
void read_Employee(std::string foo_mode);
void list_Employee(std::string foo_mode);
	//foo is just a "whatever" term in the programming community for naming various things.
void clear_vectors();




int main(){
	
	do{
		//main menu
		std::cout << "========Menu========\n\n";
		std::cout << "1. List all employees." << std::endl;
		std::cout << "2. Add an employee." << std::endl;
		std::cout << "3. Inspect an employee." << std::endl;
		//std::cout << "5. Search name\n" << std::endl;
	
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
			write_Employee(1);
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
	std::string input_text;
	int write_run=1;
	
	
		
	switch(foo_mode){
	
	//case 0, overwrite entire file
	case 0:
		{
		write_Text.open("Employees_Names.txt");
		
			do{
				read_Employee("Names");
				list_Employee("Names");
				
				std::cout << "Input new Employee Name [input 0 to exit]: ";
				getline(std::cin, input_text);
					if(input_text=="0"){
						write_run=0;
						break;
					}
				write_Text << input_text << std::endl;
				system("CLS");
				
			}while(write_run==1);
			
			
			
		write_Text.close();
		break;
		}



	//case 2, add names;
	case 2:
		{ //append names
		write_Text.open("Employees_Names.txt", std::ios::app);
		
			do{
				std::cout << "List of Employees: " << std::endl;
				read_Employee("Names");
				list_Employee("Names");
				
				std::cout << "\nInput new Employee Name [input 0 to exit]: ";
				getline(std::cin, input_text);
					if(input_text=="0"){
						system("CLS");
							read_Employee("Names");
							list_Employee("Names");
						write_run=0;
						break;
					}
				write_Text << input_text << std::endl;
				system("CLS");
				
			}while(write_run==1);
			
			
			
		write_Text.close();
		break;
		} //Overwrite file end

	
	
	}
	
	
	
}


void read_Employee(std::string foo_mode){
	std::string input_name;
	
	clear_vectors();
	
	//if we only need Names
	if(foo_mode=="Names"){
		read_Text.open("Employees_Names.txt");
		while(getline(read_Text, input_name)){
			employee_Names.push_back(input_name);
		}
		read_Text.close();
	}
	
	
}


void list_Employee(std::string foo_mode){
	
	
	
	if(foo_mode=="Names"){
		for(int i = 0; i < employee_Names.size(); i++){
			std::cout << i+1 << ". " << employee_Names[i] << std::endl;
		}
	}
	
	
	
	
	
	
	
}




//handy code for clearing all vectors
void clear_vectors(){
	
	employee_ID.clear();
	employee_Names.clear();

	employee_Salaries.clear();
	employee_Overtime.clear();
	employee_WorkTimes.clear();
	employee_RealAge.clear();
	employee_WorkAge.clear();
	employee_LeaveStatus.clear();
	employee_Recognitions.clear();
}

