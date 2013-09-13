#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {

	if(argc == 1) {
		printf("Example Usage: statsCalc 34 43 43\n");
		return 0;
	}

	int num, i = 0;
	float avg = 0, varPop = 0, stdPop = 0;
	float varSamp = 0, stdSamp = 0, rest[100];

	// This is if there are spaces between the numbers
	for(i = 1; i < argc; i++) {
		rest[i-1] = atof(argv[i]);
		avg += rest[i-1];
	}
		
	avg = avg / (argc - 1);

	for(i=0; i < argc - 1; i++) {
		rest[i] = (rest[i]-avg)*(rest[i]-avg);
		varPop += rest[i];
		varSamp += rest[i];
	}

	varPop = varPop / (argc - 1);
	varSamp = varSamp / (argc - 2);
	stdPop = sqrt(varPop);
	stdSamp = sqrt(varSamp);

	printf("Average:                 : %.3f\n",avg);
	printf("Population Variance      : %.3f\n",varPop);
	printf("Population Std Deviation : %.3f\n",stdPop);
	printf("Sample Variance:         : %.3f\n",varSamp);
	printf("Sample Std Deviation     : %.3f\n",stdSamp);
	return 0;
}