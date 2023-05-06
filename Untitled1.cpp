#include <iostream>
#include <vector>
#include "sort_vector.h"
int main(){
	
	std::vector<int> test_sort = {11, 234, 13, 5, 10, 123};
	std::vector<int> test_vect;
	
	test_vect = sort(test_sort);
	
	for(int i=0; i<test_vect.size(); i++){
		std::cout << test_vect[i] << std::endl;
	}
	
	
	return 0;
}