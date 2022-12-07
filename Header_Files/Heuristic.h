#pragma once


struct solution {
	int* tour;			//This is what the fitness_evaluation function in EVRP.hpp will evaluate
	int id;
	double tour_length; //Quality of the solution
	int steps;			//Size of the solution
	int* EVs;			//steps for route
	//the format of the solution is as follows:
	//*tour:  0 - 5 - 6 - 8 - 0 - 1 - 2 - 3 - 4 - 0 - 7 - 0
	//*steps: 12
	//this solution consists of three routes: 
	//Route 1: 0 - 5 - 6 - 8 - 0
	//Route 2: 0 - 1 - 2 - 3 - 4 - 0
	//Route 3: 0 - 7 - 0
	// EVs[0]: count of route
	// EVs[1]: steps to finalize the route 1
	// EVs[2]: steps to finalize the route 2
	// EVs[3]: steps to finalize the route 3
};


extern solution* best_sol;


void initialize_heuristic();
void run_heuristic();



void free_heuristic();