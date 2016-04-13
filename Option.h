#include "BinomialTree.h"

class Option
{
 private:
  double p;
  double CND(double x); 
  double GBM(); // gausian box muller
 public:
  double  d;
  double  u;
  double  r;
  double dt;
  double  S0;
  double  K;
  CallPut callOrPut;
  OptionType optionType;

  BinomialTree bTree;
  
  Option(double td, double tu, double tr, double dt, double tS0, double tK, OptionType optionType, CallPut callPut);
  
  double Price(int T);
  double PriceBS();
  double PriceMC(int iter);
};
