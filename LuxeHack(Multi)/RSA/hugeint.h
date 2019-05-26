/* 
* hugeint - the class to work with a big integers.
* Copyright(C) 2011 Alexey Dolgopolov.  
*
* The capacity of the number can be given as an argument
* of the constructor(10 by default).
* This class is compatible with int.
*/


#include<iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include "exceptions.h"


using namespace std;


class hugeint
{       
  short *number;
  unsigned  int currentSize;
  unsigned int maxSize;
  //if true then number is positive
  bool positive;
  void reflect();
  //removing zeros (for example 0014 -> 14)
  void removeSpace();
  //returns true if obj > *this in absolute value
  bool isAbsBigger(const hugeint &obj);
  //integer division/remainder
  hugeint divMod(const hugeint &obj, hugeint &reminder);
public:
  hugeint();
  hugeint(unsigned int n);
  ~hugeint();
  hugeint(const hugeint &obj);
  //add obj to the current value as string
  void concat(const hugeint &obj);
  vector <char> toBinary();
  //get current size
  int size();
  //power
  hugeint pow(const unsigned int power);
  //returns A^d(mod m) 
  //A = *this
  hugeint calcPowMod(const vector <char> &d, const hugeint m);
  void random(unsigned int length);
  //returns true if this value is even
  bool even();
  //MillerRabin primality test
  bool prime();
  hugeint getMaxDiviser(hugeint b);
  hugeint abs();
  hugeint operator=(const hugeint &obj);
  hugeint operator=(const int b);
  hugeint operator+(const hugeint &obj);
  hugeint operator+(const int b);
  hugeint operator*(const hugeint &obj);
  hugeint operator*(const int b);
  hugeint operator-(const hugeint &obj);
  hugeint operator-(const int b);
  hugeint operator%(const hugeint &obj);
  hugeint operator%(const int b);
  hugeint operator/(const hugeint &obj);
  hugeint operator/(const int b);
  hugeint operator+=(const hugeint &obj);
  hugeint operator+=(const int b);
  hugeint operator-=(const hugeint &obj);
  hugeint operator-=(const int b);
  bool operator>(const hugeint &obj);
  bool operator>(const int b);
  bool operator<(const hugeint &obj);
  bool operator<(const int b);
  bool operator==(const hugeint &obj);
  bool operator==(const int b);
  bool operator!=(const hugeint &obj);
  bool operator!=(const int b);
  bool operator>=(const hugeint &obj);
  bool operator>=(const int b);
  bool operator<=(const hugeint &obj);
  bool operator<=(const int b);
  friend hugeint operator-(const hugeint &obj);
  friend hugeint operator+(const int a, const hugeint &b);
  friend hugeint operator-(const int a, const hugeint &b);
  friend hugeint operator*(const int a, const hugeint &b);
  friend hugeint operator/(const int a, const hugeint &b);
  friend hugeint operator%(const int a, const hugeint &b);
  friend bool operator>(const int a, const hugeint &b);
  friend bool operator<(const int a, const hugeint &b);
  friend bool operator==(const int a, const hugeint &b);
  friend bool operator!=(const int a, const hugeint &b);
  friend bool operator>=(const int a, const hugeint &b);
  friend bool operator<=(const int a, const hugeint &b);
  friend ostream& operator<<(ostream &out, const hugeint &obj);
  friend istream& operator>>(istream &in, hugeint &obj);
};
