#include<stdio.h>
int main(int argv, char** argc){
    int i;
    for(i = 1; i < 10; i++){
        printf("%d * %d = %2d\n", 2, i, 2 * i);
    }
}
