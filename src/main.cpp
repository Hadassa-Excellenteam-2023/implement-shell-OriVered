#include <iostream>
#include <exception>

using std::cout; 
using std::endl;

using std::exception;

int main()
{

	{
		try
		{

		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
	}


	}

	return 0;
}