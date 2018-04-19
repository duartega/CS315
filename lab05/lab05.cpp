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
void colorToGray(BMP& OutPut);
void OutOfBounds (BMP & Img, int sx, int sy, int tx, int ty);
bool isWhite (BMP & In, int x, int y);
void BFS (BMP & Img, int sx, int sy, int tx, int ty);
 
int main () {

  // Make the x and y coordinates
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
  InImg.SetBitDepth(16);

  // Ask the user the starting and ending point and read the points in
  cout << "Please enter the starting point for the x value: ";
  cin >> sx;
  cout << "Please enter the starting point for the y value: ";
  cin >> sy;
  cout << "Please enter the destination point for the x value: ";
  cin >> tx;
  cout << "Please enter the destination point for the y value: ";
  cin >> ty;

  // Lets the user know the size of the image
  cout << "Starting pixel is white if 1: " << isWhite(InImg, sx, sy) << " (" << sx << ", " << sy << ")" << endl;;
  cout << "Ending pixel is white if 1: " << isWhite (InImg, tx, ty)<< " (" << tx << ", " << ty << ")" << endl;

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

  //  BMP temp;
  
  int width = I.TellWidth();
  int height = I.TellHeight();
  // temp.SetSize(width, height);
  int index = width * sy + sx;
  int start = index;
  int end = width * ty + tx;
  
  
  queue<int> Q;
  Q.push(index);
  int count = 0;
  count++;
  
  //bool visited[width*height] = {false};
  bool *visited = new bool[width*height];
  for (int i = 0; i < width*height; i++) {
    visited[i] = false;
  }
  // Marks all the black pixels as visited
 for (int i = 0; i < width; i++)
   {
     for (int j = 0; j < height; j++)
       {
	 
	 visited[i + (j * width)] = !isWhite(I, i, j);
	 // temp (i, j) ->Red =
	 //   temp (i, j) ->Blue =
	 //   temp (i, j) -> Green =
	 //   visited[i + j * width] ? 0:255;
	 
       }
   }
 // temp.WriteToFile("temp.bmp");
 
 // Mark the first distance as -1
 int *d = new int[height * width];
 for (int i = 0; i < height * width; i++) {
   d[i] = -1;
 }
 int *P = new int[height * width]; 
 for (int i = 0; i < height * width; i++) {
   P[i] = 0;
 }
 
 visited[index] = true;
 d[0] = 0;


 while (!Q.empty() && !visited[end])
   {

     int u = Q.front();
     // cout << "Q: " <<  Q.front() << endl;
     Q.pop();


     int row = u / width;
     int col = u % width;

     int top = u - width;
     int bottom = u + width;
     int right = u + 1;
     int left = u - 1;

     if (col < (width - 1) && !visited[right])
       {
     	 visited[right] = true;
     	 d[right] = d[u] + 1;
	 
	 P[right] = u;
     	 Q.push(right);

     	 count++;
       }
     if (col > 0 && !visited[left])
       {
     	 visited[left] = true;
     	 d[left] = d[u] + 1;
	 
     	 P[left] = u;
     	 Q.push(left);
	 
     	 count++;
       }
     if (row > 0 && !visited[top])
       {
      	 visited[top] = true;
	 d[top] = d[u] + 1;
	 
	 P[top] = u;
     	 Q.push(top);
     	 count++;
       }
     if (row < (height - 1) && !visited[bottom])
       {
     	 visited[bottom] = true;
     	 d[bottom] = d[u] + 1;
	 
	 P[bottom] = u;
     	 Q.push(bottom);
     	 count++;
       }

}
 
 if (visited[end])
   {
     index = end;

     while (index != start) {
       // set pixels to red
       sx = index%width;
       sy = index/width;
       I (sx, sy) -> Red = 255;
       I (sx, sy) -> Green = 0;
       I (sx, sy) -> Blue = 0;
       index = P[index];
     };
     I.WriteToFile("OutputImg.bmp");
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


void colorToGray(BMP & Output)
{
  
  int picWidth = Output.TellWidth();
  int picHeight = Output.TellHeight();
  
  Output.SetBitDepth(1); //compression happens here
  
  for (int i = 0; i < picWidth-1; ++i)
    
    for (int j = 0; j < picHeight-1; ++j)
      {
	int col = 0.1* Output(i, j)->Blue + 0.6*Output(i,j)->Green +0.3* Output(i,j)->Red;
	
	if (col > 127)
	  {
	    Output(i,j)->Red = 255;
	    Output(i,j)->Blue = 255;
	    Output(i,j)->Green = 255;
	  }
      }
}
