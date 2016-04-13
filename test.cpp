#include "Option.h"
#include <iostream>

using namespace std;

int main() {
	Option o;
	Option o2(0.2, 0.2, 0.2, 2, 0.2, 0.2, 1);

	cout << "Le prix est : " << o2.Price() << endl;
	return 0;
}