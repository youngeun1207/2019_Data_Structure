#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define INT_MAX 2147438647

int Zero();
bool IsZero(int n);
bool Equal(int x, int y);
int Successor(int n);
int Add(int x, int y);
int Subtract(int x, int y);

int main(int argc, char** args)
{
    int x = atoi(args[1]);
    int y = atoi(args[2]);

    printf("Is %d zero? %s\n",x,IsZero(x) ? "True": "False");
    printf("Is %d zero? %s\n",y,IsZero(y) ? "True": "False");
    printf("Does %d equal %d? %s\n", x,y,Equal(x,y)? "True" : "False");
    printf("%d's next number is %d\n",x,Successor(x));
    printf("%d's next number is %d\n",y,Successor(y));
    printf("%d + %d = %d\n", x, y, Add(x,y));
    printf("%d - %d = %d\n", x, y, Subtract(x,y));

    return 0;
}

bool IsZero(int n){
    if(n == 0){
        return true;
    }
    else{
        return false;
    }
}

bool Equal(int x, int y){
    if( x == y ){
        return true;
    }
    else{
        return false;
    }
}

int Successor(int n){
    if(n < INT_MAX - 1){
        return n+1;
    }
    else{
        return n;
    }
}

int Add(int x, int y){
    if(x < INT_MAX - y){
        return (x+y);
    }
    else{
        return INT_MAX;
    }
}

int Subtract(int x, int y){
    if(x > y){
        return (x-y);
    }    
    else{
        return 0;
    }
}

    
