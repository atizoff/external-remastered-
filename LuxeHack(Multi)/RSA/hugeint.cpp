#include "hugeint.h"


hugeint::hugeint(): currentSize(0),  maxSize(10), positive(true)
{ 
  number = new short [maxSize];
  for (unsigned int i = 0; i < maxSize; i++)
    number[i] = 0;
}


hugeint::hugeint(unsigned int n): currentSize(0), maxSize(n), positive(true)
{ 
  number = new short [maxSize]; 
  for (unsigned int i = 0; i < maxSize; i++)
    number[i] = 0;
}


hugeint::hugeint(const hugeint &obj): currentSize(obj.currentSize), maxSize(obj.maxSize),
  positive(obj.positive)
{
  number = new short [maxSize];
  for (unsigned int i = 0; i < maxSize; i++)
    number[i] = obj.number[i];
}


hugeint::~hugeint() { delete [] number; }


hugeint hugeint::operator=(const hugeint &obj)
{
  delete [] number;
  maxSize = obj.maxSize;
  currentSize = obj.currentSize;
  positive = obj.positive;
  number = new short [maxSize];
  for (unsigned int i = 0; i < currentSize; i++)
    number[i] = obj.number[i];
  return *this;
}


//convert value to binary 
vector <char> hugeint::toBinary()
{
  vector <char> result, temp;
  hugeint q, reminder,hex;
  hex = 16;
  q = *this;
  short hexVal = 0;


  //to hex
  while ( q != 0)
  {
   
    q = q.divMod(hex, reminder);


    if (reminder.currentSize == 1)
      hexVal = reminder.number[0];
    else
      if (reminder.currentSize == 2)
        hexVal = reminder.number[0]+reminder.number[1]*10;
      else
        hexVal = 0;


    
    for (int j = 0; j < 4; j++)
    {
      char buff;
      (hexVal&1)?(buff = 1):(buff = 0);
      temp.push_back(buff);
      hexVal = hexVal>>1;
    }
  }


 
  bool first = true;
  for (int i = (int)temp.size()-1; i >= 0; i--)
  {
    if (temp[i] == 1)
      first = false;
    if (!first)
      result.push_back(temp[i]);
  }
  return result;
}


int hugeint::size()  {  return currentSize; }


hugeint hugeint::pow(const unsigned int power)
{
 
  hugeint res;
  if (power == 0)
  {
    res = 1;
    return res;
  }


  res = *this;
  hugeint pw;
  pw = power;


 
  vector <char> d = pw.toBinary();


  for(unsigned int i = 1; i < d.size(); i++)
  {
    if (d[i])
      res = (res*res**this);
    else
      res = (res*res);
  }




  if (pw.even())
    res.positive = true;
  else
    res.positive = positive;


  return res;
}


//a^d(mod m) 
hugeint hugeint::calcPowMod(const vector <char> &d, const hugeint m)
{ 
  hugeint res;
  res = *this;


  for(unsigned int i = 1; i < d.size(); i++)
  {
    if (d[i])
      res = ((res*res)**this) % m;
    else
      res = (res*res) % m;
    //cout << "repeat = " << i <<endl;
  }
  return res;
}


 //MillerRabin primality test
bool hugeint::prime()
{


  if (*this == 1 || currentSize == 0)
    return false;


  if (*this == 2 || *this == 3)
    return true;


  if (even())
    return false;


  hugeint temp(*this);
  hugeint x;
  hugeint a(currentSize);
  hugeint t(temp);
  temp -= 1;
  int s = 0;


  do
  {
    t = t/2;
    s++;
  }
  while ( t.even());


  //t to binary
  vector <char> bint;
  bint = t.toBinary();


  //2 to binary
  vector <char> bintwo;
  bintwo.push_back(1);
  bintwo.push_back(0);


  unsigned int i = 0;


  while (i < currentSize)
  {
start:


    if ( i == currentSize-1)
      break;
    i++;


    // cout << "Repeat " << i << " of "<< currentSize-1 <<endl;
    //get random value a
    if (currentSize > 3)
    {
      int randomSize;
      randomSize = rand()%(currentSize-3)+2;
      a.random(randomSize);
    }
    else
      do
    a.random(1);
    while (!( a > 1 && a < temp));


    //getting a^t mod *this
    x = a.calcPowMod(bint, *this);


    if ((x == 1) || (x == temp))
      continue;


    for (int j = 0; j < s-1; j++)
    {
      x = x.calcPowMod(bintwo, *this);


      if (x == 1)
        return false;
      if (x == temp)
        goto start;
    }


    //not prime
    return false;
  }


  return true;
}


//GBR
hugeint hugeint::getMaxDiviser(hugeint b)
{
  hugeint a(*this);
  hugeint c;
  while (b != 0)
  {
    c = a % b;
    a = b;
    b = c;
  }
  return a.abs();
}


hugeint hugeint::abs()
{
  hugeint temp(*this);
  temp.positive = true;
  return temp;
}


hugeint hugeint::operator=(const int b)
{  
  currentSize = 0;
  positive = true;
  string str;
  char temp;
  unsigned int i = 0;


  if (b < 0)
    positive = false;


  if (b == 0)
  {
    for (unsigned int i = 0; i < maxSize; i++)
      number[i] = 0;
    return *this;
  }


  stringstream mystream;
  mystream << ::abs(b);
  mystream >> str;


  while (i < str.length())
  {
    if (i == maxSize)
      break;
    temp = str[i];
    mystream.clear();
    mystream << temp;
    mystream >> number[i];
    i++;
    currentSize++;
  }


  reflect();
  return *this;
}


hugeint hugeint::operator+(const hugeint &obj)
{
  int newsize;
  (maxSize >= obj.maxSize)?
    (newsize = maxSize+1):(newsize = obj.maxSize+1);


  hugeint temp(newsize);
  register  short chache = 0;
  register short summ = 0;
  register short a,b;
  unsigned  int maxpos;


  if (currentSize == 0 && obj.currentSize == 0)
    return temp;


  (currentSize >= obj.currentSize)?
    (maxpos = currentSize-1):(maxpos = obj.currentSize-1);


  if ((positive && obj.positive) || (!positive && !obj.positive  ))
  {
    unsigned int i;
    for ( i = 0; i <= maxpos; i++)
    {
      summ = chache;


      (currentSize > i)?(a = number[i]):(a = 0);
      (obj.currentSize > i)?(b = obj.number[i]):(b = 0);


      summ += a+b;


      chache = short (summ/10.0);
      summ = summ - chache*10;


      temp.number[i] = summ;
      temp.currentSize++;
    }
    if (chache)
    {
      temp.number[i] = chache;
      temp.currentSize++;
    }
    if (!positive && !obj.positive)
      temp.positive = false;
  }
  else
    if ((!positive && obj.positive) || (positive && !obj.positive))
    {
      if (!isAbsBigger(obj))
      {
        for (unsigned  int i = 0; i <= maxpos; i++)
        {
          summ = chache;
          chache = 0;


          (currentSize > i)?(a = number[i]):(a = 0);
          (obj.currentSize > i)?(b = obj.number[i]):(b = 0);


          if  (a+summ >= b)
            summ += a - b;
          else
          {
            summ += a + 10 - b;
            chache = -1;
          }


          temp.number[i] = summ;
          temp.currentSize++;
          if (!positive && obj.positive)
            temp.positive = false;
        }
      }
      else
      {
        for ( unsigned int i = 0; i <= maxpos; i++)
        {
          summ = chache;
          chache = 0;


          (currentSize > i)?(a = number[i]):(a = 0);
          (obj.currentSize > i)?(b = obj.number[i]):(b = 0);


          if  (b+summ >= a)
            summ += b - a;
          else
          {
            summ += b + 10 - a;
            chache = -1;
          }


          temp.number[i] = summ;
          temp.currentSize++;
        }
        if (positive && !obj.positive)
          temp.positive = false;
      }
    }


    temp.removeSpace();
    return temp;
}


hugeint hugeint::operator+(const int b)
{
  hugeint res, temp;
  temp = b;
  res =  temp + *this;
  return res;
}


hugeint hugeint::operator*(const hugeint &obj)
{
  hugeint temp(currentSize + obj.currentSize); 
  hugeint res;
  register int shift = 0;
  register  short product;
  register short chache = 0;


  for (unsigned int i = 0; i < currentSize; i++)
  {
    temp = 0;
    chache = 0;
    for (unsigned int j = 0; j < obj.currentSize; j++)
    {
      product = chache + number[i]*obj.number[j];


      chache = short (product/10.0);
      product = product - chache*10;


      temp.number[j+shift] = product;
      temp.currentSize++;
    }


    temp.currentSize += shift;
    if (chache)
    {
      temp.number[temp.currentSize] = chache;
      temp.currentSize++;
    }
    shift++;  
    res += temp;  
  }


  if ((!positive && obj.positive) || (positive && !obj.positive))
    res.positive = false;


  return res;
}


hugeint hugeint::operator*(const int b)
{
  hugeint res, temp;
  temp = b;
  res = *this * temp;
  return res;
}


hugeint hugeint::operator-( const hugeint &obj)
{
  hugeint temp;
  temp = *this + -obj;
  return temp;
}


hugeint hugeint:: operator-(const int b)
{
  hugeint res, temp;
  temp = b;
  res = *this - temp;
  return res;
}


hugeint hugeint::operator/(const hugeint &obj)
{


  if (obj.currentSize == 0)
    throw mathErr("division by zero");


  hugeint res, bf;
  res = divMod(obj, bf);


  if ((!positive && obj.positive) || (positive && !obj.positive))
    res.positive = false;


  return res;
}


hugeint hugeint::operator/(const int b)
{
  if (b == 0)
    throw mathErr("division by zero");


  hugeint res,temp;
  temp = b;
  res = *this/temp;


  return res;
}


hugeint hugeint::operator%(const hugeint &obj)
{
  if (obj.currentSize == 0)
    throw mathErr("remainder of division by zero");


  hugeint part;
  divMod(obj, part);


  //çíàê ðåçóëüòàòà
  if (!positive)
    part.positive = false;
  return part;
}


hugeint hugeint::operator%( const int b)
{
  if (b == 0)
    throw mathErr("remainder of division by zero");


  hugeint temp, res;
  temp = b;
  res = *this % temp;
  return res;
}


hugeint hugeint::operator+=(const hugeint &obj)
{
  *this = *this + obj;
  return *this;
}


hugeint hugeint::operator+=(const int b)
{
  *this = *this + b;
  return *this;
}


hugeint hugeint::operator-=(const hugeint &obj)
{
  *this = *this - obj;
  return *this;
}


hugeint hugeint::operator-=(const int b)
{
  *this = *this - b;
  return *this;
}


bool hugeint::operator>(const hugeint &obj)
{ 
  if (positive && !obj.positive)
    return true;


  if (!positive && obj.positive)
    return false;


  if (positive && obj.positive)
  {
    if (currentSize > obj.currentSize)
      return true;
    if (currentSize < obj.currentSize)
      return false;


    for (int i = currentSize-1; i >= 0; i--)
    { 
      if (number[i] > obj.number[i])
        return true;
      else
        if (number[i] < obj.number[i])
          return false;
    } 
  }


  if (!positive && !obj.positive)
  {
    if (currentSize > obj.currentSize)
      return false;
    if (currentSize < obj.currentSize)
      return true;


    for (int i = currentSize-1; i >= 0; i--)
    { 
      if (number[i] > obj.number[i])
        return false;
      else
        if (number[i] < obj.number[i])
          return true;
    }
  }
  return false;
}


bool hugeint::operator>(const int b)
{
  hugeint temp;
  temp = b;


  if (*this > temp)
    return true;


  return false;
}


bool hugeint::operator<(const hugeint &obj)
{
  if (positive && !obj.positive)
    return false;


  if (!positive && obj.positive)
    return true;


  if (positive && obj.positive)
  {
    if (currentSize > obj.currentSize)
      return false;
    if (currentSize < obj.currentSize)
      return true;


    for (int i = currentSize-1; i >= 0; i--)
    { 
      if (number[i] > obj.number[i])
        return false;
      else
        if (number[i] < obj.number[i])
          return true;
    } 
  }


  if (!positive && !obj.positive)
  {
    if (currentSize > obj.currentSize)
      return true;
    if (currentSize < obj.currentSize)
      return false;


    for (int i = currentSize-1; i >= 0; i--)
    { 
      if (number[i] > obj.number[i])
        return true;
      else
        if (number[i] < obj.number[i])
          return false;
    } 
  }
  return false;
}


bool hugeint::operator<(const int b)
{
  hugeint temp;
  temp = b;


  if (*this < temp)
    return true;


  return false;
}


bool hugeint::operator==(const hugeint &obj)
{
  if ((positive && !obj.positive) || (!positive && obj.positive)) 
    return false;


  if (currentSize != obj.currentSize)
    return false;


  for (unsigned int i = 0; i < currentSize; i++)
    if (number[i] != obj.number[i])
      return false;


  return true;
}


bool hugeint::operator==(const int b)
{
  hugeint temp;
  temp = b;


  if (*this == temp)
    return true;


  return false;
}


bool hugeint::operator!=(const hugeint &obj)
{
  if (!(*this == obj))
    return true;
  return false;
}


bool hugeint::operator!=(const int b)
{
  hugeint temp;
  temp = b;


  if (!(*this == temp))
    return true;
  return false;
}


bool hugeint::operator>=(const hugeint &obj)
{
  if (*this > obj || *this == obj)
    return true;
  return false;
}


bool hugeint::operator>=(const int b)
{
  hugeint temp;
  temp = b;


  if (*this > temp || *this == temp)
    return true;
  return false;  
}


bool hugeint::operator<=(const hugeint &obj)
{
  if (*this < obj || *this == obj)
    return true;
  return false;
}


bool hugeint::operator<=(const int b)
{
  hugeint temp;
  temp = b;


  if (*this < temp || *this == temp)
    return true;
  return false;


}


hugeint hugeint::divMod(const hugeint &obj, hugeint &reminder)
{
  hugeint  part;
  hugeint  res(currentSize);
  hugeint temp(obj.currentSize+1);
  register int position = currentSize-1;
  register  int i = 0;
  register unsigned  int j = 0;
  register int count = 0;


  if (obj.currentSize == 0)
    return res;
  if (currentSize == 0)
    return res;


  while (j < obj.currentSize)
  {
    if ( position < 0 ) break;
    temp.number[j] = number[position];
    temp.currentSize++;
    position--;
    j++;
  }
  temp.reflect();
 
  if (temp.isAbsBigger(obj))
  {
    if (position >= 0)
    {
      temp.reflect();
      temp.number[temp.currentSize] = number[position];
      temp.currentSize++;
      position--;
      temp.reflect();
    }
  }
  part = temp;


  
  while (!part.isAbsBigger(obj))
  {
    part = part + -obj;
    count ++;
  }


  res.number[i] = count;
  res.currentSize++;
  i++;


  while (position >= 0)
  {
    temp = 0;
    temp.number[0] = number[position];
    temp.currentSize++;
    position--;
    part.concat(temp);
    temp.removeSpace();
    part.removeSpace();
    temp = part;


    while (temp.isAbsBigger(obj))
    {
      if (position < 0) break;
      temp.reflect();
      temp.number[temp.currentSize] = number[position];
      temp.currentSize++;
      position--;
      temp.reflect();
      res.number[i] = 0;
      res.currentSize++;
      i++;
    }
    temp.removeSpace();
    part = temp;
    count = 0;




    while (!part.isAbsBigger(obj))
    {
      part = part + -obj;
      count ++;
    }


    res.number[i] = count;
    res.currentSize++;
    i++;
  }


  res.reflect();
  res.removeSpace();
  
  reminder = part;
  return res;
}




hugeint operator+(const int a, const hugeint &b)
{
  hugeint res, temp;
  temp = a;
  res = temp + b;
  return res;
}


hugeint operator-(const int a, const hugeint &b)
{
  hugeint res, temp;
  temp = a;
  res =  temp - b;
  return res;
}


hugeint operator*(const int a, const hugeint &b)
{
  hugeint temp, res;
  temp = a;
  res = temp * b;
  return res;
}


hugeint operator/(const int a, const hugeint &b)
{


  if (b.currentSize == 0)
    throw mathErr("division by zero");


  hugeint res,temp;
  temp = a;
  res = temp/b;
  return res;
}


hugeint operator%(const int a, const hugeint &b)
{
  if (b.currentSize == 0)
    throw mathErr("remainder of division by zero.");


  hugeint temp, res;
  temp = a;
  res = temp % b;
  return res;
}


bool operator>(const int a, const hugeint &b)
{
  hugeint temp;
  temp = a;


  if (temp > b)
    return true;


  return false;
}


bool operator<(const int a, const hugeint &b)
{
  hugeint temp;
  temp = a;


  if (temp < b)
    return true;


  return false;
}


bool operator==(const int a, const hugeint &b)
{
  hugeint temp;
  temp = a;


  if (temp == b)
    return true;


  return false;
}


bool operator!=(const int a, const hugeint &b)
{
  hugeint temp;
  temp = a;


  if (!(temp == b))
    return true;
  return false;
}


bool operator>=(const int a, const hugeint &b)
{
  hugeint temp;
  temp = a;


  if (temp > b || temp == b)
    return true;
  return false;
}


bool operator<=(const int a, const hugeint &b)
{
  hugeint temp;
  temp = a;


  if (temp < b || temp == b)
    return true;
  return false; 
}


ostream& operator<<(ostream &out, const hugeint &obj)
{
  if (!obj.positive)
    out << "-";
  for(int i = obj.currentSize-1; i >= 0; i--)
    out << obj.number[i];
  if (obj.currentSize == 0)
    out << 0;
  //out << "\nSize:" << obj.currentSize << endl;
  return out;
}


istream& operator>>(istream &in, hugeint &obj)
{
  char bf;
  obj.positive = true;
  obj.currentSize = 0;
  unsigned  int i = 0;


  while (i < obj.maxSize)
  {
    bf = in.get();


    if (bf == ' ' || bf == '\n' || in.eof() )
      break;


    if (bf == '-')
      obj.positive = false;
    else
    {
      if ( bf == '0' ||  bf == '1' ||  bf == '2' ||  bf == '3' ||  bf == '4' ||
        bf == '5' ||  bf == '6' ||  bf == '7' ||  bf == '8' ||  bf == '9' )
      {
        stringstream mystream;
        mystream << bf;
        mystream >> obj.number[i];
        obj.currentSize++;
        i++;
      }
      else
        throw mathErr("input data format is incorrect");
    }
  } 


  obj.reflect();
  obj.removeSpace();
  return in;
}


void hugeint::reflect()
{
  if (currentSize > 1)
  {
    int j = 0;
    short *tmp = new short[currentSize];


    for (unsigned int i = 0; i < currentSize; i++)
      tmp[i] = number[i];


    for (int i = currentSize-1; i >= 0; i--)
    {
      number[j] = tmp[i];
      j++;
    }
    delete [] tmp;
  }
}




void hugeint::removeSpace()
{
  unsigned int deletePos = currentSize;
  for (unsigned int i = 0; i <  currentSize; i++)
  {
    if (number[i] == 0)
    {
      if (deletePos == currentSize)
        deletePos = i;
    }
    else
      deletePos = currentSize;
  }
  currentSize = deletePos;
}


void hugeint:: concat(const hugeint &obj)
{
  int j = currentSize;
  reflect();
  for (int i = obj.currentSize-1; i >=0; i--)
  {
    number[j] = obj.number[i];
    currentSize++;
    j++;
  }
  reflect();
}


bool hugeint::isAbsBigger(const hugeint &obj)
{
  if (obj.currentSize > currentSize)
    return true;
  else
    if (obj.currentSize < currentSize)
      return false;


  for (int i = currentSize-1; i >= 0; i--)
  {
    if (obj.number[i] > number[i])
      return true;
    else
      if (obj.number[i] < number[i])
        return false;
  }
  return false;
}


bool hugeint::even()
{
  short element = number[0];


  if (element & 1)
    return false;


  return true;
}




void hugeint::random(unsigned int length)
{
  if (length <= maxSize)
  { 
    for (unsigned int i = 0; i < length; i++)
      (i != length-1)?(number[i] = rand()%10):(number[i] = rand()%9+1);   


    currentSize = length;
    positive = true;
  }
  else
    throw mathErr("specified size exceeds the maximum capacity of the object");
}


hugeint operator-(const hugeint &obj)
{
  hugeint temp(obj);
  temp.positive = !temp.positive;
  return temp;
}
