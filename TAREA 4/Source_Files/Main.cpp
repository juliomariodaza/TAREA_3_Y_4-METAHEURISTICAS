#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS1
#include<iostream>
#include<stdlib.h>
#include<limits.h>

#include <string.h> 
#include <stdio.h>

#include "../Header_Files/EVRP.h"
#include "../Header_Files/Multi-Start.h"
#include "../Header_Files/stats.h"

using namespace std;


/*initialiazes a run for your heuristic*/
void start_run(int r) {

    srand(r); //random seed
    init_evals();
    init_current_best();
    //cout << "\n->Run: " << r << " with random seed " << r << endl;
    cout << " - Running Trial: " << r << endl;
}

/*gets an observation of the run for your heuristic*/
void end_run(int r) {

    get_mean(r - 1, get_current_best()); //from stats.h
    //cout << "\nEnd of run " << r << " with best solution quality " << get_current_best() << " and " << get_evals() << " total evaluations. " << endl;
    cout << "\tEnd of run " << r << ", with best solution quality " << get_current_best();
    cout << " " << endl;
}

/*sets the termination conidition for your heuristic*/
bool termination_condition(void) {

    bool flag;
    if (get_evals() >= TERMINATION)
        flag = true;
    else
        flag = false;

    return flag;
}


/****************************************************************/
/*                Main Function                                 */
/****************************************************************/
int main(int argc, char* argv[]) {

    /*Step 1*/
    problem_instance = argv[1];     //Pass the .evrp filename as an argument
    read_problem(problem_instance); //Read EVRP from file from EVRP.h

    /*Step 2*/
    open_stats();                   //Open text files to store the best values from the 30 runs stats.h

    for (int run = 1; run <= MAX_TRIALS; run++) {
        /*Step 3*/
        start_run(run);
        initialize_Multi_Start();     //Multi_Start.h 

        /*Step 4*/
        //while (!termination_condition())
        //    run_Multi_Start();        //Execute Multi_Start | Multi_Start.h
        //run_Local_Search();

        while (!termination_condition())
        {
            run_Multi_Start();        //Execute Multi_Start | Multi_Start.h
            run_Local_Search();
        }

                       
        //print_solution(best_sol->tour,best_sol->steps);         
       //check_solution(best_sol->tour,best_sol->steps);
        

        /*Step 5*/
        end_run(run);               //Store the best solution quality for each run
    }
    
    /*Step 6*/
    close_stats();                  //Close text files to calculate the mean result from the 30 runs stats.h

    //free memory
    free_stats();
    free_Multi_Start();
    free_EVRP();

    return 0;
}
