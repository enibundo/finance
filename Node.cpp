#include <iostream>
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include "Node.h"

using namespace std;

Node::Node(int ttotalTime, Node* tparent, double coef) { 
  totalTime = ttotalTime;
  parent = tparent;
  time = tparent->time+1;
  actionValue = tparent->actionValue * coef;
  
  left = NULL;
  right = NULL;
  
}

Node::Node(){
  actionValue = 0;
  optionValue = 0;
  time = 0;
  left = NULL;
  right = NULL;
  parent = NULL;
}

Node::Node(double tactionValue, double toptionValue, double ttime) { 
  actionValue = tactionValue;
  optionValue = toptionValue;
  time = ttime;

  left = NULL;
  right = NULL;
  parent = NULL;
}

void Node::print() { 
  cout << "[A:" << actionValue << "; O:"<< optionValue << "; t:"<<time<<"]";
  
  if (left != NULL) { 
    left->print();
  }  
  
  if (right != NULL) { 
    right->print();
  }  
  
  cout << endl;
}

void Node::calculatePayOff(OptionType optionType, CallPut callOrPut, double dt, double k, double r, double p) { 
  
  /** 
   * if final node than we calculate the pay off
   * the algorithm is the same in case of european
   * or american options
   */
  if (left == NULL && right == NULL) { 
    if (callOrPut == Call) { 
      optionValue = max(actionValue - k, (double)0);
    } else if (callOrPut == Put) { 
      optionValue = max(k - actionValue, (double)0);
    }
  } else {
    /**
     * otherwise, we recursively call the 
     * payoff calculation
     */
    left->calculatePayOff(optionType, callOrPut, dt, k, r, p);
    right->calculatePayOff(optionType, callOrPut, dt, k, r, p);    
    
    double tempOptionValue = exp(-1*r*dt) * (p * left->optionValue + (1-p)*right->optionValue);

    if (optionType = American) { 
      if (callOrPut == Call){
	tempOptionValue = max(tempOptionValue, actionValue - k);
      } else if (callOrPut == Put) {
	tempOptionValue = max(tempOptionValue, k - actionValue);
      }
    }
    
    optionValue = tempOptionValue;
  }
}
