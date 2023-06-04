#include <iostream>
#include <exception>
#include "shell.h"

using std::cout; 
using std::endl;

using std::exception;

int main()
{

	{
		try
		{
			Shell shell;
			shell.run();

			return 0;
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
	}

	return 0;
}