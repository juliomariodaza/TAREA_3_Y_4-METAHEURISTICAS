#include<cmath>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<math.h>
#include<fstream>
#include<limits.h>

#include "../Header_Files/Heuristic.h"
#include "../Header_Files/EVRP.h"

using namespace std;


solution* best_sol;   //see heuristic.hpp for the solution structure

/*initialize the structure of your heuristic in this function*/
void initialize_heuristic() 
{
    best_sol = new solution;
    best_sol->tour = new int[NUM_OF_CUSTOMERS + 1000];
    best_sol->id = 1;
    best_sol->steps = 0;
    best_sol->tour_length = INT_MAX;
    best_sol->EVs = new int[MIN_VEHICLES * 2];
}


/*implement your heuristic in this function*/
void run_heuristic() {

    /*Generate a random solution for the random heuristic*/
    int i, help, object, tot_assigned = 0;
    int* r;
    double energy_temp = 0.0;
    double capacity_temp = 0.0;
    int from, to, temp_int, trucks = 0;
    int charging_station;
    double temp_double;

    r = new int[NUM_OF_CUSTOMERS + 1];
    
    //Set indexes of objects
    for (i = 1; i <= NUM_OF_CUSTOMERS; i++)
    {
        r[i - 1] = i;
    }
      
     //Randomly change indexes of objects
    for (i = 0; i <= NUM_OF_CUSTOMERS; i++) 
    {
        object = (int)((rand() / (RAND_MAX + 1.0)) * (double)(NUM_OF_CUSTOMERS - tot_assigned));
        help = r[i];
        r[i] = r[i + object];
        r[i + object] = help;
        tot_assigned++;
    }

    // Initialize the route
    best_sol->steps = 0;
    best_sol->tour_length = INT_MAX;
    best_sol->tour[0] = DEPOT;
    best_sol->steps++;
    best_sol->EVs[0] = 1;

    i = 0;
    while (i < NUM_OF_CUSTOMERS) 
    {
        from = best_sol->tour[best_sol->steps - 1];
        to = r[i];

        //double DEMANDA = (capacity_temp + get_customer_demand(to));
        //double BATERIA = (energy_temp + get_energy_consumption(from, to));
        
        if ((capacity_temp + get_customer_demand(to)) <= MAX_CAPACITY && (energy_temp + get_energy_consumption(from, to)) <= 0.8*BATTERY_CAPACITY) 
        {// EV have CAPACITY and BATTERY
            capacity_temp += get_customer_demand(to);
            energy_temp += get_energy_consumption(from, to);
            best_sol->tour[best_sol->steps] = to;
            best_sol->steps++;
            i++;
        }
        else if ((capacity_temp + get_customer_demand(to)) > MAX_CAPACITY) 
        {// EV not have CAPACITY
            capacity_temp = 0.0;
            energy_temp = 0.0;
            best_sol->tour[best_sol->steps] = DEPOT;
            best_sol->steps++;
            trucks++;
            best_sol->EVs[trucks] = best_sol->steps;
        }
        else if (energy_temp + get_energy_consumption(from, to) > 0.8*BATTERY_CAPACITY) 
        {// EV not have BATTERY
            temp_double = (double)BATTERY_CAPACITY; 
            charging_station = rand() % (ACTUAL_PROBLEM_SIZE - NUM_OF_CUSTOMERS - 1) + NUM_OF_CUSTOMERS + 1;
            for (int ii = (NUM_OF_CUSTOMERS + 2); ii <= ACTUAL_PROBLEM_SIZE; ii++)
            {
                if (get_energy_consumption(from, to) < temp_double && (energy_temp + get_energy_consumption(from, to)) <= BATTERY_CAPACITY)
                {
                    temp_double = get_energy_consumption(from, to);
                    charging_station = ii;
                }
            }            
            if (is_charging_station(charging_station) == true) 
            {
                energy_temp = 0.0;
                best_sol->tour[best_sol->steps] = charging_station;
                best_sol->steps++;
            }
        }else 
        {
            if (best_sol->steps > 1)
            {
                capacity_temp = 0.0;
                energy_temp = 0.0;
                best_sol->tour[best_sol->steps] = DEPOT;
                best_sol->steps++;
                trucks++;
                best_sol->EVs[trucks] = best_sol->steps;
            }

        }//End-if ((capacity_temp + get_customer_demand(to)) <= MAX_CAPACITY && (energy_temp + get_energy_consumption(from, to)) <= 0.8*BATTERY_CAPACITY)
    }//End-while (i < NUM_OF_CUSTOMERS)

    //Close EVRP tour to return back to the depot
    if (best_sol->tour[best_sol->steps - 1] != DEPOT)
    {
        best_sol->tour[best_sol->steps] = DEPOT;
        best_sol->steps++;
        trucks++;
        best_sol->EVs[trucks] = best_sol->steps;
    }

    best_sol->EVs[0] = trucks;

    best_sol->tour_length = fitness_evaluation(best_sol->tour, best_sol->steps);

    //free memory
    delete[] r;

}


/*free memory structures*/
void free_heuristic() 
{
    delete[] best_sol->tour;
    delete[] best_sol->EVs;
}

