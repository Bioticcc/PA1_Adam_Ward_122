#include "Header.h"

int main() {
	//declaring arrays
	maxStep activity[1440] = { 0 };//for tracking max steps ig
	FitbitData arr[1440]; 
	FitbitData arrProblemChildren[1440]; //for the removed, duped, and other shitty lines
	//opening FitbitData.csv in read mode
	FILE* input = fopen("FitbitData.csv", "r");
	if (input == NULL) {
		printf("File failed to open...");
		return 1;
	}
	else printf("FitbitData.csv opened successfully!\n\n");
	FILE* output = fopen("Results.csv", "w");
	if (output == NULL) {
		printf("File failed to open...");
		return 1;
	}
	else printf("Results.csv opened successfully!\n\n");


	//reading from the CSV
	readInput(input, arr, arrProblemChildren);
	/*
	for (int i = 0; i < 1440; i++) {
		if (strcmp(arrProblemChildren[i].patient, "") != 0) {
			printf("\narrProblemChildren[%d] = |%s\t|%s\t|%lf\t|%lf\t|%d\t|%d\t|%d\t|%d\t|\n", i, arrProblemChildren[i].patient, arrProblemChildren[i].minute, arrProblemChildren[i].calories, arrProblemChildren[i].distance, arrProblemChildren[i].floors, arrProblemChildren[i].heartRate, arrProblemChildren[i].steps, arrProblemChildren[i].sleepLevel);
		}
	}
	*/
	//calculating totals
	double totalCalV = totalCal(arr);
	double totalDistV = totalDis(arr);
	double totalFloorsV = totalFloors(arr);
	double totalStepsV = totalSteps(arr);

	//calculating avg heart rate
	double avgHeartV = avgHeart(arr);

	//calculating max steps (highest activity levels ig?)
	maxSteps(arr, activity);

	//calculating longest range of poor sleep
	char* worstSleepS[100];
	worstSleep(arr, worstSleepS);
	//printf("\nTesting worstSleepS: %s", worstSleepS);
	
	
	
	//writing to results.csv
	writeOutput(arr, output, activity, totalCalV, totalDistV, totalFloorsV, totalStepsV, avgHeartV, worstSleepS, arrProblemChildren);

	//closing files
	fclose(input);
	fclose(output);

	return 1;
}