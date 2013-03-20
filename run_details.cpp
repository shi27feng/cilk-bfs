#include <iostream>
#include "math.h"
#include <string>
#include <fstream>

using namespace std;


/** NOT DONE YET */

class RunDetails {
	int NBFS;
	int SCALE;
	int edgefactor;
	double constructionTime;

	double *startvtx;
	double *runtime;
	double *nedges;
	double *depth;

	double *TEPS;

	int counter;


public:
	RunDetails(int NBFS, int SCALE, int edgefactor);

	void addConstructionTime(double constructionTime);
	void addRun(double startvtx, double runtime, double nedges, double depth);

	int findMinIndex(double *array, int starts);
	double getMin(double *array);
	double getFirstQuartile(double *array);
	double getMedian(double *array);
	double getLastQuartile(double *array);
	double getMax(double *array);
	double getMean(double *array);

	double *sortArray(double *array);
	void sortArrays();
	


	void printStatistics();
};

RunDetails::RunDetails(int NBFS, int SCALE, int edgefactor) {
	this->NBFS = NBFS;
	this->SCALE = SCALE;
	this->edgefactor = edgefactor;

	startvtx = new double [NBFS];
	runtime = new double[NBFS];
	nedges = new double[NBFS];
	depth = new double[NBFS];

	TEPS = new double[NBFS];
	counter = 0;
}

void RunDetails::addRun(double startvtx, double runtime, double nedges, double depth) {
	this->startvtx[counter] = startvtx;
	this->runtime[counter] = runtime;
	this->nedges[counter] = nedges;
	this->depth[counter] = depth;
	this->TEPS[counter++] = nedges/runtime;
}


void RunDetails::addConstructionTime(double constructionTime) {
	this->constructionTime = constructionTime;
}

int RunDetails::findMinIndex(double *array, int startAt) {
	
	int minIndex = startAt;
	for (int i = startAt; i < counter; i++){
		if (array[i] < array[minIndex] ) {
			minIndex = i;
		}
	}
	return minIndex;
}
double RunDetails::getMin(double *array) {
	return array[0];
}

double RunDetails::getFirstQuartile(double *array){
	int quart = counter/4;
	if (counter%4 <= 1 ) {
		return (array[quart] + array[quart - 1])/2.0;
	}
	else { 
		return array[quart];
	}
}

double RunDetails::getLastQuartile(double *array){
	int quart = counter/4;
	if (counter%4 <= 1 ) {
		return (array[counter-quart] + array[counter-quart - 1])/2.0;
	}
	else { 
		return array[counter-quart];
	}
}

double RunDetails::getMedian(double *array){
	int mid = counter/2;
	return (counter%2 != 0) ? array[mid] : (array[mid] + array[mid-1])/2.0;
}



double RunDetails::getMax(double *array) {
	return array[counter-1];
}

double RunDetails::getMean(double *array) {
	double sum = 0;
	for (int i = 0; i < counter; i++) {
		sum += array[i];
	}
	return sum/counter;
}


double* RunDetails::sortArray(double *array) {

	for (int i = 0; i < counter; i++) {
		int index =	findMinIndex(array, i);
		int tmp = array[i];
		array[i] = array[index];
		array[index] = tmp;
	}
	return array;
}

void RunDetails::sortArrays() {
	runtime = sortArray(runtime);
	nedges = sortArray(nedges);
	TEPS = sortArray(TEPS);
}


void RunDetails::printStatistics(){

	sortArrays();

	printf("SCALE: %d\n", SCALE);
	printf("edgefactor: %d\n", edgefactor);
  	printf("NBFS: %d\n", counter);

  	printf("construction_time: %20.17e\n", constructionTime); 

  	printf("min_time: %20.17e\n", getMin(runtime));
  	printf("firstquartile_time: %20.17e\n", getFirstQuartile(runtime));
  	printf("median_time: %20.17e\n", getMedian(runtime));
  	printf("lastquartile_time: %20.17e\n", getLastQuartile(runtime));
  	printf("max_time: %20.17e\n", getMax(runtime));
  	printf("mean_time: %20.17e\n", getMean(runtime));

  	printf("min_nedges: %20.17e\n", getMin(nedges));
  	printf("firstquartile_nedges: %20.17e\n", getFirstQuartile(nedges));
  	printf("median_nedges: %20.17e\n", getMedian(nedges));
  	printf("lastquartile_nedges: %20.17e\n", getLastQuartile(nedges));
  	printf("max_nedges: %20.17e\n", getMax(nedges));
  	printf("mean_nedges: %20.17e\n", getMean(nedges));


  	printf("min_TEPS: %20.17e\n", getMin(TEPS));
  	printf("firstquartile_TEPS: %20.17e\n", getFirstQuartile(TEPS));
  	printf("median_TEPS: %20.17e\n", getMedian(TEPS));
  	printf("lastquartile_TEPS: %20.17e\n", getLastQuartile(TEPS));
  	printf("max_TEPS: %20.17e\n", getMax(TEPS));
  	printf("mean_TEPS: %20.17e\n", getMean(TEPS));

}
