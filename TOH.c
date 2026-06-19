#include <stdio.h>
int moves = 0;

void TOH(int n, char src, char dest, char temp){
    if(n==1){
        moves++;
        printf("Move %d: Move disc %d from %c to %c.\n", moves, n, src, dest);
    }
    else{
        TOH(n-1, src, temp, dest);
        moves++;
        printf("Move %d: Move disc %d from %c to %c.\n", moves, n, src, dest );
        TOH(n-1, temp, dest, src);
    }
}

int main(){
    TOH(4, 'A', 'C', 'B');
}