/* "It's a free world, all you have to do is fall in Love" - Queen

Taylor Brockhoeft
COP4531 Algorithms
Maya Ackerman

Assignment 2 - Sorting Implementation and analysis.

Dev Notes:
9-20-15 Counting Sort Issue, names are not linked. Maybe make a seperate array for them or combine them in struct array idk

FIXED
9-20-15 Issue with insertion sort, only partially sorting - FIXED 9-20-15
9-20-15 Issue with generatedData, generates n+1 instead of n. Minor error. - FIXED 9-20-15
9-20-15 Segmentation Fault with Mergesort - FIXED 9-20-15 (missued variable)
9-29-15 Input handler complete
9-29-15 Time Mechanism complete

*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <time.h>


using namespace std;
const string names[] = {"Yoda", "Doku", "Vader", "Palpatine","Obiwan","C3PO","R2D2","Chewbacca","Han","Lando","Jabba","Windu","Luke","Leia", "Boba", "Padme", "JarJarBinks","Kylo","Kyhigh"};
string filename = "data.txt";//Output filename
const int randUpperLimit = 100;
clock_t begin_time, end_time;

struct Item{
	int num;
	string name;
};

void generateDataFile(int num, int k,string fn){
	//This function generates up to 'num' lines of test data for my sorting programs
	int nameUpperLimit = sizeof(names)/sizeof(*names);//Get length of array (total bytes/ byte size of each element)
	srand(time(0));
	ofstream myfile;
  	myfile.open(fn.c_str());

  	randUpperLimit = k;

  	for(int i =0; i< num; i++){
  		myfile << rand()%randUpperLimit << " " << names[rand()%nameUpperLimit] << endl; //Generate random #'s (between 0 and the randUpperLimit) and names from the list'
  	}

  	myfile.close();
  	cout << "File written " << fn << endl;
}

void loadData(vector<Item> &stuff){
	//Loads Generated Data into vector construct
	Item indexItem;
	ifstream myfile;
  	myfile.open (filename.c_str());

  	while(!myfile.eof()){
  		myfile >> indexItem.num >> indexItem.name;
  		stuff.push_back(indexItem);
  	}

  	myfile.close();
}

void printData(vector<Item> &stuff){
	//Prints the data in the list one line at a time
	for(int i = 0; i < stuff.size()-1; i++){
		cout << stuff[i].num << " " << stuff[i].name << endl;
	}
}

int smallestItemIndex(vector<Item> &stuff){
	//Helper function that finds the smallest value and returns it's index. 
	//(DOES NOT RETURN ITS VALUE)
	//unused in this project

	int index = 0;

	for(int i = 0; i < stuff.size(); i++){
		if(stuff[i].num < stuff[index].num){
			index = i;
		}
	}

	return index;
}

int largestItemInList(vector<Item> &stuff){

	int largest = 0;

	if(stuff.size()>0){
		largest = stuff[0].num;
	}

	for(int i = 0; i < stuff.size(); i++){
		if(stuff[i].num > largest){
			largest = stuff[i].num;
		}
	}

	return largest;
}

void insertionSort(vector<Item> &stuff){
	//Insertion sort	
	Item tmp;
	begin_time = clock();
	for(int i = 1; i < stuff.size();i++){
		int j = i;
		while( j > 0 && stuff[j-1].num > stuff[j].num){
			tmp = stuff[j];
			stuff[j] = stuff[j-1];
			stuff[j-1] = tmp;
			j--;
		}
	}
	end_time = clock () - begin_time;

	printData(stuff);

	cout << "\nTime Elapsed: " << float( end_time - begin_time ) /  CLOCKS_PER_SEC;
}

void merge(vector<Item> &stuff, int l, int m, int r){
	int i = 0, j = 0, k = 0; //Counting variables
	int n1 = m - l + 1;//of left
	int n2 = r - m;//of right

	//cout << endl << "Inside Merge " << l << " " << r << endl;
	//Create Temp Arrays
	Item left[n1], right[n2];

	//Copy Data to Temp Arrays left and right
	for(i = 0; i <n1; i++){
		left[i] = stuff[l+i];
	}

	for(j = 0; j <n2; j++){
		right[j] = stuff[m + j + 1];
	}

	//Merge arrays back into into stuff(item vector)
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

		//cout << endl << "Before Merge " << l << " " << r << endl;

		merge(stuff,l,m,r);
	}
}

void callMergeSort(vector<Item> &stuff, int l, int r){
	//Due to the recursive nature or mergesort, this function wrapps the mergesort function so we dont print out of context
	begin_time = clock();
	mergeSort(stuff,0,stuff.size()-1);
	end_time = clock();
    printData(stuff);

    cout << "\nTime Elapsed: " << float( end_time - begin_time ) /  CLOCKS_PER_SEC;
}

void countingSort(vector<Item> &stuff){
	//Counting Sort	
	int countingArray[randUpperLimit];

	begin_time = clock();

	//Buckets for each of the numbers up to our upper limit
	for(int i = 0; i < randUpperLimit; i++){
		countingArray[i]=0;
	}

	//Count instances of items in each buckets
	for (int i=0;i< stuff.size()-1;i++){ 
        countingArray[stuff[i].num]++;
    }



    int outputindex = 0;

    //re-order items in array
    for(int j =0; j < randUpperLimit;j++){
    	while(countingArray[j]--){
    		stuff[outputindex++].num = j;
    	}
    }
    end_time = clock();

    printData(stuff);

    cout << "\nTime Elapsed: " << float( end_time - begin_time ) /  CLOCKS_PER_SEC;
}

string lowerCase(string cmd){
	//Convert String to lowercase
	for(unsigned int i = 0; i < cmd.length();i++){
		if(isupper(cmd[i])){
			cmd[i] = tolower(cmd[i]);
		}
	}
	return cmd;
}

void printHelp(){
	cout << "Help Menu" << endl;
	cout << "=====================" << endl;
	cout << "command" << "   ---   " << "Action" << endl;
	cout << "=====================" << endl;
	cout << "help/h" << "   ---   " << "prints this help menu" << endl;
	cout << "exit/quit" << "  ---   " << "exits the program" << endl;
	cout << "countingsort" << "  <filename>" << "  ---   " << "Runs countingSort on <filename>" << endl;
	cout << "mergesort" << "  <filename>" << "  ---   " << "Runs mergeSort on <filename>" << endl;
	cout << "insertionsort" << "  <filename>" << "  ---   " << "Runs insertionSort on <filename>" << endl;
}

int main(int argc, char *argv[]){
	vector<Item> list;//Storage of list items
	bool run = true;
	string command;

	int toGenerate = 10;//Default to generate
	int largestK = 100;//largest k to generate

	printHelp();

	while(run==true){
		list.clear();
		cout << "\n\nPlease enter a valid command: ";
		cin >> command;
		command = lowerCase(command);

		if(command=="gen"){
			cout << "\nHow many records to generate? Default is 10: ";
			cin >> toGenerate;

			cout << "\nLargest K? Default is 100: ";
			cin >> largestK;

			cout << "\nFilename to output: ";
			cin >> filename;

			generateDataFile(toGenerate, largestK, filename);
		}
		else if(command=="insertionsort"){
			cin >> filename;
			loadData(list);
			insertionSort(list);
		}
		else if(command=="mergesort"){
			cin >> filename;
			loadData(list);
			callMergeSort(list,0, list.size()-1);
		}
		else if(command=="countingsort"){
			cin >> filename;
			loadData(list);
			countingSort(list);
		}
		else if(command=="help" || command=="h"){
			printHelp();
		}
		else if(command=="exit" || command=="quit"){
			break;
		}
		else{
			cout << "\n Invalid Input \n";
		}
	}

	return 0;

}
