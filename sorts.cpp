/* "It's a free world, all you have to do is fall in Love" - Queen

Taylor Brockhoeft

COP4531 Algorithms

Maya Ackerman



Assignment 2 - Sorting Implementation and analysis.



Dev Notes:

9-20-14 Issue with generatedData, generates n+1 instead of n. Minor error.



FIXED

9-20-14 Issue with insertion sort, only partially sorting - FIXED 9-20-14





*/

#include <iostream>

#include <ctime>

#include <cstdlib>

#include <fstream>

#include <string>

#include <vector>



using namespace std;



const string names[] = {"Yoda", "Doku", "Palpatine","Obiwan","C3PO","R2D2","Chewbacca","Han","Lando","Jabba","Windu","Luke","Liea"};

const char filename[] = "data.txt";//Output filename



struct Item{

	int num;

	string name;

};





void generateDataFile(int num){

	//This function generates up to 'num' lines of data for my sorting programs

	int randUpperLimit = 100;

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

	for(int i = 0; i < stuff.size(); i++){

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

	//Interpreted from lecture slides



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



void mergeSort(vector<ITem> &stuff){

	

}



int main(){

	vector<Item> list;



	//generateDataFile(100);

	loadData(list);

	//printData(list);

	//smallestItem(list);

	//insertionSort(list);





    

}
