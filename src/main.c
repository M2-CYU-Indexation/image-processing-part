
#include <stdio.h>

#include "input/input.h"

int main(int argc, char *argv[])
{
    Input input;
    int respRetrieve = retrieveInput(argc, argv, &input);
    if (respRetrieve != 0)
    {
        printf("Error while retrieving the inputs : error code %d", respRetrieve);
        return 1;
    }

    

    return 0;
}
