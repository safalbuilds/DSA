#include<iostream>
using std::cout, std::cin, std::endl;

template <class T, int MAX>
class Stack {
    private:
    int TOP;
    T data[MAX];

    public:
    bool IsEmpty(){
        return TOP == -1;
    }
    bool IsFull(){
        return TOP == MAX-1;
    }
    void PUSH(T element){
        if(IsFull()){
            cout << "Stack Overflow" << endl;
        }
        else{
            data[++TOP] = element;
        }
    }
    T POP(){
        if(IsEmpty()){
            cout << "Stack Underflow" << endl;
            return T();
        }
        else {
            return data[TOP--];
        }
    }
    Stack() {
        TOP = -1;
    }
};

int main() {
    Stack<int, 5> s;
    int choice;
    int element;

    do {
        cout <<"\n--------------\n";
        cout <<"Choice? \n";
        cout <<"1. PUSH \n";
        cout <<"2. POP \n";
        cout <<"3. Exit \n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout <<"Element? \n";
            cin >> element;
            s.PUSH(element);
            break;
        
        case 2:
            element = s.POP();
            cout <<element <<" is POPPED";
            break;

        case 3:
            cout << "Exiting...";
            break;
        
        default:
            cout <<"Enter different number.";
            break;
            
        }
    } while(choice!= 3);
}