#include <iostream>
#include <exception>
#include "shell.h"

using std::cout;
using std::endl;

using std::exception;

/**
 * @brief The entry point of the program.
 *
 * This main function creates an instance of the Shell class and runs it.
 * Any exceptions thrown during the execution of the shell are caught, and the corresponding error message is printed.
 *
 * @return int The exit status of the program.
 */
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
