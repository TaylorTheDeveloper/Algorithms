/* "It's a free world, all you have to do is fall in Love" - Queen

Taylor Brockhoeft

COP4531 Algorithms

Maya Ackerman



Assignment 2 - Sorting Implementation and analysis.



Dev Notes:

9-20-15 Issue with generatedData, generates n+1 instead of n. Minor error.

9-20-15 Segmentation Fault with Mergesort

9-20-15 Counting Sort Issue, names are not linked. Maybe make a seperate array for them or combine them in struct array idk



FIXED

9-20-15 Issue with insertion sort, only partially sorting - FIXED 9-20-15





*/

#include <iostream>

#include <ctime>

#include <cstdlib>

#include <fstream>

#include <string>

#include <vector>



using namespace std;



const string names[] = {"Yoda", "Doku", "Palpatine","Obiwan","C3PO","R2D2","Chewbacca","Han","Lando","Jabba","Windu","Luke","Leia"};

const char filename[] = "data.txt";//Output filename

const int randUpperLimit = 100;



struct Item{

	int num;

	string name;

};





void generateDataFile(int num){

	//This function generates up to 'num' lines of data for my sorting programs

	int nameUpperLimit = sizeof(names)/sizeof(*names);//Get length of array (total bytes/ byte size of each element)



	srand(time(0));

	ofstream myfile;

  	myfile.open(filename);



  	for(int i =0; i< num; i++){

  		myfile << rand()%randUpperLimit << " " << names[rand()%nameUpperLimit] << endl;

  	}

  	myfile.close();

}



void loadData(vector<Item> &stuff){

	//Loads Generated Data into program

	Item indexItem;

	ifstream myfile;

  	myfile.open (filename);

  	while(!myfile.eof()){

  		myfile >> indexItem.num >> indexItem.name;

  		stuff.push_back(indexItem);

  	}

  	myfile.close();



}



void printData(vector<Item> &stuff){

	//Making sure data is inside the list is correct

	for(int i = 0; i < stuff.size()-1; i++){

		cout << stuff[i].num << " " << stuff[i].name << endl;

	}



}



int smallestItemIndex(vector<Item> &stuff){

	//Helper function that finds the smallest value and returns it's index. 

	//(DOES NOT RETURN ITS VALUE)

	int index = 0;



	for(int i = 0; i < stuff.size(); i++){

		if(stuff[i].num < stuff[index].num){

			index = i;

		}

	}



	return index;

}



void insertionSort(vector<Item> &stuff){

	//Insertion sort

	

	Item tmp;



	for(int i = 1; i < stuff.size();i++){

		int j = i;

		while( j > 0 && stuff[j-1].num > stuff[j].num){

			tmp = stuff[j];

			stuff[j] = stuff[j-1];

			stuff[j-1] = tmp;

			j--;

		}

	}



	printData(stuff);

}



void merge(vector<Item> &stuff, int l, int m, int r){



	int i = 0, j = 0, k = 0; //Counting variables

	int n1 = m - l + 1;//of left

	int n2 = r - m;//of right



	cout << endl << "Inside Merge " << l << " " << r << endl;





	//Create Temp Arrays

	Item left[n1], right[n2];



	//Copy Data to Temp Arrays left and right

	for(i = 0; i <n1; i++){

		left[i] = stuff[l+i];

	}

	for(j = 0; j <n2; j++){

		right[i] = stuff[m + j + 1];

	}



	//Merge arrays back into into stuff

	i =0, j =0, k =l;



	while(i < n1 && j < n2){

		if(left[i].num <= right[j].num){

			stuff[k] = left[i];

			i++;

		}

		else{

			stuff[k] = right[j];

			j++;

		}

		k++;

	}



	//if there are remaining left items, copy them

	while( i < n1){

		stuff[k] = left[i];

        i++;

        k++;

	}



	//if there are remaining right items, copy them

	while( j < n2){

		stuff[k] = right[j];

        j++;

        k++;

	}



}



void mergeSort(vector<Item> &stuff, int l, int r){

	//Merge sort

	//Call like: mergeSort(list,0,list.size()-1)



	if( l < r){

		int m =  (l+r)/2;

		mergeSort(stuff,l,m);

		mergeSort(stuff,m+1,r);



		cout << endl << "Before Merge " << l << " " << r << endl;



		merge(stuff,l,m,r);

	}





	printData(stuff);

}



void countingSort(vector<Item> &stuff){

	//Counting Sort

	

	int countingArray[randUpperLimit];



	//Buckets for each of the numbers up to our upper limit

	for(int i = 0; i < randUpperLimit; i++){



		countingArray[i]=0;

	}





	//Count instances of items in each buckets

	for (int i=0;i< stuff.size()-1;i++){ 

        countingArray[stuff[i].num]++;

    }



    int outputindex = 0;



    for(int j =0; j < randUpperLimit;j++){

    	while(countingArray[j]--){

    		stuff[outputindex++].num = j;

    	}

    }



    printData(stuff);



}



int main(){

	vector<Item> list;



	//generateDataFile(10);

	loadData(list);

	//printData(list);

	//smallestItem(list);

	//insertionSort(list);

	//cout << endl << "First Call " << 0 << " " << list.size()-1 << endl;

	//mergeSort(list,0, list.size()-1);

//cout << "Seggy " << i << endl;

	countingSort(list);







    

}
