#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <exception>
using namespace std;

template<class T>
class MaxPalindromeGenerator{
public:
  MaxPalindromeGenerator() : fNumberOfDigits(5), 
                           fPrimeNumbersVector(0),
                           fMaxPalindrome(0),
                           fFirstPrime(0),
                           fSecondPrime(0)
                           { 
                           }
  ~MaxPalindromeGenerator() {}
  void SetNumberOfDigits(const int& numberOfDigits) {fNumberOfDigits = numberOfDigits;}
  const T& GetNumberOfDigits() const {return fNumberOfDigits;}
  const T& GetMaxPalindromeFromProductOfTwoPrimes() const {return fMaxPalindrome;}
  const T& GetFirstPrime() const {return fFirstPrime;}
  const T& GetSecondPrime() const {return fSecondPrime;}
  void GeneratePrimes();
  void MaxPalindromeCalculationFromProductOfTwoPrimes();
private:
  int fNumberOfDigits;
  std::vector<T> fPrimeNumbersVector;
  T fMaxPalindrome;
  T fFirstPrime;
  T fSecondPrime;
};

template<class T>
void MaxPalindromeGenerator<T>::GeneratePrimes()
{
  if(fNumberOfDigits < 1)
    throw "Check input number of digits! It should be non less than 1.";
  T upperBound = 0;
  for (int i=1; i<=fNumberOfDigits; i++)
  {
    upperBound *= 10;
    upperBound += 9;
  }
  T lowerBound = 1 + upperBound/10;
  
  fPrimeNumbersVector.reserve(upperBound-lowerBound);
  if(fNumberOfDigits == 1)
  {
    fPrimeNumbersVector.push_back(2);
    fPrimeNumbersVector.push_back(3);
  }
    for (int numb1=lowerBound; numb1<upperBound; ++numb1) 
        for (int numb2=2; numb2*numb2<=numb1; numb2++)
        {
            if (numb1 % numb2 == 0) 
                break;
            else if (numb2+1 > sqrt(numb1)) {
                fPrimeNumbersVector.push_back(numb1);
            }
        }
}

template<class T>
void MaxPalindromeGenerator<T>::MaxPalindromeCalculationFromProductOfTwoPrimes()
{
  T mult = 0;
    for(T pr1 = fPrimeNumbersVector.size()-1; pr1 >= 0 ; --pr1)
      for(T pr2 = pr1; pr2 >= 0 ; --pr2)
      {
        mult = fPrimeNumbersVector[pr1]*fPrimeNumbersVector[pr2];
        if (mult < fMaxPalindrome)
          continue;
        T number = mult;
        T reverse = 0;
        while (number != 0)
        {
          reverse = reverse * 10 + number % 10;
          number /= 10;
        }
 
        if (mult == reverse && mult > fMaxPalindrome)
        {
          fMaxPalindrome = mult;
          fFirstPrime = fPrimeNumbersVector[pr1];
          fSecondPrime = fPrimeNumbersVector[pr2];
        }
      }
}

template<class T>
void printResults(MaxPalindromeGenerator<T>* gen)
{
  cout << "****************************Results*******************************" << endl;
  cout <<
    "Maximum palindrome made of two 5-digits prime numbers equals: " << gen->GetMaxPalindromeFromProductOfTwoPrimes() << endl << //999949999
    "First prime number equals:  " << gen->GetFirstPrime() << endl << // 33211
    "Second prime number equals: " << gen->GetSecondPrime() << endl; // 30109
  cout << "******************************************************************" << endl;
}


int main () 
{   
    clock_t tStart = clock();
    MaxPalindromeGenerator<long>* gen = new MaxPalindromeGenerator<long>();
    gen->SetNumberOfDigits(5);
    gen->GeneratePrimes();
    gen->MaxPalindromeCalculationFromProductOfTwoPrimes();
    printResults(gen);
    delete gen;
    cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << "s " << endl;
    return 0;
}