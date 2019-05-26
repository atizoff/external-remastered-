#include <fstream>
#include "hugeint.h"


struct cryptkey
{
  hugeint a;
  hugeint b;


  bool loadFromFile(const char *filename)
  {
    hugeint temp(800);
    
    ifstream in (filename);
    if (in.good())
    {  
      in >> temp;
      a = temp;
      in >> temp;
      b = temp;
      in.close();
      return true;
    }
    return false;
  }


  bool saveToFile(const char *filename)
  {
    ofstream out (filename);
    if (out.good()) 
    {
      out << a << endl;
      out << b << endl;
      out.close();
      return true;
    }
    return false;
  }
};
