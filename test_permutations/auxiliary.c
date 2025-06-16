/* Some utility functions (not part of the algorithm) */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"

/* Function to return the maximum of two variables */
int maximum (int a, int b)
{
    if (a>b)
    {
        return(a);
    }
    return (b);
}

/* Function to return the minimum of two variables */
int minimum (int a, int b)
{
    if (a<b)
    {
        return (a);
    }
    return (b);
}


