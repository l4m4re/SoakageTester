/* A Simple GPIO application
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include<iostream>
#include<unistd.h> //for usleep
#include"GPIO.h"
using namespace exploringBB;
using namespace std;

int main(){
   GPIO outGPIO(49);

   // Basic Output
   outGPIO.setDirection(OUTPUT);
   for (;;){
      outGPIO.setValue(HIGH);
      usleep(5000); //micro-second sleep 0.005 seconds
      outGPIO.setValue(LOW);
      usleep(5000);
   }
   return 0;
}
