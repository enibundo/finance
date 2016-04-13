#include "BinomialTree.h"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

BinomialTree::BinomialTree(){
  steps = 0;
}

BinomialTree::BinomialTree(double S0, int tstep, double u, double d)  { 
  
  rootNode.actionValue = S0;
  
  vector<Node*> nodes(tstep+1);
  int i,j;  
  
  steps = tstep;
  nodes[0] = &rootNode;
  
  for (i=0; i < tstep; i++) {    
    for (j=0; j<=i; j++) {
      if (j==0) { 
	nodes[j]->left = new Node(tstep, nodes[j], u);
	nodes[j]->right = new Node(tstep, nodes[j], d);
      } else { 
	nodes[j]->left = nodes[j-1]->right;
	nodes[j]->right = new Node(tstep, nodes[j], d);
      }
    }
    
    for (j=0; j < i; j++) {
      nodes[j] = nodes[j]->left;
    }
    
    nodes[i+1] = nodes[i]->right;
    nodes[i] = nodes[i]->left;
  }
}

void BinomialTree::print() { 
  rootNode.print();
}

/** 
 * callOrPut:
 * 0 -> call
 * 1 -> put
 */
double BinomialTree::Price(OptionType optionType, CallPut callOrPut, double dt, double K, double r, double p){
  // we calculate the price at the rootNode recursively
  rootNode.calculatePayOff(optionType, callOrPut, dt, K, r, p);
  
  // and return it.
  return rootNode.optionValue;
}
