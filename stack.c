#include<stdio.h>
#define MAX 5
#define True 1
#define False 0

struct Stack {
    int TOP;
    int data [MAX];
};

int IsFull(struct Stack* s) {
    if (s->TOP == MAX-1) {
        return True;
    }
    else 
        return False;
}

int IsEmpty(struct Stack* s) {
    if (s->TOP == -1) {
        return True;
    }
    else 
        return False;
}

void PUSH(struct Stack* s, int element) {
    if(IsFull(s)) {
        printf("Stack Overflowed");
    }
    else {
        s->data[++s->TOP] = element;
        printf("%d PUSHED", element);
    }
}
int POP(struct Stack* s) {
    if(IsEmpty(s)){
        printf("Stack Underflowed");
    }
    else {
        int element = s->data[s->TOP];
        s->TOP--;
        return element;
    }
}

int main() {
    struct Stack s = {-1};
    int choice, element;
    do {
        printf("\n--------------\n");
        printf("Choice? \n");
        printf("1. PUSH \n");
        printf("2. POP \n");
        printf("3. Exit \n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Element? \n");
            scanf("%d", &element);
            PUSH(&s, element);
            break;
        
        case 2:
            element = POP(&s);
            printf("%d is POPPED", element);
            break;
        
        default:
            printf("Enter different number.");
            break;
        }
    } while(choice != 3);

}