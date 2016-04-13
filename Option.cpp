#include <iostream>
#include <stdlib.h>

// for PI
#define _USE_MATH_DEFINES
#include <math.h>

#include "Option.h"

using namespace std;

/*********************************
 * td : down percentage
 * tu : up percentage
 * tr : risk 
 * dt : time step
 * tT : total steps
 * tS0 : initial price
 * tK : strike price
 * callPut : call/put
 */
Option::Option(double td,			\
				 double tu,			\
				 double tr,			\
				 double tdt,			\
				 double tS0,			\
				 double tK,			\
				 OptionType europeanAmerican,     \
				 CallPut callPut) { 
	
	// variables initialization
	d          = td;
	u          = tu;
	r          = tr;
	dt         = tdt;
	S0         = tS0;
	K          = tK;
	callOrPut  = callPut;
	optionType = europeanAmerican;
	
	// risk free rate
	p = (exp(r*dt) - d ) / (u - d);

}

double Option::PriceMC(int iter) { 
  double payoff=0;
  double v = log(u)/sqrt(dt);
  double Sadj = S0 * exp(dt*(r-0.5*v*v));

  int i;

  for (i=1; i <= iter; i++);
  {
    double x = GBM();
    double ST = Sadj * exp(sqrt(v*v*dt)*x);
    if(callOrPut == Call) {
      payoff += (max(0.0, ST - K));
    }
    else if(callOrPut == Put) 
      {
	payoff += (max(0.0, K - ST));
      } 
  }
  return ( payoff ) /iter;
}

double Option::PriceBS(){
  // we find the volatility from the u
  // http://en.wikipedia.org/wiki/Binomial_options_pricing_model
  //
  double v = log(u)/sqrt(dt);
  
  double d1, d2;
  
  d1 = (log(S0/K) + (r + v * v / 2) * dt) / (v * sqrt(dt));
  d2 = d1 - v * sqrt(dt);
  
  if(callOrPut == Call) {
    return max(0.0, S0 * CND(d1) - K * exp(-r * dt) * CND(d2));
  } 
  else if(callOrPut == Put) 
    {
      return max(0.0, K * exp(-r * dt) * CND(-d2) - S0 * CND(-d1));
    }
}

double Option::Price(int T) { 
	// tree construction
	bTree = BinomialTree(S0, T, u, d);  
	return bTree.Price(optionType, callOrPut, dt, K, r, p);
}



/************ private methods ******************/
double Option::CND(double x)
{
	double Pi = M_PI;
	double L, K, w ;

	double const a1 = 0.31938153, a2 = -0.356563782, a3 = 1.781477937;
	double const a4 = -1.821255978, a5 = 1.330274429;

	L = fabs(x);
	K = 1.0 / (1.0 + 0.2316419 * L);
	w = 1.0 - 1.0 / sqrt(2 * Pi) * exp(-L *L / 2) * (a1 * K + a2 * K *K + a3 * pow(K,3) + a4 * pow(K,4) + a5 * pow(K,5));

	if (x < 0 ){
		w = 1.0 - w;
	}
	return w;
}

double Option::GBM() { 
	double x  = 0.0;
	double y  = 0.0;
	double eu = 0.0;

	do{
		x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
		y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
		eu = x*x + y*y;
	} while(eu >= 1.0);

	return x * sqrt(-2 * log(eu)/eu);
}
