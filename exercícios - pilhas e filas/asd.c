#include <stdio.h>
#include <stdlib.h>

void func(int c, int p, int u){
    if(c <= u){
        int aux = c / 10;
        int dig_direita = c % 10;

        if(dig_direita != 0 && c%aux == 0){
            printf("%d\n", c);
        }
        func(c+1, p, u);
    }
}

int main(){
    int p, u;
    scanf("%d %d", &p, &u);
    func(p, p, u);
}