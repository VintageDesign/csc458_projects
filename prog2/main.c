#include <stdio.h>

#include "bank.h"
#include "customer.h"


int main(int argc, char * argv[])
{
    if(argc - 1 != NUMBER_OF_RESOURCES)
    {
        printf("Bankers Algorithm requires %d resources.\nExiting...\n"
                , NUMBER_OF_RESOURCES);
        return -1;
    }

}
