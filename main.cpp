#include<iostream>
#include<cmath>
#include<fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;


const char fill = '#';
const char blank = ' ';


//print array to the console window
//take in parameters for dynamically allocated array and square rows/colums
//square is important here because it means rows = columns
void printArray(char** array, int size)
{
	
	for (int i = 0; i < size; i++)
	{
		
		for (int j = 0; j < size; j++)
		{
			
			cout << array[i][j] << ' ';
			
		}
		cout << "\n";
	}
	
}


bool inside(int xPos, int yPos)
{
	
	while(xPos != 0 && yPos != 0) //move through array in steps until we reach a corner
	{
		
		//fill the main void between the carpet squares which occurs for every 3
		//this is indicative of the design of a square/cube
		//if it is 0 or 2, that would mean we are at a corner and we would want true
		if (xPos % 3 == 1 && yPos % 3 == 1)
		{
			
			return false;
			
		}
		
		//iterate through the shape, similar to when we truncate or replace an integer with /10
		xPos /= 3;
		yPos /= 3;
		
	}
	return true;
	
}

//take the carpet and recursively use the input from our above function
//iterate through the array and replace the values within
//rather than the function returning a value or printing to the console
//we change the original array to represent our new carpet. From this we can
//print the array to a file 
void createCarpet(char** carpet, int size)
{
	
	for (int i = 0; i < size; i++)
	{
		
		for (int j = 0; j < size; j++)
		{
			
			if (inside(i, j))
			{
				
				//fill with character
				carpet[i][j] = fill;
				
			}
			else
			{
				
				carpet[i][j] = ' '; //add space where applicable
				
			}
			
		}
		
	}
	
}

//take in the array and size of the array to print this to a file
void fileOut(char** array, int size)
{
	
	//file output stream
	ofstream newFile;
	
	//create the new textfile
	newFile.open("carpet.txt");
	
	
	//for loop to iterate through array
	for (int i = 0; i < size; i++)
	{
		
		for (int k = 0; k < size; k++)
		{
		
			//rather than assign new array variable like prev method
			//we print straight to the file. As we would not need this for further use within the function
			if (inside(i, k))
			{
				
				newFile << "#";
				
			}
			else
			{
				
				newFile << " ";
				
			}
			
		}
		//add spacing
		newFile << endl;
		
	}
	
	//close the file
	newFile.close();
	
	
	
}

int main()
{
	
	cout << "\n-----------------------------------------------------\nWelcome to the Sierpinski Carpet Maker\n-----------------------------------------------------\n";
	
	int layers;
	
	cout << "How many layers of carpet do you prefer?(1-8) --> ";
	cin >> layers;
	
	while(cin.fail() || layers < 0 || layers > 8) //check layer boundaries
	{
		
		cout << "\nInput is invalid\nPlease use a valid integer value\n";
		cin.clear();
		cin.ignore(256, '\n');
		cout << "How many layers of carpet do you prefer? --> ";
		cin >> layers;
	}
	
	char **carpet;
	
	int size = pow(3, layers);
	
	
	//dynamically allocate row and column space within the heap
	carpet = new char*[size];
	
	for (int i = 0; i < size; i++)
	{
		
		carpet[i] = new char[size];
		
	}
	
	createCarpet(carpet, size); //create the main carpet that we are going to output from user input
	
	if(layers <= 3) //output to console and file
	{
		printArray(carpet, size);
	}
	else //only output to a file
	{
		printArray(carpet, size);
		fileOut(carpet, size);
		
	}
	
	
	delete[] carpet;
	
	return 0;
	
}