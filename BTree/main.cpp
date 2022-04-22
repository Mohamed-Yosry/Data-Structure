#include <iostream>

using namespace std;

template<class t>
struct BTreeNode
{
    t *key;
    BTreeNode <t>  **children;
    BTreeNode <t>  *parent;
    int curruntKeynum=0;
    int curruntChildrennum=0;
    int maxKey;
    int maxChildren;
    bool isLeaf;

};

template<class t,int maxNum>
class BTree
{
private:
    BTreeNode<t> *root=NULL;


public:
    BTreeNode<t>* createNode(BTreeNode<t> *bnode)
    {
        bnode=new BTreeNode<t>;
        bnode->key=new t[maxNum];
        bnode->children=new BTreeNode<t>*[maxNum+1];
        bnode->maxChildren=maxNum;
        bnode->maxKey=maxNum;
        bnode->parent=NULL;

        return bnode;
    }

    void Insert(t value)
    {
        BTreeNode<t>*node;
        node=createNode(node);
        if(root==NULL)
        {
            node->key[0]=value;
            node->isLeaf=true;
            node->curruntKeynum++;
            root=node;
            root->parent=NULL;
        }
        else
        {
            BTreeNode<t>*currunt=root;
            BTreeNode<t>*curuntParent=createNode(curuntParent);

            currunt=findLeaf(root,value);
            curuntParent=currunt->parent;


            if(currunt->curruntKeynum<maxNum)
            {

                for(int i=0;i<=currunt->curruntKeynum;i++)
                {
                    if(currunt->key[i]>value)
                    {
                        for(int x=currunt->curruntKeynum;x>=i;x--)
                        {
                            currunt->parent=curuntParent;
                            currunt->key[x]=currunt->key[x-1];
                        }
                        currunt->key[i]=value;
                        currunt->isLeaf=true;
                        break;
                    }
                    else if(currunt->key[i]<value && i==(currunt->curruntKeynum-1))
                    {
                        currunt->key[i+1]=value;
                        currunt->parent=curuntParent;
                        currunt->isLeaf=true;
                        break;
                    }
                }
                currunt->curruntKeynum++;
            }
            if(currunt->curruntKeynum==maxNum)
            {
                if(currunt==root)
                {
                    BTreeNode<t>*newnode=createNode(newnode);
                    newnode->children[0]=currunt;
                    newnode->curruntChildrennum++;
                    root=newnode;
                    currunt->parent=newnode;
                    split(currunt);
                }
                else
                {
                    split(currunt);
                }
            }

        }
    }

    BTreeNode<t> *findLeaf(BTreeNode<t> *node, t value)
    {
        BTreeNode<t>*currunt=createNode(currunt);
        currunt=node;
        BTreeNode<t>*curuntParent=createNode(curuntParent);
        if(!currunt->isLeaf)
        {
            for(int i=0;i<currunt->curruntKeynum;i++)
            {
                if(value<currunt->key[i])
                {
                    curuntParent=currunt;
                    if(currunt->curruntChildrennum>0)
                        currunt=findLeaf(currunt->children[i],value);
                    break;
                }
                else if(value>currunt->key[i] && i==(currunt->curruntKeynum-1))
                {
                    curuntParent=currunt;
                    if(currunt->curruntChildrennum==0)
                        break;
                    currunt=currunt->children[i+1];
                }
            }
        }

        return currunt;
    }

    void split(BTreeNode <t>*currunt)
    {
        int mid=(maxNum-1)/2,midChild=maxNum/2;
        t midContent=currunt->key[mid];
        BTreeNode<t>*noderight;
        noderight=createNode(noderight);

        for(int i=mid+1;i<maxNum;i++)
        {
            noderight->key[i-mid-1]=currunt->key[i];
            noderight->parent=currunt->parent;
            noderight->curruntKeynum++;
            currunt->curruntKeynum--;
        }



        if(!currunt->isLeaf || currunt->curruntChildrennum>0)
        {
            for(int i=midChild+1;i<maxNum+1;i++)
            {
                noderight->children[i-midChild-1]=currunt->children[i];
                noderight->curruntChildrennum++;
                currunt->curruntChildrennum--;
            }
            noderight->isLeaf=currunt->isLeaf;
        }


        for(int i=0;i<currunt->parent->curruntChildrennum;i++)
        {
            if(currunt==currunt->parent->children[i])
            {
                for(int x=currunt->parent->curruntChildrennum;x>i;x--)
                {
                    currunt->parent->children[x]=currunt->parent->children[x-1];
                }
                currunt->parent->curruntChildrennum++;
                currunt->parent->children[i+1]=noderight;
                break;
            }
        }

        //put mid in parent

        BTreeNode<t>*Parent=createNode(Parent);
        Parent=currunt->parent;

        if(Parent->curruntKeynum<maxNum)
        {
            for(int i=0;i<=Parent->curruntKeynum;i++)
            {
                if(Parent->key[i]>midContent)
                {
                    for(int x=Parent->curruntKeynum;x>i;x--)
                    {
                        Parent->key[x]=Parent->key[x-1];
                    }
                    Parent->key[i]=midContent;
                    break;
                }
                else if(midContent>Parent->key[i] && i==(Parent->curruntKeynum-1))
                {
                    Parent->key[i+1]=midContent;
                    break;
                }
            }
            if(Parent->curruntKeynum==0)
            {
                Parent->key[0]=midContent;
            }
            Parent->curruntKeynum++;
            currunt->curruntKeynum--;
        }

        if(Parent->curruntKeynum==maxNum)
        {
            if(Parent==root)
            {
                BTreeNode<t>*newnode=createNode(newnode);
                newnode->children[0]=Parent;
                newnode->curruntChildrennum++;
                root=newnode;
                Parent->parent=newnode;
                split(Parent);
            }
            else
            {
                split(Parent);
            }
        }


    }

    void Print()
    {
        string space="  ";
        BTreeNode<t>*newnode=createNode(newnode);
        newnode=root;

        printHelper(root,space,0);
        cout<<"\n";
    }

    void printHelper(BTreeNode<t> * node,string space,int coun)
    {
        for(int x=0;x<coun;x++)
            cout<<space;

        if(!node->isLeaf)
        {
            for(int i=0;i<node->curruntKeynum;i++)
            {

                cout<<node->key[i];
                if(i<node->curruntKeynum-1)
                    cout<<",";
            }
            coun++;
            cout<<"\n";
            for(int i=0;i<node->curruntChildrennum;i++)
                printHelper(node->children[i],space,coun);
        }
        else
        {
            for(int i=0;i<node->curruntKeynum;i++)
            {
                cout<<node->key[i];
                if(i<node->curruntKeynum-1)
                    cout<<",";
            }
            cout<<"\n";
            return;
        }
        return;

    }
};




int main()
{
    // Construct a BTree of order 3, which stores int data
    BTree<int,3> t1;

    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);

    t1.Print(); // Should output the following on the screen:

    /*
    1,4
      0
      2,3
      5
    */

    // Construct a BTree of order 5, which stores char data
    BTree<char,5> t;

    // Look at the example in our lecture:
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');

    t.Print(); // Should output the following on the screen:

    /*
    K
      C,G
        A,B
        D,E,F
        H,I,J
      N,R
        L,M
        P,Q
        S,T
    */

    return 0;
}
