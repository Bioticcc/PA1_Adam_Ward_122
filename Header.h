/*
Author: Adam T Ward
Date: 5/8/2024
Description: PA_1 for CptS 122
*/


#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//required structs
typedef enum sleep {
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;
typedef struct fitbit {
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;

typedef struct maxstep {
	char minute[9];
	unsigned int steps;
} maxStep;


//read file
int readInput(FILE* input, FitbitData *arr, FitbitData* arrProblemChildren);

//better strtok()
char* stok(char** p, const char* delim);

//total calories burned, distance walked, floors walked, steps taken
double totalCal(FitbitData* arr);
double totalDis(FitbitData *arr);
double totalFloors(FitbitData* arr);
double totalSteps(FitbitData *arr);

//avg heart rate
double avgHeart(FitbitData * arr);

//max step
char* maxSteps(FitbitData* arr, maxStep* activity);

//worst sleep
char worstSleep(FitbitData* arr, char* worstSleepS);


//writing to results.csv
int writeOutput(FitbitData* arr, FILE* output, maxStep* activity, double Cal, double Dist, double Floors, double Steps, double Heart, char* worstSleepS, FitbitData* arrProblemChildren);


