/* Author: Nick Nesbit
 * Date: 4/4/2018
 * CS4300: Project 3
 * Simple GA: individual.h
 */

#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <string>

//Data structure for an individual
typedef struct Individual {
	std::string pattern;
	int fitness;
} Individual;

#endif /* INDIVIDUAL_H_ */
