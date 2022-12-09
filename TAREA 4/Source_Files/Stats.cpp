
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include<cmath>
#include<iostream>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<math.h>
#include<fstream>
#include<time.h>
#include<limits.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../Header_Files/EVRP.h"
#include "../Header_Files/stats.h"

using namespace std;

//Used to output offline performance and population diversity

FILE* log_performance;
//output files
char* perf_filename;
double* perf_of_trials;

void open_stats(void) {
    //Initialize
    perf_of_trials = new double[MAX_TRIALS];

    for (int i = 0; i < MAX_TRIALS; i++) {
        perf_of_trials[i] = 0.0;
    }

    //initialize and open output files
    perf_filename = new char[CHAR_LEN];
    
    // Delete extention .evrp
    int s = (int)strlen(problem_instance);
        problem_instance[s - 1] = NULL;
        problem_instance[s - 2] = NULL;
        problem_instance[s - 3] = NULL;
        problem_instance[s - 4] = NULL;
        problem_instance[s - 5] = NULL;

    strcpy(perf_filename, problem_instance);		//Copy instances name
    strcat(perf_filename, "_stats.txt");	    	//Add extention .txt	
    
    //for performance
    if ((log_performance = std::fopen(perf_filename, "a")) == NULL) { exit(2); }
    //initialize and open output files

    cout << "\n-> Running Instance " << problem_instance << endl;
}


void get_mean(int r, double value) {

    perf_of_trials[r] = value;

}


double mean(double* values, int size) {
    int i;
    double m = 0.0;
    for (i = 0; i < size; i++) {
        m += values[i];
    }
    m = m / (double)size;
    return m; //mean
}

double stdev(double* values, int size, double average) {
    int i;
    double dev = 0.0;

    if (size <= 1)
        return 0.0;
    for (i = 0; i < size; i++) {
        dev += ((double)values[i] - average) * ((double)values[i] - average);
    }
    return sqrt(dev / (double)(size - 1)); //standard deviation
}

double best_of_vector(double* values, int l) {
    double min;
    int k;
    k = 0;
    min = values[k];
    for (k = 1; k < l; k++) {
        if (values[k] < min) {
            min = values[k];
        }
    }
    return min;
}


double worst_of_vector(double* values, int l) {
    double max;
    int k;
    k = 0;
    max = values[k];
    for (k = 1; k < l; k++) {
        if (values[k] > max) {
            max = values[k];
        }
    }
    return max;
}



void close_stats(void) {
    int i;
    double perf_mean_value, perf_stdev_value;

    //For statistics
    for (i = 0; i < MAX_TRIALS; i++) {
        //cout << i << " " << perf_of_trials[i] << endl;
        //cout << i << " " << time_of_trials[i] << endl;
        fprintf(log_performance, "%.2f", perf_of_trials[i]);
        fprintf(log_performance, "\n");

    }

    perf_mean_value = mean(perf_of_trials, MAX_TRIALS);
    perf_stdev_value = stdev(perf_of_trials, MAX_TRIALS, perf_mean_value);
    fprintf(log_performance, "Mean %f\t ", perf_mean_value);
    fprintf(log_performance, "\tStd Dev %f\t ", perf_stdev_value);
    fprintf(log_performance, "\n");
    fprintf(log_performance, "Min: %f\t ", best_of_vector(perf_of_trials, MAX_TRIALS));
    fprintf(log_performance, "\n");
    fprintf(log_performance, "Max: %f\t ", worst_of_vector(perf_of_trials, MAX_TRIALS));
    fprintf(log_performance, "\n");


    fclose(log_performance);


}


void free_stats() {

    //free memory
    delete[] perf_of_trials;

}


