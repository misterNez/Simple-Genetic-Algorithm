/* Author: Nick Nesbit
 * Date: 4/4/2018
 * CS4300: Project 3
 * Simple GA: main.cpp
 */

//#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>

#include "individual.h"

using namespace std;

//Start of main program
int main() {

	//Seed the random number generator
	srand(time(0));

	//Initialize the population size and string size
	int popSize = 10;
	int stringSize = 0;

	//Declare upperBound and lowerBound varibles
	int upperBound = 81920;
	int lowerBound = 10;

	//Pass variable determines if the global optimum was found
	int pass;

	//Get the string size from user
	do {
		cin.clear();
		cout << "Enter the size of the string (2 - 50): ";
		cin >> stringSize;
		cin.ignore();
	} while ( stringSize < 2 || stringSize > 50 );

	//Termination loop
	bool fail = true;
	while ( popSize < 81920 && fail == true ) {
		//Display population size
		cout << endl << "Population size: " << popSize << endl;

		//Set pass to 0
		pass = 0;

		//Procedural loop
		for ( int count = 0; count < 5; count++ ) {
			//Display the round number
			cout << endl << "Round: " << count+1 << endl;

			//Randomly initialize the population:
			Individual* pop = new Individual[popSize];
			cout << " Original population: " << endl;
			for ( int i = 0; i < popSize; i++ ) {
				pop[i].pattern = "";
				pop[i].fitness = 0;
				for ( int j = 0; j < stringSize; j++) {
					if ( (rand()%2) == 0 ) {
						pop[i].pattern += '0';
					}
					else {
						pop[i].pattern += '1';
						pop[i].fitness++;
					}
				}
			}

			//Declare utility variables
			int totalFitness;
			int lowFitness;
			int highFitness;
			float avgFitness;
			float maxAvgFitness = 0.0;
			int numGens = 0;
			int itr = 0;

			//Generational loop
			while ( itr < 3 ) {
				//Increment number of generations
				numGens++;

				//Initialize fitness values
				totalFitness = 0;
				highFitness = 0;
				lowFitness = stringSize + 1;

				//Calculate fitness information
				for ( int i = 0; i < popSize; i++ ) {
					totalFitness += pop[i].fitness;
					if ( pop[i].fitness > highFitness )
						highFitness = pop[i].fitness;
					if ( pop[i].fitness < lowFitness)
						lowFitness = pop[i].fitness;
				}
				avgFitness = ((float)totalFitness) / popSize;

				//Handle termination details
				if ( avgFitness > maxAvgFitness ) {
					maxAvgFitness = avgFitness;
					itr = 0;
				}
				else {
					itr++;
				}

				//Display fitness information
				cout << "  Highest fitness: " << highFitness << endl;
				for ( int i = 0; i < popSize; i++ ) {
					if ( pop[i].fitness == highFitness)
						cout << "    " << pop[i].pattern << endl;
				}
				cout << "  Lowest fitness: " << lowFitness << endl;
				for ( int i = 0; i < popSize; i++ ) {
					if ( pop[i].fitness == lowFitness)
						cout << "    " << pop[i].pattern << endl;
				}
				cout << "  Average fitness: " << std::setprecision(3) << avgFitness << endl << endl;

				//Create a new array of parents
				int parentSize = (popSize - 2) / 2;
				Individual* parents = new Individual[parentSize];

				//Selection:
				for ( int i = 0; i < parentSize; i++ ) {
					int a = rand() % popSize;
					int b = rand() % popSize;
					while (b == a)
						b = rand() % popSize;

					if (pop[a].fitness >= pop[b].fitness)
						parents[i] = pop[a];
					else
						parents[i] = pop[b];
				}

				//Create a new array of children
				int childrenSize = popSize - 2;
				Individual* children = new Individual[childrenSize];

				//Recombination:
				for ( int i = 0; i < childrenSize; i += 2 ) {
					int p = rand() % parentSize;
					int q = rand() % parentSize;
					while ( q == p )
						q = rand() % parentSize;

					//Direct Copy
					if ( (rand()%10 + 1) < 5 ) {
						children[i].pattern = "";
						children[i].fitness = 0;
						children[i+1].pattern = "";
						children[i+1].fitness = 0;
						for (int j = 0; j < stringSize; j++ ) {
							//Generate child 1
							int mutation = rand() % stringSize;
							if ( mutation == 0 && parents[p].pattern[j] == '0' ) {
								children[i].pattern += '1';
								children[i].fitness++;
							}
							else if ( mutation == 0 && parents[p].pattern[j] == '1' ) {
								children[i].pattern += '0';
							}
							else if ( mutation > 0) {
								children[i].pattern += parents[p].pattern[j];
								if ( parents[p].pattern[j] == '1')
									children[i].fitness++;
							}
							//Generate child 2
							mutation = rand() % stringSize;
							if ( mutation == 0 && parents[q].pattern[j] == '0' ) {
								children[i+1].pattern += '1';
								children[i+1].fitness++;
							}
							else if ( mutation == 0 && parents[q].pattern[j] == '1' ) {
								children[i+1].pattern += '0';
							}
							else if ( mutation > 0) {
								children[i+1].pattern += parents[q].pattern[j];
								if ( parents[q].pattern[j] == '1')
									children[i+1].fitness++;
							}
						}
					}

					//Crossover
					else {
						children[i].pattern = "";
						children[i].fitness = 0;
						children[i+1].pattern = "";
						children[i+1].fitness = 0;
						for ( int j = 0; j < stringSize; j++ ) {
							//Generate child 1
							int mutation = rand() % stringSize;
							if ( (rand()%2) == 0 ) {
								if ( mutation == 0 && parents[p].pattern[j] == '0' ) {
									children[i].pattern += '1';
									children[i].fitness++;
								}
								else if ( mutation == 0 && parents[p].pattern[j] == '1') {
									children[i].pattern += '0';
								}
								else if ( mutation > 0 ) {
									children[i].pattern += parents[p].pattern[j];
									if ( parents[p].pattern[j] == '1' )
										children[i].fitness++;
								}
							}
							else {
								if ( mutation == 0 && parents[q].pattern[j] == '0' ) {
									children[i].pattern += '1';
									children[i].fitness++;
								}
								else if ( mutation == 0 && parents[q].pattern[j] == '1' ) {
									children[i].pattern += '0';
								}
								else if ( mutation > 0 ) {
									children[i].pattern += parents[q].pattern[j];
									if ( parents[q].pattern[j] == '1' )
										children[i].fitness++;
								}
							}
							//Generate child 2
							mutation = rand() % stringSize;
							if ( children[i].pattern[j] == '1') {
								if ( mutation != 0 ) {
									children[i+1].pattern += '0';
								}
								else {
									children[i+1].pattern += '1';
									children[i+1].fitness++;
								}

							}
							else {
								if ( mutation != 0 ) {
									children[i+1].pattern += '1';
									children[i+1].fitness++;
								}
								else {
									children[i+1].pattern += '0';
								}
							}
						}
					}
				}

				//Replacement:

				//temps hold the most fit individuals in the current population
				Individual temp1;
				Individual temp2;

				//max and next hold the two highest fitness values in the current population
				int max = 0;
				int next = 0;

				//first and second hold the index values of the most fit individuals
				int first = -1;
				int second = -1;

				//Find the most fit individual
				for ( int i = 0; i < popSize; i++ ) {
					if ( pop[i].fitness >= max ) {
						max = pop[i].fitness;
						temp1 = pop[i];
						first = i;
					}
				}

				//Find the next fit individual
				for ( int i = 0; i < popSize; i++ ) {
					if ( pop[i].fitness == max && i != first) {
						temp2 = pop[i];
						second = i;
					}
				}
				if ( second == -1) {
					for ( int i = 0; i < popSize; i++ ) {
						if ( pop[i].fitness > next && pop[i].fitness < max ) {
							next = pop[i].fitness;
							temp2 = pop[i];
							second = i;
						}
					}
				}

				//Update the population
				for ( int i = 0; i < childrenSize; i++ )
					pop[i] = children[i];
				pop[popSize-2] = temp1;
				pop[popSize-1] = temp2;

				cout << " Generation: " << numGens << endl;

				//Delete the allocated memory
				delete [] children;
				delete [] parents;
			}
			//End of generational loop

			//Display fitness information
			cout << "  Highest fitness: " << highFitness << endl;
			for ( int i = 0; i < popSize; i++ ) {
				if ( pop[i].fitness == highFitness)
					cout << "    " << pop[i].pattern << endl;
			}
			cout << "  Lowest fitness: " << lowFitness << endl;
			for ( int i = 0; i < popSize; i++ ) {
				if ( pop[i].fitness == lowFitness)
					cout << "    " << pop[i].pattern << endl;
			}
			cout << "  Average fitness: " << std::setprecision(4) << avgFitness << endl << endl;

			//Check if global optimum was found
			for ( int i = 0; i < popSize; i++ ) {
				if ( pop[i].fitness == stringSize ) {
					pass++;
					break;
				}
			}
			//Delete allocated memory
			delete [] pop;
		}
		//End of procedural loop

		if ( pass != 5) {
			lowerBound = popSize;
			popSize *= 2;
		}
		else {
			upperBound = popSize;
			fail = false;
		}
	}
	//End termination loop

	//Display results
	cout << "Process terminating at population size of " << popSize << endl;
	if ( fail == false )
		cout << "Status: Success";
	else if ( popSize >= 81920)
		cout << "Status: Fail";
	else
		cout << "Status: Unknown";

	//End program
	return 0;
}
//End of main program
