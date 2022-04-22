#include <iostream>

using namespace std;

struct Node;
struct suffixtrieNode;


struct Node{
    suffixtrieNode* data;
    Node *next;
};

class linkedList
{
    Node* head=NULL;
    int siz=0;
public:

    void insertInList(suffixtrieNode* val)
    {
        Node* newnode=new Node;
        newnode->data=val;
        newnode->next=NULL;
        if(head==NULL)
        {
            head=newnode;
        }
        else
        {
            Node*current=head;
            while(current->next!=NULL)
                current=current->next;
            current->next=newnode;
        }
        siz++;
    }

    int Size(){return siz;}
    Node *getHead(){return head;}

};


struct suffixtrieNode{
    char value;
    linkedList child;
    int ID=-1;
};

class SuffixTrie {
    int treiCharSize=0;
    char *trieChar;
    int id=0;
    suffixtrieNode *root=new suffixtrieNode;
public:
    SuffixTrie(char a[])
    {
        while(a[treiCharSize]!='$')
            treiCharSize++;
        treiCharSize++;
        trieChar=new char[treiCharSize];
        for(int i=0;i<treiCharSize;i++)
            trieChar[i]=a[i];


        for(int i=0;i<treiCharSize;i++)
           insertSuffix(i);

    }

    void insertSuffix(int start)
    {
        if(root->child.Size()==0)
        {
            insertNewRootChild(start);
        }
        else
        {
            bool cond=false;
            bool cond2=false,cond3=false;
            Node *li=root->child.getHead();
            for(int i=0;i<root->child.Size();i++)
            {
                if(li->data->value==trieChar[start])
                {
                    Node *li2=li->data->child.getHead();
                    for(int i=start+1;i<treiCharSize;i++)
                    {

                        if(li2->data->value!=trieChar[i] && trieChar[i]!='$')
                        {
                            cond=false;
                            break;
                        }

                        else if(li2->data->value!=trieChar[i] && trieChar[i]=='$')
                        {
                            suffixtrieNode *childNode=new suffixtrieNode;
                            childNode->value=trieChar[i];
                            childNode->ID=id;
                            id++;
                            li2->data->child.insertInList(childNode);
                            i=treiCharSize;
                            cond=true;
                            break;
                        }

                        li2=li2->next;
                    }
                }
                if(cond)
                    break;
                li=li->next;

            }
            if(!cond)
                insertNewRootChild(start);

        }

    }

    void insertNewRootChild(int start)
    {
        suffixtrieNode *newnode=new suffixtrieNode;
        newnode->value=trieChar[start];
        root->child.insertInList(newnode);

        for(int i=start+1;i<treiCharSize;i++)
        {
            suffixtrieNode *childNode=new suffixtrieNode;
            childNode->value=trieChar[i];
            if(childNode->value=='$')
            {
                childNode->ID=id;
                id++;
            }
            newnode->child.insertInList(childNode);
        }

    }

    void Search(char a[])
    {
        int i=0;
        int tSize=0;
        while(a[tSize]!='\0')
            tSize++;

        char *t=new char [tSize];
        for(int i=0;i<tSize;i++)
            t[i]=a[i];

        Node *currunt=root->child.getHead();
        int counter=0;
        for(int i=0;i<root->child.Size();i++)
        {
            if(currunt->data->value==t[counter])
            {
                counter++;
                Node *curruntChild=currunt->data->child.getHead();
                for(int x=0;x<currunt->data->child.Size();x++)
                {
                    if(counter<tSize)
                    {
                        if(curruntChild->data->value==t[counter])
                            counter++;
                        else
                            break;
                    }
                    else
                    {
                       if(curruntChild->data->child.Size()==1)
                        {
                            Node *curruntChild2=curruntChild->data->child.getHead();
                            cout<<curruntChild2->data->ID<<"     ";
                        }
                        else if(curruntChild->data->value=='$')
                            cout<<curruntChild->data->ID<<"     ";
                    }
                    curruntChild=curruntChild->next;

                }
            }
            counter=0;
            currunt=currunt->next;
        }
        cout<<endl;
    }

};

int main()
{
    // Construct a suffix trie containing all suffixes of "bananabanaba$"

    //            0123456789012
    SuffixTrie t("bananabanaba$");

    t.Search("ana"); // Prints: 1 3 7
    t.Search("naba"); // Prints: 4 8

    return 0;
}


