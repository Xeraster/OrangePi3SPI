/*
gpiod compatible spi. Made for OrangePi3B but any gpiod system should work as long as it's 3.3 volts logic levels and as long as its possible to figure out the chip and line numbers for yourself
to compile, use:
g++ main.cpp -lgpiod
*/

#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include <linux/gpio.h>

#include <gpiod.h> //sudo apt install libgpiod libgpiod-dev
// https://www.ics.com/blog/gpio-programming-exploring-libgpiod-library+

#include <vector>

using namespace std;

/*use chip 4 pins 0-3 for the software defined spi
i know there is probably hardware accelerated spi but i NEVER want to program spi in c++ again
This code can probably be shoehorned into anything just due to the hyper-simplified approach being taken*/
const int CHIPNUM = 4;
const int SCK = 0;
const int SS = 1;
const int SO = 2;
const int SI = 3;

#include "utils.h"
#include "spi.h"
#include "color.h"

//fetch all of the gpio0 lines that can be fetched without causing a crash
vector<int> &getAllGpio0Lines()
{
  vector<int> *vec = new vector<int>();
  for (int i = 0; i < 32; i++)
  {
    vec->push_back(-2);
  }

  gpiod_chip *chip0 = gpiod_chip_open_by_name("gpiochip0");

  for (int i = 0; i < 32; i++) 
  {
    if ((i < 3 || i > 10) && i != 14 && i != 15 && i != 16 && i != 27) 
	  {
      gpiod_line *testline3 = gpiod_chip_get_line(chip0, i); // FINALLY IT HAS BEEN FOUND!!
      int status3 = gpiod_line_request_input(testline3, "testline3");
      if (status3 == 0) 
	    {
        // only get the value of that pin can be got
        //cout << "line" << i << " = " << gpiod_line_get_value(testline3) << endl;
        vec->at(i) = gpiod_line_get_value(testline3);
      } 
	    else 
	    {
        //cout << "line" << i << " = x" << endl;
        vec->at(i) = -3;
      }
      gpiod_line_release(testline3);
    }
  }

  gpiod_chip_close(chip0);
  return *vec;
}

//fetch all of the gpio0 lines that can be fetched without causing a crash
vector<int> &getAllGpio2Lines()
{
  vector<int> *vec = new vector<int>();
  for (int i = 0; i < 32; i++)
  {
    vec->push_back(-2);
  }

  gpiod_chip *chip0 = gpiod_chip_open_by_name("gpiochip2");

  for (int i = 0; i < 32; i++) 
  {
    if (i != 15 && i != 16 && i != 17) 
	  {
      gpiod_line *testline3 = gpiod_chip_get_line(chip0, i); // FINALLY IT HAS BEEN FOUND!!
      int status3 = gpiod_line_request_input(testline3, "testline3");
      if (status3 == 0) 
	    {
        // only get the value of that pin can be got
        //cout << "line" << i << " = " << gpiod_line_get_value(testline3) << endl;
        vec->at(i) = gpiod_line_get_value(testline3);
      } 
	    else 
	    {
        //cout << "line" << i << " = x" << endl;
        vec->at(i) = -3;
      }
      gpiod_line_release(testline3);
    }
  }

  gpiod_chip_close(chip0);
  return *vec;
}

//fetch all of the gpio1 lines that can be fetched. this will always crash the system, there is nothing that can be done about it
vector<int> &getAllGpio1Lines()
{
  vector<int> *vec = new vector<int>();
  for (int i = 0; i < 32; i++)
  {
    vec->push_back(-2);
  }

  gpiod_chip *chip0 = gpiod_chip_open_by_name("gpiochip1");

  for (int i = 0; i < 32; i++) 
  {
    //if ((i < 3 || i > 10) && i != 14 && i != 15 && i != 16 && i != 27) 
	  //{
      gpiod_line *testline3 = gpiod_chip_get_line(chip0, i); // FINALLY IT HAS BEEN FOUND!!
      int status3 = gpiod_line_request_input(testline3, "testline3");
      if (status3 == 0) 
	    {
        // only get the value of that pin can be got
        //cout << "line" << i << " = " << gpiod_line_get_value(testline3) << endl;
        vec->at(i) = gpiod_line_get_value(testline3);
      } 
	    else 
	    {
        //cout << "line" << i << " = x" << endl;
        vec->at(i) = -3;
      }
      gpiod_line_release(testline3);
    //}
  }

  gpiod_chip_close(chip0);
  return *vec;
}

//fetch all of the gpio0 lines that can be fetched without causing a crash
vector<int> &getAllGpio3Lines()
{
  vector<int> *vec = new vector<int>();
  for (int i = 0; i < 32; i++)
  {
    vec->push_back(-2);
  }

  gpiod_chip *chip0 = gpiod_chip_open_by_name("gpiochip3");

  for (int i = 0; i < 32; i++) 
  {
    if (i != 18) 
	  {
      gpiod_line *testline3 = gpiod_chip_get_line(chip0, i); // FINALLY IT HAS BEEN FOUND!!
      int status3 = gpiod_line_request_input(testline3, "testline3");
      if (status3 == 0) 
	    {
        // only get the value of that pin can be got
        //cout << "line" << i << " = " << gpiod_line_get_value(testline3) << endl;
        vec->at(i) = gpiod_line_get_value(testline3);
      } 
	    else 
	    {
        //cout << "line" << i << " = x" << endl;
        vec->at(i) = -3;
      }
      gpiod_line_release(testline3);
    }
  }

  gpiod_chip_close(chip0);
  return *vec;
}

//fetch all of the gpio0 lines that can be fetched without causing a crash
vector<int> &getAllGpio4Lines()
{
  vector<int> *vec = new vector<int>();
  for (int i = 0; i < 32; i++)
  {
    vec->push_back(-2);
  }

  gpiod_chip *chip0 = gpiod_chip_open_by_name("gpiochip4");

  for (int i = 0; i < 32; i++) 
  {
    //if (i != 18) 
	  //{
      gpiod_line *testline3 = gpiod_chip_get_line(chip0, i); // FINALLY IT HAS BEEN FOUND!!
      int status3 = gpiod_line_request_input(testline3, "testline3");
      if (status3 == 0) 
	    {
        // only get the value of that pin can be got
        //cout << "line" << i << " = " << gpiod_line_get_value(testline3) << endl;
        vec->at(i) = gpiod_line_get_value(testline3);
      } 
	    else 
	    {
        //cout << "line" << i << " = x" << endl;
        vec->at(i) = -3;
      }
      gpiod_line_release(testline3);
    //}
  }

  gpiod_chip_close(chip0);
  return *vec;
}

//print the differences between the 2 vectors
void getVectorDiff(vector<int> *first, vector<int> *second)
{
  vector<int> diffPositions;
  for (int i = 0; i < 32; i++)
  {
    if (first->at(i) != second->at(i))
    {
      diffPositions.push_back(i);
    }
  }

  //now, print all the differences
  for (int i = 0; i < diffPositions.size(); i++)
  {
    cout << "mismatch at pos " << diffPositions.at(i) << endl;
  }
}

//get the value of any single line. does not filter out crashing commands, it's fully impossible to avoid gpio-induced crashes if you don't already know which ones crash anyway
int getSingleLine(int chipNum, int lineNum)
{
  int recordedValue = -10;
  string chipName = "gpiochip" + to_string(chipNum);
  gpiod_chip *chip = gpiod_chip_open_by_name(chipName.c_str());
  gpiod_line *testline = gpiod_chip_get_line(chip, lineNum);
  int status3 = gpiod_line_request_input(testline, "testline");
  if (status3 == 0)
  {
    recordedValue = gpiod_line_get_value(testline);
  }
  else
  {
    recordedValue = -1;
  }

  gpiod_line_release(testline);
  gpiod_chip_close(chip);

  return recordedValue;
}

/*int outputLine(int chipNum, int lineNum)
{
  gpiod_line_set_value
  return 0;
}*/

void switchToTestmode(gpiod_chip *chip, gpiod_line *sckline, gpiod_line *soline, gpiod_line *siline, gpiod_line *ssline)
{
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xB3,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0x00,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 1
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
}

void switchToVramMode(gpiod_chip *chip, gpiod_line *sckline, gpiod_line *soline, gpiod_line *siline, gpiod_line *ssline)
{
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xB3,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xFF,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 1
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
}

//uses the spi interface to set the ice40 video card's address register to some arbitrary value suitable for testing. Guarenteed to be an address on the screen's viewable area but that's about it.
void setVramAddress(gpiod_chip *chip, gpiod_line *sckline, gpiod_line *soline, gpiod_line *siline, gpiod_line *ssline)
{
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xB0,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xF0,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 1
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);

  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xB1,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0x00,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 1
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);

  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xB2,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0x00,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 1
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
}

/*sets the ice 40 video cards address register to a 20 bit value.
@param vramAddress the address to set the ice 40 video card address register to. numbers larger than 20 bits are concatenated to 20 bit values (probably, unless I got lazy, didnt do it and then didnt update this comment)
*/
void setVramAddressable(unsigned int vramAddress, gpiod_chip *chip, gpiod_line *sckline, gpiod_line *soline, gpiod_line *siline, gpiod_line *ssline)
{
  //since the ice 40 video card splits the address into 3 registers, splits vramAddress into 3 unsigned chars. or something
  unsigned char lowByte, mediumByte, highByte;

  lowByte = (vramAddress & 0xFF);
  mediumByte = (vramAddress >> 8) & 0xFF;
  highByte = (vramAddress >> 16) & 0x0F;

  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xB0,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(lowByte,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 1
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);

  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xB1,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(mediumByte,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 1
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);

  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xB2,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(highByte,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 1
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
}

void writePixel(gpiod_chip *chip, gpiod_line *sckline, gpiod_line *soline, gpiod_line *siline, gpiod_line *ssline)
{
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xB4,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xFF,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 1
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0xFF,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 1
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
}

unsigned char getStatus(gpiod_chip *chip, gpiod_line *sckline, gpiod_line *soline, gpiod_line *siline, gpiod_line *ssline)
{
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  spiSendByte(0x80,chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 1
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);

  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(ssline, 0);//it's active low ss
  unsigned char status = spiReadByte(chip, soline, siline, sckline);
  gpiod_line_set_value(ssline, 1);//it's active low and were done with it, so set to 1
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  gpiod_line_set_value(sckline, 1);
  usleep(1);
  gpiod_line_set_value(sckline, 0);
  usleep(1);
  usleep(20);
  return status;
}

// draws a square somewhere on the screen
void drawASquareOrSomething(color whatColor, gpiod_chip *chip, gpiod_line *sckline, gpiod_line *soline, gpiod_line *siline, gpiod_line *ssline)
{
  for (int r = 0; r < 20; r++)
  {
    setVramAddressable(100 + (640 * r), chip, sckline, soline, siline, ssline);
    for (int i = 0; i < 200; i++)
    {
      waitReady(chip, sckline, soline, siline, ssline);
      writePixel(chip, sckline, soline, siline, ssline);
    }
  }
}

void waitReady(gpiod_chip *chip, gpiod_line *sckline, gpiod_line *soline, gpiod_line *siline, gpiod_line *ssline)
{
  bool status = getStatus(chip, sckline, soline, siline, ssline);
  while (status > 0)
  {
    status = getStatus(chip, sckline, soline, siline, ssline);
  }
}

//make CLK be chip 4 line 0
//DATA can be chip 4 line 2
//THIS HAS TO BE RUN AS ROOT!! IF ITS CRASHING FOR NO REASON, THIS IS PROBABLY WHY
int main() 
{

  /*string inputwhatever;
  cin >> inputwhatever;
  cout << binaryStringToHex(inputwhatever) << endl;
  return 0;*/

  //cout << getSingleLine(3, 30) << endl;
  //try to do a output

  //cout << "test1" << endl;
  string chipName = "gpiochip" + to_string(CHIPNUM);
  //string chipName = "gpiochip4";
  //cout << "test2" << endl;
  //gpiod_chip *chip = gpiod_chip_open_by_name(chipName.c_str());
  gpiod_chip *chip = gpiod_chip_open_by_name(chipName.c_str());
  //gpiod_chip *chip = gpiod_chip_open_by_number(4);
  if (chip == nullptr)
  {
    cout << "Error! chip equals nullptr. Are you running as root?" << endl;
  }

  //get all the lines allocated and stuff
  gpiod_line *sckline = gpiod_chip_get_line(chip, SCK);
  gpiod_line *ssline = gpiod_chip_get_line(chip, SS);
  gpiod_line *soline = gpiod_chip_get_line(chip, SO);
  gpiod_line *siline = gpiod_chip_get_line(chip, SI);
  int sckStatus = gpiod_line_request_output(sckline, "sckline", 0); //host to slave, therefore output
  int ssStatus = gpiod_line_request_output(ssline, "ssline", 1);  //host to slave, therefore output
  int soStatus = gpiod_line_request_output(soline, "soline", 0);  //host to slave, therefore output
  int siStatus = gpiod_line_request_input(siline, "siline");  //input: slave to host
  //default values MATTER.

  if (sckStatus != 0 || ssStatus != 0 || soStatus != 0 || siStatus != 0)
  {
      cout << "Error detected:" << endl;
      cout << "sckStatus = " << to_string(sckStatus) << endl;
      cout << "ssStatus = " << to_string(ssStatus) << endl;
      cout << "soStatus = " << to_string(soStatus) << endl;
      cout << "siStatus = " << to_string(siStatus) << endl;
  }
  else
  {
    cout << "all spi lines requested and allocated sucessfully" << endl;
  }

  //bool gtfo = false;
  bool gtfo = true;
  bool alreadyReset = false;
  int data = 0;
  bool activation = false;

  unsigned char gpustatus = getStatus(chip, sckline, soline, siline, ssline);
  cout << "the status is " << intToBinary(gpustatus) << endl;

  string breakpoint2;
  cout << "do the breakpoint cin dance to continue" << endl;
  cin >> breakpoint2;
  
  switchToVramMode(chip, sckline, soline, siline, ssline);

  //setVramAddress(chip, sckline, soline, siline, ssline);

  string breakpoint3;
  cout << "do the breakpoint cin dance to continue" << endl;
  cin >> breakpoint3;

  /*for (int i = 0; i < 200; i++)
  {
    waitReady(chip, sckline, soline, siline, ssline);
    writePixel(chip, sckline, soline, siline, ssline);
  }*/
 //attempt to draw a square using this untested probably non-working code but hopefully there will be a nice light show at least
 color testColor = color(31, 63, 31);
 drawASquareOrSomething(testColor, chip, sckline, soline, siline, ssline);

  string breakpoint;
  cout << "do the breakpoint cin dance to continue" << endl;
  cin >> breakpoint;

  switchToTestmode(chip, sckline, soline, siline, ssline);

  while (gtfo == false)
  {
    
  }

  gpiod_line_release(sckline);
  gpiod_line_release(ssline);
  gpiod_line_release(siline);
  gpiod_line_release(soline);
  gpiod_chip_close(chip);

  /*cout << "exit after timeout and detect = " << detect << endl;

  cout << "contents of data vector = ";
  string shutUp = "";
  for (int i = 0; i < valsSoFar.size(); i++)
  {
    cout << valsSoFar.at(i);
    shutUp += to_string(valsSoFar.at(i));
  }
  cout << endl;
  cout << binaryStringToHex(shutUp) << endl;*/

  //remmeber to return 0 to avoid doing all that other stuff
  return 0;

  //dont do any of this stuff, it crashes the system
  vector <int> gpiovals0 = getAllGpio0Lines();
  vector <int> gpiovals1 = getAllGpio1Lines();
  vector <int> gpiovals2 = getAllGpio2Lines();
  vector <int> gpiovals3 = getAllGpio3Lines();
  vector <int> gpiovals4 = getAllGpio4Lines();
  cout << "change the logic level then press enter" << endl;
  string pressanykey;
  cin >> pressanykey;
  vector <int> gpiovals0_again = getAllGpio0Lines();
  vector <int> gpiovals1_again = getAllGpio1Lines();
  vector <int> gpiovals2_again = getAllGpio2Lines();
  vector <int> gpiovals3_again = getAllGpio3Lines();
  vector <int> gpiovals4_again = getAllGpio4Lines();

  cout << "===GPIOCHOP0===" << endl;
  getVectorDiff(&gpiovals0, &gpiovals0_again);
  cout << endl << "===GPIOCHOP1===" << endl;
  getVectorDiff(&gpiovals1, &gpiovals1_again);
  cout << endl << "===GPIOCHOP2===" << endl;
  getVectorDiff(&gpiovals2, &gpiovals2_again);
  cout << endl << "===GPIOCHOP3===" << endl;
  getVectorDiff(&gpiovals3, &gpiovals3_again);
  cout << endl << "===GPIOCHIP4===" << endl;
  getVectorDiff(&gpiovals4, &gpiovals4_again);
  
  cout << "done" << endl;
  return 0; // just stop here

  // backspacing all that shit to maintain good formatting is too hard, i'll fix
  // it next time im viewing this code on something with a GOOD c++ language
  // server
  for (int i = 3; i < 4; i++) {
    // cout << "about to declare structs" << endl;
    struct gpiod_chip *chip;
    struct gpiod_line *testLine;
    // cout << "about to figure out chip" << endl;
    string chipName = "gpiochip" + to_string(i);
    chip = gpiod_chip_open_by_name(chipName.c_str());

    // brute force every single gpio line until i find one that ever
    // changes
    string valsSoFar = "";
    for (int i = 0; i < 32; i++) {
      // cout << "about to get the line" << endl;
      testLine = gpiod_chip_get_line(chip, i); // try. them. all.

      // cout << "about to set line to input" << endl;
      string name = "test" + to_string(i);
      int status = gpiod_line_request_input(testLine, name.c_str());

      if (status == 0) {
        // cout << "about to request output of line" << endl;
        int val = gpiod_line_get_value(testLine);
        // cout << "the value of line " << i << " on " << chipName << " is " <<
        // val << endl;
        valsSoFar += to_string(val);

        // remember to do the proper closing stuff
        gpiod_line_release(testLine);
      } else {
        valsSoFar += "x";
      }
    }
    // close the chip, whatever that means
    gpiod_chip_close(chip);
    cout << chipName << " pins = " << valsSoFar << endl;
    usleep(1000); // sleep for 1 millisecond to see if that stops io errors
  }

  return 0;
}
