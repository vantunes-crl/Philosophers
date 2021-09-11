#include "philo.h"

int main()
{
    printf("%ld\n", chronometer());
    for (int i = 0; i < 0xFFFFFF; i++);
    printf("%ld\n", chronometer());
    return 0;
}

/* eating sleeping thinking*/