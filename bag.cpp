#include <iostream>
#include "math.h"
#include <string>
#include <fstream>

using namespace std;

class VertexBag {

	int bagSize;

	int lengthOfArray;
	int* bagArray;

	/* Where the min vertex is located */
	int counter;

	bool heap;

public:
	/**
	*	Initalizes the Bag
	*/
	VertexBag(); //Constructor


	/**
	*	Returns the number of vertices in the bag
	*/
	int size() {
		return bagSize;
	}

	bool exists(int vertex) {
		for (int i = 0; i < size(); i++) {
			if (vertex == bagArray[i]) {
				return true;
			}
		}
		return false;
	}

	int peekMin();
	int popMin();

	void mergeBags(VertexBag *bag);
	int* mergeLists(int *a, int *b, int sizeA, int sizeB){
		printf("Starting mergeLists\n");
		int* result = new int[sizeA+sizeB];
		int l =0 ,r =0, size;
		
		size = sizeA + sizeB;
		for (int i = 0; i < size; ++i){
		//	printf("Appending %i or %i \n", a[l],b[r]);
			if(a[l] == b[r] && l < sizeA && r < sizeB){
				result[i] = a[l++];
				r++;
				size--;
			}else if(a[l] < b[r] && l < sizeA && r < sizeB){
				result[i] = a[l++];
			}else if(a[l] > b[r]  && l < sizeA && r < sizeB){
				result[i] = b[r++];
			}else if(l >= sizeA){
				result[i] = b[r++];
			}else if(r >= sizeB){
				result[i] = a[l++];
			}
		}
		bagSize = size;
		return result;
	}

	//Sannsynligvis bug med size hvis det er duplicates
	int* merge_sort(int *list, int size){
		int middle = ceil(size/2);
		int* left = new int[(int)ceil(size/2)];
		int* right = new int[(int)floor(size/2)];

		if(size <=1){
			return list;
		}

		for (int i = 0; i < size; ++i){
			if(i> ceil(size/2)){
				left[i] = list[i];
			}else{
				right[i-(int)ceil(size/2)] = list[i];
			}
		}
		left = merge_sort(left,ceil(size/2));
		right = merge_sort(right,floor(size/2));
		return mergeLists(left,right,ceil(size/2),floor(size/2));

	}


	bool isEmpty(){
		return size() == 0;
	}

	void put(int vertex) {
		push(vertex, false);
	}

	void push(int vertex, bool asHeap);

	int get(); 

	int getElement(int i);

	void setElement(int i, int value);

	void join(VertexBag otherBag) {
		while (otherBag.size() != 0) {
			put(otherBag.get());
		}
	}

	VertexBag* split(int numberOfBags);

	void printBag();
};

VertexBag::VertexBag() {
	lengthOfArray = 1;
	bagArray = new int[lengthOfArray];
	counter = -1;
	bagSize = 0;
	heap = false;
}

void VertexBag::printBag(){
	string str("Bag: ");
	cout << "Bag: ";
	for (int i = 0; i <size() && i < 10; i++) {
		cout << getElement(i) << ", ";
	}
	cout << "\n";
}

void VertexBag::push(int vertex, bool asHeap) {
	int tmp;
	int i = bagSize;

	if (bagSize == lengthOfArray){
		int *newArray = new int[lengthOfArray*2];
		for (int j = 0; j < lengthOfArray; j++) {
			newArray[j] = bagArray[j];
		}
		free(bagArray);
		bagArray = newArray;
		lengthOfArray = lengthOfArray*2;
	}

	bagArray[bagSize++] = vertex;

	if (!asHeap) return;

	heap = true;

	while(i > 0 && bagArray[(i-1)/2] > vertex ) {
		tmp = bagArray[(i-1)/2];
		bagArray[(i-1)/2] = bagArray[i];
		bagArray[i] = tmp;
		i = (i-1)/2;
	}

}

int VertexBag::peekMin() {
	if (bagSize == 0) return -1;

	if (heap) return bagArray[0];
	else 	return bagArray[counter];
}

int VertexBag::popMin() {
	bagSize--;
	if (heap) {
		int l, r, i;
		int minValue = bagArray[0];
		
		i = 0; 

		bagArray[0] = bagArray[bagSize];

	}
	else {
		return bagArray[counter++];
	}

}

int VertexBag::get() {
	if(bagSize != 0){
		return bagArray[--bagSize];
	}else{
		return -1;
	}
}

int VertexBag::getElement(int i) {
	return bagArray[i];
}

void VertexBag::setElement(int i, int value) {
	bagArray[i] = value;
}

void VertexBag::mergeBags(VertexBag *bag){
	printf("Starting mergeBags with %i and %i \n",bagSize,bag->size());
	
	int *temp;
	int duplicates = 0;
	temp = new int[size() + bag->size()];
	//int* left;
	//left = (int *)calloc(bagSize-1,sizeof(int));
	//sleep(1);
	//for sorterte lister
/*
	printf("Getting left half\n");
	for (int i = 0; i < bagSize; ++i){
		left[i] = getElement(i);
	}

	printf("Getting right half\n");
	for (int i = 0; i < bag->size(); ++i){
		right[i] = bag->getElement(i);
	}
*/
	for (int i = 0; i < size() + bag->size()-duplicates; ++i){
		if(bag->peekMin() == peekMin() && peekMin() != -1){
			temp[i] = popMin();
			bag->popMin();
			duplicates++;
		}else if(bag->peekMin() < peekMin() && bag->peekMin() > 0){
			temp[i] =  bag->popMin();
		}else if(peekMin() > 0){
			temp[i] = popMin();
		}
		//kopiere over verdier til den nye bagen !!!!!!!
		free(bagArray);
		bagArray = temp;	
	}
	
	//bagArray = mergeLists(left,right,bagSize,bag->size());

}

VertexBag* VertexBag::split(int numberOfBags){

	VertexBag *bags;
	bags = new VertexBag[numberOfBags];
	int numberInEachBag = (int)ceil((double)size()/numberOfBags);
/*
	for (int i = 0; i < numberOfBags; i++) {

		// lag settere for bagArray og bagSize
		bags[i].bagArray = &bagArray[i*numberInEachBag];
		bags[i].bagSize = numberInEachBag -1;
		if(i < size() % numberInEachBag){
			bags[i].bagSize++;
		}
	}
*/

	for (int i = 0; i < numberOfBags; i++) {
		for (int j = 0; j < numberInEachBag && i*numberInEachBag+j < size(); j++){
			bags[i].put(getElement(i*numberInEachBag + j));
		}
	}
	return bags;


	printf("split done\n");
	return bags;

}
