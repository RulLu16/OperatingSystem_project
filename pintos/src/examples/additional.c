#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>

int main(int argc, char** argv){
    printf("%d ", fibonacci(atoi(argv[0])));
    printf("%d\n", max_of_four_int(atoi(argv[0]), atoi(argv[1]), \
                                   atoi(argv[2]), atoi(argv[3])));
    return EXIT_SUCCESS; 
}
