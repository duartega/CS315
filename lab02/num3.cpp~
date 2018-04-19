// Author   : Gabriel Duarte
// Date     : 01/30/2018
// Lab #    : 02
// Description : There are multiple labs in this file and descriptions for each are down below

// Include the library
#include "EasyBMP.h"
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

void scaleing(BMP & In, BMP & Out); // Function prototype to shrink the image
void place_tile(BMP & Out, BMP & In, int x, int y); // Copies the image
void tile(BMP & Out, BMP & temp_tile); // Places the images

void part1 (); // The function that is exercise 1's main. We are creating a checker board.
void part2 (); // The function that is exercise 2's main. We are creating a serpenski gasket.
void part3 (); // The funciton that is exercise 3's main. We are creating a shrunk and tiled image of Einstein.

int main()
{
  // The calls for exercise 1, 2, and 3's main
  part1();
  part2();
  part3();
  
  return 0;
}

void part1()
{
  // Create an image
  BMP AnImage;
  
  // Set the image size
  AnImage.SetSize(256,256);
  // Set the bit depth
  AnImage.SetBitDepth(8);
  
  // The for loop for the rows
  for (int i = 0; i < 256; ++i)
    { // The for loop for the cols
      for (int j = 0; j < 256; ++j)
	{
	  // Make it a red square
	  if ((i/32)%2 == 0 && (j/32)%2 == 0)
	    {
	      AnImage (i,j)->Red = 255;
	      AnImage (i,j)->Green = 0;
	      AnImage (i,j)->Blue = 0;
	    }
	  else  if ((j/32)%2 == 1 && (i/32)%2 == 1)
	    {
	      AnImage (i,j)->Red = 255;
	      AnImage (i,j)->Green = 0;
	      AnImage (i,j)->Blue = 0;
	    }
	  
	  // Make it a black square
	  else
	    {
	      AnImage (i,j)->Red = 0;
	      AnImage (i,j)->Green = 0;
	      AnImage (i,j)->Blue = 0;
	    }	  
	}
    }
  
  // Output the image to a "file" 
  AnImage.WriteToFile("board.bmp");
}

void part2()
{
  // Create an image
  BMP triangle;
  
  // Set the image size
  triangle.SetSize(256,256);
 
  // Create the arrays for the points
  int array[3][2] = {{128,5},{5,251},{251,251}};
  int array2[1][2] = {{171,34}};

  // Start the for loop to do the formula and draw
  for (int i = 0; i < 100000; i++)
    {

      // Graba random point
      int randpt = rand() % 3;
      int value1 = (array[randpt][0] + array2[0][0]) / 2;
      int value2 = (array[randpt][1] + array2[0][1]) / 2;

      // Change the values
      array2[0][0] = value1;
      array2[0][1] = value2;

      // Draw the red "pixels"
      triangle (value1, value2)->Red = 255;
      triangle (value1, value2)->Green = 0;
      triangle (value1, value2)->Blue = 0;
    }
  
  // Output the image to a "file" 
  triangle.WriteToFile("sierpinski.bmp");
}

void part3()
{
    // Create 3 windows and read in an image
  BMP In;
  BMP temp;
  BMP Out;
  In.ReadFromFile("e.bmp");
  
  // Set the image sizes for Out
  Out.SetSize(In.TellWidth(), In.TellHeight());

  // Call the shrink function and tile function
  scaleing(In, temp);
  tile(Out, temp);
  
  // Write the image to a file
  Out.WriteToFile("tile.bmp");
}

// Copies the image
void place_tile (BMP & Out, BMP & In, int x, int y)
{
  RangedPixelToPixelCopy(In, 0, In.TellWidth()-1, 0, Out.TellHeight()-1, Out, x, y);
}

// Places the images
void tile(BMP & Out, BMP & temp_tile)
{
  // Keep count so we dont go out of bounds
  int tile_count = Out.TellHeight() / temp_tile.TellHeight() - 1;

  // For loop for the tile placements
  for (int i = 0; i < tile_count; i++)
  {
    place_tile(Out, temp_tile, i * temp_tile.TellWidth(), temp_tile.TellWidth()); // Draws the horizontal tiles
    place_tile(Out, temp_tile, (tile_count - 1) * temp_tile.TellWidth(), temp_tile.TellHeight() * (i + 1)); // Draws the tiles vertically
  }

  if (temp_tile.TellWidth() <= 1 || temp_tile.TellHeight() <= 1) // Base case is 1 pixel
    {
      //Out = temp;
      return;
    }
  BMP temp; // Create a temp to make a "smaller image"
  scaleing (temp_tile, temp); // Shrink the temp
  
  tile (Out, temp);  // Will call the function recursively
}

// This function will shrink the image
void scaleing(BMP & In, BMP & Out)
{ // Set the size
  Out.SetSize(In.TellWidth(), In.TellHeight());
  place_tile(Out, In, 0, 0); // Make the call to place_tile to copy the image
  Rescale(Out, 'p', 50); // Rescale the image
}
