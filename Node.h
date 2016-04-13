#include "Global.h"

class Node {
 private:
  int totalTime;
 public:
  // == constructors ==
  Node();
  Node(int ttotalTime, Node* parent, double coef);
  Node(double tactionValue, double toptionValue, double ttime);
  
  // == data ==
  double actionValue;
  double optionValue;					
  double time;
  int id;
  
  // == links ==
  Node* left;
  Node* right;
  Node* parent;

  // == methods ==
  void print();
  void calculatePayOff(OptionType optionType, CallPut callOrPut, double dt, double k, double r, double p);
};
