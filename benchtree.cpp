#include <iostream>
#include <cmath>
#include <algorithm>
#include <string.h>
#include <vector>
#include <set>
#include <stdlib.h>
#include "RST.hpp"
#include "BST.hpp"
#include "countint.hpp"

//Helper method that runs through the test and gets avgcomps
double indivTest(int num, bool sorted, int type)
{
  //Creates a vector with the items to be put in the tree
  std::vector<countint> v;
  v.clear();
  
  //Inserts the items into the vector
  for( int index = 0; index < num; index++)
  {
    v.push_back(index);
  }

  //Checks to see if the user inputed sorted or shuffled
  if(!sorted)
  {
    std::random_shuffle(v.begin(), v.end());
  }

  //Sets the beginning and end vectors
  std::vector<countint>::iterator vit = v.begin();
  std::vector<countint>::iterator ven = v.end();

  //Inserts and finds the items in a set
  if(type == 1)
  {
    std::set<countint> s;
    for(vit = v.begin(); vit != ven; ++vit)
    {
      s.insert(*vit);
    }
    countint::clearcount();
    for(vit = v.begin(); vit != ven; ++vit)
    {
      s.find(*vit);
    }
  }
  //Inserts and finds the items in a BST
  else if(type == 2)
  {
    BST<countint> b;
    for (vit = v.begin(); vit < ven; ++vit) 
    {
      b.insert(*vit);
    }
    countint::clearcount();
    for (vit = v.begin(); vit < ven; ++vit) 
    {
      b.find(*vit);
    }
  }
  //Inserts and finds the items in a RST
  else if(type == 3)
  {
    RST<countint> r;
    for (vit = v.begin(); vit != ven; ++vit) 
    {
      r.insert(*vit);  
    }
    countint::clearcount();
    for (vit = v.begin(); vit < ven; ++vit) {
      r.find(*vit);
    }
  }
  //Calculates the average number of comparisons and returns it
  double avgcomps = countint::getcount()/(double)num;
  return avgcomps;
}

//Helper method that calculates the avgcomps and stdev
void test(int num, bool sorted, int type, int N, double &avg, double &stdev)
{
  //Variables to keep track of the components for avgcomp and stdev
  double sum = 0.0; 
  double squares = 0.0;

  //Loop that runs the desired amount of trials and gather values from each
  for (int i = 0; i < N; ++i) 
  {
    double result = indivTest(num, sorted, type);
    sum += result;
    squares += (result * result);
  }
  
  //Calculates the value of avgcomps
  avg = sum / (double) N;

  //Calculates the value of stdev
  double avgsquares = squares / (double) N;
  
  //Creates threshold value for variance
  double epsilon = 0.00001;

  //Finds variance
  double var = avgsquares - (double) (avg * avg);

  //Takes away negative
  var = (double) abs(var);

  //Checks var for thresshold
  if (var < epsilon)
  {
    var = 0;
  }
 
  //Sets stdev value
  stdev = (double) sqrt(var);
}

//Main method that takes in 4 arguments
int main(int argc, char* argv[])
{
  //Throws error message if arguments are remotely wrong
  if(argc != 5)
  {
    std::cout << "Your arguments are incoorect, please try again" << std::endl;
    return -1;
  }

  //Used to check the type of data structure to use
  int type = 0;

  //Sets the type according to the user input of the first command
  if(!strcmp(argv[1], "set"))
  {
    type = 1;
  }
  else if (!strcmp(argv[1], "bst"))
  {
    type = 2;
  }
  else if (!strcmp(argv[1], "rst"))
  {
    type = 3;
  }

  //Used to check if the user wanted the vector to be sorted or shuffle
  bool flag = false;

  //Sets the flag according to the user input of the second command
  if(!strcmp(argv[2], "sorted"))
  {
    flag = true;
  }

  //Sets the values from the command line arguments using atoi
  int num = atoi(argv[3]);
  int N = atoi(argv[4]);

  //Print statements for the charts
  std::cout << "# Data Structure: " << argv[1] << std::endl;
  std::cout << "# Data: " << argv[2] << std::endl;
  std::cout << "# N is powers of 2, minus 1, from 1 to "<<argv[3]<<std::endl;
  std::cout << "# Averaging over " << argv[4] << " for each N" << std::endl;
  std::cout << "#" << std::endl;
  std::cout << "# N 	 avgcomps 	 stdev" << std::endl;

  //Set up some variables for the computations
  int index = 1;
  int runs = 1;
  double avg = 0.0;
  double stdev = 0.0;
  
  //While loop to take care of the ammount of runs and calls the helper methods
  while (runs <= num)
  {
    std::cout << runs << "\t\t";
    test(runs, flag, type, N, avg, stdev);
    std::cout << avg << "\t\t" << stdev << std::endl;
    runs += (int)pow(2, index);
    ++index;
  }

  return 0;
}
