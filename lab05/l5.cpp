// Author          : Gabriel Duarte
// Date            : 02/22/2018
// Class           : CS315
// Description     : This program will find the shortest path in a maze graph

// Include all the libraries
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdlib.h>
#include "EasyBMP.h"
#include <queue>

  
using namespace std;

// Declare all the functions
void colorToGray(BMP & OutPut);
void OutOfBounds (BMP & Img, int sx, int sy, int tx, int ty);
bool isWhite (BMP & In, int x, int y);
void BFS (BMP & Img, int sx, int sy, int tx, int ty);
 
int main () {

  // Sx and Sy are the x and y values for the start point. T is for ending point
  int sx, sy, tx, ty;

  // Create a BMP and file name variable then read in the file
  BMP InImg;
  string infile;

  cout << "Please enter file name: ";
  cin >> infile;
  
  // Read in the BMP image
  InImg.ReadFromFile(infile.c_str());
  
  // Print out the height and width of the image so the user knows the bounds
  cout << "This is the image size: " << InImg.TellWidth() << "x" << InImg.TellHeight() << endl;

  // Converts the image to a grey scaled image
  colorToGray(InImg);
  
  // Set pixel depth
  InImg.SetBitDepth(24);

  // Ask the user the starting and ending point and read the points in
  cout << "Please enter the starting point for the x value: ";
  cin >> sx;
  cout << "Please enter the starting point for the y value: ";
  cin >> sy;
  cout << "Please enter the destination point for the x value: ";
  cin >> tx;
  cout << "Please enter the destination point for the y value: ";
  cin >> ty;

  // Checks to see if the starting pixels or ending pixels are white, exit if they are not white
  if ((!isWhite(InImg, sx, sy) || (!isWhite(InImg, tx, ty)))) {
      cout << "\nThe pixel(s) selected is not white! Exiting!\n\n";
      exit(1);
    }
  
  // Checks to see if the points entered are out of bounds
  OutOfBounds(InImg, sx, sy, tx, ty);

  // Call BFS
  BFS (InImg, sx, sy, tx, ty);
    
  return 0;
}

void OutOfBounds (BMP & InImg, int sx, int sy, int tx, int ty)
{
  // This will output more specific errors rather than just saying out of bounds
  if ((sx > InImg.TellWidth()) || sy > InImg.TellHeight() || (sx < 0) || (sy < 0))
    {
      if (sx > InImg.TellWidth())
	cout << "The value that you entered is out of bounds! '" << sx << "' Exiting!\n";
      if (sx < 0)
	cout << "The value that you entered is out of bounds! '" << sx << "' Exiting!\n";
      if (sy > InImg.TellHeight())
        cout << "The value that you entered is out of bounds! '" << sy << "' Exiting!\n";
      if (sy < 0)
	cout << "The value that you entered is out of bounds! '" << sy << "' Exiting!\n";
      if (tx > InImg.TellWidth())
	cout << "The value that you entered is out of bounds! '" << tx << "' Exiting!\n";
      if (tx < 0)
	cout << "The value that you entered is out of bounds! '" << tx << "' Exiting!\n";
      if (ty > InImg.TellHeight())
	cout << "The value that you entered is out of bounds! '" << ty << "' Exiting!\n";
      if (ty < 0)
	cout << "The value that you entered is out of bounds! '" << ty << "' Exiting!\n";
      exit(2);
    }
}

// Will check if the pixel is white and returns true if it is, else returns false
bool isWhite (BMP & I, int x, int y)
{
  if (
      I (x, y) -> Red == 255 &&
      I (x, y) -> Green == 255 &&
      I (x, y) -> Blue == 255
      )
    return true;
  else
    return false;
}  

void BFS (BMP & I, int sx, int sy, int tx, int ty)
{
  // Get the width and height
  int width = I.TellWidth();
  int height = I.TellHeight();

  // Create the start and end points by flattening them
  int index = width * sy + sx;
  int start = index;
  int end = width * ty + tx;
  
  // Initialize the queue and push the starting point
  queue<int> Q;
  Q.push(index);

  // Initialize count
  int count = 0;
  count++;
  
  // Dynamically allocate memory for bigger images if needed. Deleted later on so there isnt a memory leak
  bool *visited = new bool[width*height];
  
  // Set the values so you dont have garbage data
  for (int i = 0; i < width*height; i++) {
    visited[i] = false;
  }
  
  // Marks all the black pixels as visited
 for (int i = 0; i < width; i++)
   {
     for (int j = 0; j < height; j++)
       {
	 
	 visited[i + (j * width)] = !isWhite(I, i, j);
       }
   }
 
 // Dynamically allocate memory for bigger images if needed. Deleted later on so there isnt a memory leak
 int *d = new int[height * width];
 
 // This is for the distance and set all to negative one so there isnt garbage data
 for (int i = 0; i < height * width; i++) {
   d[i] = -1;
 }

 // Dynamically allocate memory for bigger images if needed. Deleted later on so there isnt a memory leak
 int *P = new int[height * width];

 // This is for the parent array and sets all to 0 so there isnt garbage data
 for (int i = 0; i < height * width; i++) {
   P[i] = 0;
 }

 // Set the starting point as visited
 visited[index] = true;

 // Set the starting distance to 0
 d[0] = 0;

 // Runs until the Q is empty and we have reached the end point
 while (!Q.empty() && !visited[end])
   {
     // Store the front before we delete
     int u = Q.front();

     // Pop the first value
     Q.pop();

     // Variables to access the x and y coordinates for when we flatten the points
     int row = u / width;
     int col = u % width;

     // Variables for direction
     int top = u - width;
     int bottom = u + width;
     int right = u + 1;
     int left = u - 1;

     // Checks to the right by checking if the it is in bounds and the point hasnt been visited
     if (col < (width - 1) && !visited[right])
       {
	 // Set the point to visited
     	 visited[right] = true;

	 // Increment the distance
     	 d[right] = d[u] + 1;

	 // Push the parent to the P array
	 P[right] = u;

	 // Push the pixel onto to the queue
     	 Q.push(right);

	 // Increment count
     	 count++;
       }

     // Checks to the left by checking if the it is in bounds and the point hasnt been visited
     if (col > 0 && !visited[left])
       {
     	 visited[left] = true;
     	 d[left] = d[u] + 1;
	 
     	 P[left] = u;
     	 Q.push(left);
	 
     	 count++;
       }

     // Checks above the current pixel by checking if the it is in bounds and the point hasnt been visited
     if (row > 0 && !visited[top])
       {
      	 visited[top] = true;
	 d[top] = d[u] + 1;
	 
	 P[top] = u;
     	 Q.push(top);
     	 count++;
       }

     // Checks below the current pixel by checking if the it is in bounds and the point hasnt been visited
     if (row < (height - 1) && !visited[bottom])
       {
     	 visited[bottom] = true;
     	 d[bottom] = d[u] + 1;
	 
	 P[bottom] = u;
     	 Q.push(bottom);
     	 count++;
       }
}

 // If we have reached the end point then do things
 if (visited[end])
   {
     // Set the end to the start
     index = end;

     // Runs from the end to the start
     while (index != start)
       {
	 // Access the points that we flattened
	 sx = index%width;
	 sy = index/width;
	 
	 // set pixels to red
	 I (sx, sy) -> Red = 255;
	 I (sx, sy) -> Green = 0;
	 I (sx, sy) -> Blue = 0;

	 // Sets the index to the next pixel (parent)
	 index = P[index];
     };
     double finish_time = 0;
     double start_time = clock();
     
     // Write out the image to a BMP file
     I.WriteToFile("Output.bmp");

     finish_time = clock();
     double time = (finish_time - start_time) / CLOCKS_PER_SEC;
     cout << "This is the time it took to write out: " << time << endl;
     // Write out the count and the shortest distance
     cout << "D[end]: " << d[end] << endl;
     cout << "Count: " << count << endl;
   }
 else
   {
     cout << "No path found!" << endl;
   }

 // Deleting the arrays so we dont get a memory leak
 delete [] P;
 delete [] d;
 delete [] visited;
}

// Will convert the image to gray scale
void colorToGray(BMP & Output)
{
  int picWidth = Output.TellWidth();
  int picHeight = Output.TellHeight();
  
  Output.SetBitDepth(1); //compression happens here
  
  for (int i = 0; i < picWidth-1; ++i)
    
    for (int j = 0; j < picHeight-1; ++j)
      {
	int col = 0.1 * Output(i, j)->Blue + 0.6 * Output(i,j)->Green + 0.3 * Output(i,j)->Red;
	
	if (col > 127)
	  {
	    Output(i,j)->Red = 255;
	    Output(i,j)->Blue = 255;
	    Output(i,j)->Green = 255;
	  }
      }
}
