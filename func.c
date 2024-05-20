#include "Header.h"

//better strtok()
char* stok(char** p, const char* delim) {
	if (*p == NULL) return NULL;
	char* s = *p;
	char* e = s + strcspn(s, delim);

	if (*e) {
		*e++ = '\0';
		*p = e;
	}
	else {
		*p = NULL;
	}

	return s;
}
//first, Im going to just read everything in the csv into arr, and replace any NULL's/empties with 0
readInput(FILE* input, FitbitData* arr, FitbitData* arrProblemChildren){

	int bad = 0;
	int j = 0;
	int line = 1;
	int i = 0;
	char patientI[500];

	fgets(patientI, 100, input);
	fgets(patientI, 100, input); 

	/*
	char* tok = strtok(patientI, ",");
	tok = strtok(NULL, ",");
	char target[10] = "12cx7";
	strcpy(target, tok); //should give me the target person
	*/
	char target[10] = "12cx7";
	printf("Target: %s\n", target);

	//fgets(patientI, 100, input); //just getting the next line because its title.

	//printf("Line\t\t|Patient\t|Minute\t\t|Calories\t|Distance\t|Floors\t|HR\t|Steps\t|SL\t|\n");
	//just using fgets twice on the top line of the file to skip past the two title thingies
	line = 3; //represents the line of the file we starting at
	char* tok;
 	while (fgets(patientI, 500, input)!=NULL) {
		bad = 0;
		//if (i >= 1440) return 0;
		//printf("Current line: %d\n", line);
		int a = 1;
		//skipping first two lines cause its just nonsense titles n such
			int c = 0;
			for (char* p = patientI; (tok = stok(&p, ",\n")); ) {			
				switch (c)
				{
				case 0:
					//target field
					if (strcmp(tok, target) != 0) { 
						//printf("\nSkipping line...\n line:%d, String:%s, Index in arr:%d\n", line, tok, i);
						//system("pause");
						bad = 1;
						strcpy(arrProblemChildren[j].patient, tok);
						a = 0; 
						c++;

						break; }
					else if (strcmp(tok, target) == 0) { strcpy(arr[i].patient, tok);  }
					//printf("[%d]", strlen(tok));
					//printf("[%d]: %s - %s\n", i,tok, arr[i].patient);
					c++;
					break;
				case 1:
					//minutes field
					if (bad) { strcpy(arrProblemChildren[j].minute, tok); }

					strcpy(arr[i].minute, tok);
					c++;
					break;
				case 2:
					//calories field
					if (bad) {arrProblemChildren[j].calories = strtod(tok, NULL);}

					if (strlen(tok) == 0) {
						arr[i].calories = -1;
						c++;
						break;
					}
					arr[i].calories = strtod(tok, NULL);
					//printf("[%d]", strlen(tok));
					c++;
					break;
				case 3:
					//distance field
					if (bad) { arrProblemChildren[j].distance = strtod(tok, NULL); }

					if (strlen(tok) == 0) {
						arr[i].distance = -1;
						c++;
						break;
					}
					arr[i].distance = strtod(tok, NULL);
					//printf("[%d]", strlen(tok));

					c++;
					
					break;
				case 4:
					//floors field
					if (bad) { arrProblemChildren[j].floors = atoi(tok); }

					if (strlen(tok) == 0) {
						arr[i].floors = -1;
						break;
					}
					arr[i].floors = atoi(tok);
					//printf("[%d]", strlen(tok));
					c++;
					break;
				case 5:
					//heartrate field
					if (bad) { arrProblemChildren[j].heartRate = atoi(tok); }

					if (strlen(tok) == 0) {
						arr[i].heartRate = -1;
						c++;
						break;
					}
					arr[i].heartRate = atoi(tok);
					//printf("[%d]", strlen(tok));
					c++;
					break;
				case 6:
					//steps field
					if (bad) { arrProblemChildren[j].steps = atoi(tok); j++; }
					arr[i].steps = atoi(tok);
					if (strlen(tok) == 0) {
						arr[i].steps = -1;
						c++;
						break;
					}
					//printf("[%d]", strlen(tok));
					c++;
					break;
				case 7:
					if (bad) {
						//only occurs once??? no shot
						arrProblemChildren[j].sleepLevel == NONE;
						
					}
					if (strlen(tok) == 0 || tok == NULL) {
						//this one just does even get called once??? alright buster brown
						arr[i].sleepLevel = NONE;
					}
				    if (atoi(tok) == 1) arr[i].sleepLevel = ASLEEP;
					else if (atoi(tok) == 2) arr[i].sleepLevel = AWAKE;
					else if (atoi(tok) == 3) arr[i].sleepLevel = REALLYAWAKE;
					else {
						arr[i].sleepLevel = NONE;
					}
					//sleep field
					c++;

					break;
				}
				
			}
			if (bad) j++;
			//if (i > 1439) {
				//printf("Problem children: line:%d - index:%d - patient:%s - time:%s\n", line, i, arr[i].patient, arr[i].minute);
				//system("pause");
			//}
			//printf("[%d]", c);
			//printf("line[%d]\t|%s\t\t|%s\t|%lf\t|%lf\t|%d\t|%d\t|%d\t|%d\t|\n", line + 1, arr[i].patient, arr[i].minute, arr[i].calories, arr[i].distance, arr[i].floors, arr[i].heartRate, arr[i].steps, arr[i].sleepLevel);
			if (i > 0) {
				if (strcmp(arr[i].minute, arr[i - 1].minute) == 0) {
					//printf("\nFOUND THE FuCKER %s\n", arr[i].minute);
					//system("pause");
					strcpy(arrProblemChildren[j].patient, arr[i].patient);
					strcpy(arrProblemChildren[j].minute, arr[i].minute);
					arrProblemChildren[j].steps = arr[i].steps;
					arrProblemChildren[j].distance = arr[i].distance;
					arrProblemChildren[j].floors = arr[i].floors;
					arrProblemChildren[j].heartRate = arr[i].heartRate;
					arrProblemChildren[j].sleepLevel = arr[i].sleepLevel;
					j++;
					a = 0;
				}
			}

			if (a) {
				//printf("No line skip, index: %d\n", i);
				i++; 
			}
			else {
				//printf("index after line skip: %d\n", i);
				//system("pause");
			}
		line++;

	}
	for (int i = 0; i < 1440; i++) {
		if (i < 100) {
			printf("arr[%d]\t\t|%s\t|%s\t|%lf\t|%lf\t|%d\t|%d\t|%d\t|%d\t|\n", i, arr[i].patient, arr[i].minute, arr[i].calories, arr[i].distance, arr[i].floors, arr[i].heartRate, arr[i].steps, arr[i].sleepLevel);

		}
		else {
			printf("arr[%d]\t|%s\t|%s\t|%lf\t|%lf\t|%d\t|%d\t|%d\t|%d\t|\n", i, arr[i].patient, arr[i].minute, arr[i].calories, arr[i].distance, arr[i].floors, arr[i].heartRate, arr[i].steps, arr[i].sleepLevel);
		}
	}
}

//now that I have the csv, calculating totals / averages / ranges
double totalCal(FitbitData *arr) {
	double total = 0.0;
	for (int i = 0; i < 1440; i++) {
		if (arr[i].calories != -1) {
			total += arr[i].calories;
		}
	}
	printf("\nTotal Calories: %0.2f", total);
	return total;
}
double totalDis(FitbitData* arr) {
	double total = 0.0;
	for (int i = 0; i < 1440; i++) {
		if (arr[i].distance != -1) {
			total += arr[i].distance;
		}
	}
	printf("\nTotal Distance: %0.2f", total);
	return total;
}
double totalFloors(FitbitData* arr) {
	double total = 0.0;
	for (int i = 0; i < 1440; i++) {
		if (arr[i].floors != -1) {
			total += arr[i].floors;
		}
	}
	printf("\nTotal Floors: %0.2f", total);
	return total;
}
double totalSteps(FitbitData* arr) {
	double total = 0.0;
	for (int i = 0; i < 1440; i++) {
		if (arr[i].steps != -1) {
			total += arr[i].steps;
		}
	}
	printf("\nTotal Steps: %0.2f", total);
	return total;
}
double avgHeart(FitbitData* arr) {
	double avg = 0;
	double total = 0;
	double a = 0;
	for (int i = 0; i < 1440; i++) {
		if (arr[i].heartRate != -1) {
			total += arr[i].heartRate;
			a++;
		}
	}
	avg = total / a;
	printf("\nAverage Heart Rate: %0.2f", avg);
	return avg;
}
char* maxSteps(FitbitData* arr, maxStep* activity) {
	double max = 0;
	for (int i = 0; i < 1440; i++) {
		if (arr[i].steps > max) {
			max = arr[i].steps;
		}
	}
	int j = 0;
	printf("\nMost active at:\n");
	for (int i = 0; i < 1440; i++) {
		if (arr[i].steps == max) {
			strcpy(activity[j].minute,arr[i].minute);
			activity[j].steps = arr[i].steps;
			printf(" %s - %d steps taken\n", arr[i].minute, arr[i].steps);
			j++;
		}
	}
}


char worstSleep(FitbitData* arr, char* worstSleepS) {
	//IMPORTANT NOTE FOR FUTURE ME:
	//    ASK MR. FALLON OR TA IF HE WANTS EMPTY SPACES FOR SLEEPING TO BE NONE OR AWAKE

	int awake = 0;
	int asleep = 0;
	int napS = 0;
	int napE = 0;
	int worst = 0;
	int worstI[2] = { 0,0 };
	int timeAwake = 0;

	for (int i = 0; i < 1440; i++) {
		if (arr[i].sleepLevel != ASLEEP && asleep == 0) {
			//alright! they are asleep! now we increment naps by 1, and set asleep to 1 as well.
			timeAwake = 0;
			awake++;
			asleep = 1;
			napS = i;
			printf("\n\nAWAKE FROM: %s, TO ", arr[i].minute);
		}
		if (asleep) {
			if (arr[i].sleepLevel == ASLEEP) {
				asleep = 0;
				printf("%s\n", arr[i].minute);
				napE = i;
				for (int i = napS; i < napE + 1; i++) {
					switch (arr[i].sleepLevel) {
					case NONE:
						timeAwake += 0;
						break;
					case AWAKE:
						timeAwake += 2;
						break;
					case REALLYAWAKE:
						timeAwake += 3;
					}
				}
				if (timeAwake > worst) {
					printf("prev worst time: %d, curr worst time: %d\n", worst, timeAwake);
					worst = timeAwake;
					worstI[0] = napS;
					worstI[1] = napE;
					printf("New longest time awake found : %s to %s\n", arr[worstI[0]].minute, arr[worstI[1]].minute);
				}
			}
		}
	}
	
	worstSleepS[100] = "";
	strcat(worstSleepS, arr[napS].minute);
	strcat(worstSleepS, " - ");
	strcat(worstSleepS, arr[napE].minute);
	//printf("\nJust testing strcat: %s", worstSleepS);
	worstSleepS;
}


//writing to new file
int writeOutput(FitbitData* arr, FILE* output, maxStep* activity, double Cal, double Dist, double Floors, double Steps, double Heart, char* worstSleepS, FitbitData* arrProblemChildren) {
	fprintf(output, "Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps(minutes), SLeep\n");
	fprintf(output, "%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,", Cal, Dist, Floors, Steps, Heart);
	int j = 0;
	while (activity[j].steps != 0) {
		fprintf(output, "(%s),", activity[j].minute);
		j++;
	}
	printf("\nTesting worstSleepS: %s", worstSleepS);

	//FOR SOME reason, the code just slaps in some weird hexadecima escape codes, whitch im not sure how to get rid of. 
	//it appears my worstSleepS just aqquires a "\x4\x" somewhere, no idea why how or where. bit of a bruh moment if you ask me.
	fprintf(output, "(%s)", worstSleepS);
	fprintf(output, "\n");
	
	for (int i = 0; i < 1440; i++) {
		if (strcmp(arrProblemChildren[i].patient, "") != 0) {
			fprintf(output, "%s,%s,%lf,%lf,%d,%d,%d,%d,\n",arrProblemChildren[i].patient, arrProblemChildren[i].minute, arrProblemChildren[i].calories, arrProblemChildren[i].distance, arrProblemChildren[i].floors, arrProblemChildren[i].heartRate, arrProblemChildren[i].steps, arrProblemChildren[i].sleepLevel);
		}
	}
	
	
}


