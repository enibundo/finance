#include <math.h>

/**
 * Two different Option Types 
 */
enum OptionType { American, European };

/**
 * we have two Option Types
 */
enum CallPut{ Put, Call };

/**
 * we can price according to one of these methods
 */
enum PriceMethods { Binomial, BlackAndScholes, MonteCarlo };