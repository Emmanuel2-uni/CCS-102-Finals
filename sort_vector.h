#include <vector>
#include <iostream>
#include <numeric>

std::vector<int> sort(std::vector<int> first_vector){
	std::vector<int> second_vector = first_vector;
	
	for(int current=0; current<first_vector.size(); current++){
		
		for(int swap=current; swap<first_vector.size(); swap++){
			
			if(first_vector[current] >= second_vector[swap]){
				first_vector[current] = second_vector[swap]; 
				first_vector[swap] = second_vector[current]; 
				
				
					for(int i=0; i<first_vector.size(); i++){
						second_vector[i]=first_vector[i];
							
					}
	
				}
			
		}
		
	}
		return first_vector;
}