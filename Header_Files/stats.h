#pragma once
#define MAX_TRIALS 	30
#define CHAR_LEN 100

void open_stats(void);									//creates the output file
void close_stats(void);									//stores the best values for each run
void get_mean(int r, double value);						//stores the observation from each run
void free_stats();										//free memory

