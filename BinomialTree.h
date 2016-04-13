#include "Node.h"

class BinomialTree{
 private:
  Node rootNode;
 public:
  int steps;
  BinomialTree();
  BinomialTree(double S0, int tstep, double u, double d);
  void print();
  double Price(OptionType optionType, CallPut callOrPut, double dt, double k, double r, double p);
};
