#include <iostream>
#include <cstdlib>
#include <cstring>

#include "Driver.hpp"

int main(const int argc, const char **argv)
{
    /** check for the right # of arguments **/
    //if (argc == 2)
    {
        C0::Driver driver;
        //driver.parse(argv[1]);
        driver.parse("prueba2");
    }
    /*else
    {
         exit with failure condition 
        //return (EXIT_FAILURE);
    //}*/
    return (EXIT_SUCCESS);
}
