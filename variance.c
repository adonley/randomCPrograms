#include<stdio.h>

int main() {

	int num, i = 0;
	float avg = 0, var = 0;
	printf("%s\n","How many numbers?");
	scanf("%i",&num);
	float rest[num];
	
	for(i=0; i<num; i++) {
		printf("%i: \n", i+1);
		scanf("%f",&rest[i]);
	}

	for(i=0; i<num; i++)
		avg += rest[i];

	avg = avg / num;
	printf("\nAverage: %f",avg);
	for(i=0; i<num; i++) {
		rest[i] = (rest[i]-avg)*(rest[i]-avg);
		var += rest[i];
	}
	var = var / num;
	printf("\nVariance: %f\n",var);
	return 0;
}