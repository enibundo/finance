#include "Option.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() { 
  string input;

  // initial price
  double S0; //= 4691;
  cout << "Enter the initial Price (EX: 4961.5):" << endl;
  cin >> S0;

  // strike price
  double K; // = 4300;
  cout << "Enter the strike Price (EX: 4300)" << endl;
  cin >> K;

  // down
  double d; // = 0.998;
  cout << "Enter the down percentage (EX: 0.9):" << endl;
  cin >> d;

  // up
  double u; // = 1/d;
  cout << "Enter the up percentage (EX: 0.1):" << endl;
  cin >> u;

  // risk
  double r;//  = 0.002;
  cout << "Enter the risk (EX:0.002)" << endl;
  cin >> r;

  // option time (0.5 = 6 months)
  double dt; // = 0.05833;
  cout << "Enter the Maturity in years (EX:0.5 for 6 months)"<<endl;
  cin >> dt;

  // number of steps
  int T; //    = 5;
  cout << "Enter the number of steps for the Binomial simulation (EX: 5)" << endl;
  cin >> T;

  int MC;
  cout << "Enter the number of steps for the Monte Carlo simulation (EX: 20)" << endl;
  cin >> MC;

  char cp;
  cout << "Enter C- for Call, P- for Put" << endl;
  cin >> cp;
  
  CallPut callPut = Put;
  
  if (cp == 'c' || cp == 'C') { 
    callPut = Call;
  } // else put

  char ae;
  cout << "Enter E- for european, A- for American" << endl;
  cin >> ae;

  OptionType aeOption = European;
  
  if (ae == 'a' || ae=='A') { 
    ae = American;
  }
  
  // option creation
  Option o1 = Option(d, u, r, dt/T, S0, K, aeOption, callPut);
  
  cout << "-----------------------------------------------"<<endl;
  cout << "Option: \t" << ae << " " << cp << endl;
  cout << "Initial Price: \t"<< S0 << endl;
  cout << "Strik Price: \t"<< K << endl;
  cout << "Maturity: \t"<< dt << endl;
  cout << "U/D: \t\t"<<u << "/" << d<< endl;
  cout << "Risk: \t\t"<<r << endl;
  cout << "-----------------------------------------------"<<endl;

  // option pricing
  cout << "(Binomial ["<< T<<" iterations]) The option has a price of : " << o1.Price(T) << endl;
  cout << "(BS) The option has a price of : " << o1.PriceBS() << endl;
  cout << "(MC ["<< MC <<" iterations]) The option has a price of : " << o1.PriceMC(MC) << endl;

  cout << "-----------------------------------------------"<<endl;
  
  //  cout << "--- Tree ---" << endl;
  // o1.bTree.print();
  
  cout << "Press any key to exit..."<<endl;
  getline(cin, input);
  getline(cin, input);
  return 0;
}
