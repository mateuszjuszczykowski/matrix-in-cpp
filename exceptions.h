#include <iostream>
#include <exception>

using namespace std;

class InvalidColumnsSize : public invalid_argument {
  public:
	InvalidColumnsSize()
		: invalid_argument("Invalid columns size.")
	{}
};

class InvalidRowsSize : public invalid_argument {
	public:
		InvalidRowsSize()
			: invalid_argument("Invalid rows size.")
		{}
};

class WrongMatricesSizes : public invalid_argument {
	public:
		WrongMatricesSizes()
			: invalid_argument("Wrong matrices sizes.")
		{}
};