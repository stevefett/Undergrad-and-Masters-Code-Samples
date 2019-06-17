//Steven Salmons
//HW#3
//CSC 130

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

int findNth(int[], int[], int aStart, int bStart, int size);

//*********************************************************
//A selection sort algorithm for sorting the two randomly
//generated arrays.
//*********************************************************

void selectionSort(int numbers[], int array_size)
{
  int i, j;
  int min, temp;

  for (i = 0; i < array_size-1; i++)
  {
    min = i;
    for (j = i+1; j < array_size; j++)
    {
      if (numbers[j] < numbers[min])
        min = j;
    }
    temp = numbers[i];
    numbers[i] = numbers[min];
    numbers[min] = temp;
  }
}

int main () 
{
//*************************************
//Generate two random arrays, using
//the size specified by the user for
//each array.
//Seeder controls the maximum value of 
//the random number generator.
//*************************************
	srand((unsigned)time(0));
	int seeder = 50;
	int random_integer = rand() % seeder;
	int count = 0;
	cout <<"Enter the size that you want the arrays: ";
	int size;
	cin >>size;
	int A[size], B[size];
	A[0] = random_integer;
	random_integer = rand() % seeder;
	B[0] = random_integer;
	count++;
	while (count < size)
	{
   		random_integer = rand() % seeder;
		A[count] = random_integer;
		random_integer = rand() % seeder;
		B[count] = random_integer;
		count++;
	}
	selectionSort(A, size);
	selectionSort(B, size); 

//**** Tell the user what each array contains. ******
//**** Then tell them what the nth largest is. ******

	cout <<"Array A = ";
	for (int i=0;i<size;i++)
	{
		cout <<A[i] <<", ";
	}
	cout <<endl <<"Array B = ";
	for (int i=0;i<size; i++)
	{
		cout <<B[i] <<", ";
	}
	cout <<endl <<endl;
	cout <<"The " <<size <<" largest item is: " <<findNth(A,B,0,0,size);
	return 0;
}

//***********************************************************
//Function findNth takes two arrays of size n="size" 
//and returns the nth item.
//We use aStart and bStart as indexes to the start of 
//subArray A and subArray B so we can do all of the 
//work in the original array, saving memory.
//***********************************************************

int findNth(int A[], int B[], int aStart, int bStart, int size)
{
	int center = size/2, bMid = 0, aMid = 0;

//**** This case looks for two one-item arrays and returns the larger.
	if (size == 1)
	{
		if (A[aStart] > B[bStart])
			return A[aStart];
		else
			return B[bStart];
	}

//**** This case evaluates "even-sized" cases. *******************
//**** An even sized case is where each array is an even size.****
	else if (size%2 == 0)
	{
		if (A[aStart+center] == B[bStart+center])
			return A[aStart+center];
		else if (A[aStart+center] < B[bStart+center])
			return findNth(A, B, aStart+center, bStart, center);
		else
			return findNth(A, B, aStart, bStart+center, center);
		
	}	
//**** This case handles odd sized cases. ************************
	else
	{
		if (A[aStart+center] == B[bStart+center])
			return A[aStart+center];
		else if (A[aStart+center] < B[bStart+center])
			return findNth(A, B, aStart+center, bStart, center+1);
		else
			return findNth(A, B, aStart, bStart+center, center+1);
	}
			
}

