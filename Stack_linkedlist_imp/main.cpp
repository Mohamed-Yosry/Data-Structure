#include <iostream>

using namespace std;


class Stack
{
    struct Node
    {
        int data;
        Node*next;
    };
    Node*top=NULL;
public:


    void push(int val)
    {
        Node*newnode=new Node;
        newnode->data=val;
        if(isEmpty())
            newnode->next=NULL;
        else
            newnode->next=top;
        top=newnode;
    }

    void pop()
    {
        if(isEmpty())
            return;
        Node*temp=top;
        top=top->next;
        delete temp;
    }

    int Top()
    {
        if(isEmpty())
            return -1;
        else
            return top->data;
    }

    bool isEmpty()
    {
        if(top==NULL)
            return true;
        else
            return false;
    }
};

int main()
{
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    while(!s.isEmpty())
    {
        cout<<s.Top()<<endl;
        s.pop();
    }
    return 0;
}
