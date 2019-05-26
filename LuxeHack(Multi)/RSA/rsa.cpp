#include "rsa.h"


//key length (decimal digits)
#define KEYLENGTH 80


//generating keys
void rsa::genKeys(cryptkey &pbkey, cryptkey &prkey)
{
  hugeint p(KEYLENGTH/2);
  hugeint q(KEYLENGTH/2);
  hugeint d(KEYLENGTH-3);
  hugeint n, eiler, diviser,e;


  //getting 2 prime numbers
  while (!p.prime())
    p.random(KEYLENGTH/2);


  while (!q.prime())
    q.random(KEYLENGTH/2);


  n = p*q;


  //Euler's function
  eiler = (p - 1) * (q - 1);


  //getting private and public exponents
  do
  {
    do
    {
      d.random(KEYLENGTH-3);
      diviser = d. getMaxDiviser(eiler);
    }
    while ( diviser != 1);


    extEuclid(eiler, d, e);
  }
  while (e < 0);


  //keys
  pbkey.a = d;
  pbkey.b = n;
  prkey.a = e;
  prkey.b = n;


  /*
  vector <char> a = d.toBinary();
  hugeint message = 153;
  hugeint crypt;
  hugeint decrypt;


  crypt = message.calcPowMod(a,n);


  a = e.toBinary();
  decrypt = crypt.calcPowMod(a,n);


  if (message == decrypt)
  cout << "Test passed\n";
  else
  cout << "Test failed\n";
  */
}


//extended Euclidean algorithm
// y - private exponent
void rsa::extEuclid (hugeint  a, hugeint  b, hugeint &y)
{
  hugeint r, q, a11, a12, a21, a22;
  hugeint A11, A12, A21 ,A22;
  a11 = 1, a12 = 0, a21 = 0, a22 = 1;


  while ( b > 0)
  {
    r = a%b;
    q = a/b;
    if (r == 0)
      break;


    A11 = a12;
    A12 = a11+a12*-q;
    A21 = a22;
    A22 = a21+a22*-q;


    a11 = A11, a12 = A12, a21 = A21, a22 = A22;


    a = b;
    b = r;
  }
  y = a22;
}


//encrypt a string (a,b - values from key)
hugeint rsa::encrypt(string &data, const vector<char>  &a, const hugeint &b)
{
  hugeint block;
  block = 1;
  
  if (data.length() > (KEYLENGTH-4)/3)
    throw rsaErr("size of the input string is exceeds size limit");


  //input string > hugeint
  //the first digit = 1, next 3 digits = code 
  for (unsigned int i = 0; i < data.length(); i++)
  {
    hugeint buff;
    buff = int(data[i]);


    //cp1251 support
    if (buff < 0)
      buff = 256+buff;


    block = block*int(pow(10.0, 3 - buff.size()));
    block.concat(buff);
  }
  //encryption
  return block.calcPowMod(a, b);
}


//decrypt a string (a,b - values from key)
string rsa::decrypt(hugeint &data, const vector<char>  &a, const hugeint &b)
{
  stringstream mystream;
  hugeint temp, block;
  int bf;
  string buffer, res;


  
  block = data.calcPowMod(a, b);


  //hugeint > string
  while (block.size() > 3)
  {
    temp = block;
    block = block/1000;


    mystream.clear();
    mystream << temp - block*1000;
    mystream >> bf;


    //cp1251 support
    if (bf > 127)
      bf =  bf - 256;


    buffer += char(bf);
  }


  if (block != 1)
    throw rsaErr("input data corrupted");


  for (int i = (int)buffer.length() - 1; i >= 0; i-- )
    res += buffer[i];


  return res;
}


//encrypt the text file in, result to the text file out
void rsa::encryptTxtFile(const char *in, const char *out, cryptkey &key)
{
  string buff;
  vector <char> a = key.a.toBinary();


  ifstream input (in);
  if (!input.good())
    throw rsaErr("unable to open input file");


  ofstream output(out);
  if (!output.good())
    throw rsaErr("unable to create output file");


  while (!input.eof())
  {
    buff.clear();


    for (int i = 0; i < (KEYLENGTH-4)/3; i++)
    {
      char bf = input.get();
      if (input.eof())
        break;
      buff += bf;
    }


    if (!buff.empty())
      output <<  encrypt(buff, a, key.b) << " ";
  }


  input.close();
  output.close();
}


//decrypt the text file in, result to the text file out
void rsa::decryptTxtFile(const char *in, const char *out, cryptkey &key)
{
  vector <char> a = key.a.toBinary();
  hugeint buff(KEYLENGTH*2);


  ifstream input (in);
  if (!input.good())
    throw rsaErr("unable to open input file");


  ofstream output (out);
  if (!output.good())
    throw rsaErr("unable to create output file");


  for (;;)
  {
    input >> buff;
    if (input.eof())
      break;
    output << decrypt(buff, a, key.b);
  }


  input.close();
  output.close();
}