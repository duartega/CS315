// Author   : Gabriel Duarte
// Date     : 01/30/2018
// Lab #    : 02 exercise 2
// Description : We are making a Sierpinski gasket.

// Include the library
#include "EasyBMP.h"
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
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
  triangle.WriteToFile("triangle.bmp");

  return 0;
}
