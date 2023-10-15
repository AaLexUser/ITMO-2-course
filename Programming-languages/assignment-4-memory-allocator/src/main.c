//main.c file that starts tests
#include "tests.h"
#include <printf.h>
#include <stdio.h>

int main(void){
    printf("Starting tests\n");
    if(!test1()){
        printf("Test 1 failed\n");
        return 1;
    }
    if(!test2()){
        printf("Test 2 failed\n");
        return 1;
    }
    if(!test3()){
        printf("Test 3 failed\n");
        return 1;
    }
    if(!test4()){
        printf("Test 4 failed\n");
        return 1;
    }
    if(!test5()){
        printf("Test 5 failed\n");
        return 1;
    }
    printf("All tests passed\n");
    return 0;

}