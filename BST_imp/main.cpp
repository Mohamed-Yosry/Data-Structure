#include <iostream>
#include<queue>
using namespace std;


class BST
{
    struct node
    {
        int data;
        node*right;
        node*left;
    };

    node*root=NULL;
public:
    void add_iter(int val)
    {
        node*newnode=new node;
        newnode->data=val;
        newnode->left=NULL;
        newnode->right=NULL;
        if(root==NULL)
        {
            root=newnode;
        }
        else
        {
            node*temp=root;
            node*parent=root;
            while(temp!=NULL)
            {
                parent=temp;
                if(val<=temp->data)
                    temp=temp->left;
                else
                    temp=temp->right;
            }
            if(val<=parent->data)
                parent->left=newnode;
            else
                parent->right=newnode;
        }
    }
    void addHelper(int val,node *newnode)
    {
        if(val<=newnode->data)
        {
            if(newnode->left==NULL)
            {
                node*newnode2=new node;
                newnode2->data=val;
                newnode=newnode2;
                newnode2->left=NULL;
                newnode2->right=NULL;
            }
            else
                addHelper(val,newnode->left);
        }
        else
        {
            if(newnode->right==NULL)
            {
                node*newnode2=new node;
                newnode2->data=val;
                newnode=newnode2;
                newnode2->left=NULL;
                newnode2->right=NULL;
            }
            else
                addHelper(val,newnode->right);
        }
    }
    void add_rec(int val)
    {
        if(root==NULL)
        {
            node*newnode=new node;
            newnode->data=val;
            root=newnode;
            newnode->left=NULL;
            newnode->right=NULL;
        }
        else
        {
            addHelper(val,root);
        }
    }

    int getMax_iter()
    {
        node*temp=root;
        while(temp->right!=NULL)
        {
            temp=temp->right;
        }
        return temp->data;
    }

    int getMin_iter()
    {
        node*temp=root;
        while(temp->left!=NULL)
        {
            temp=temp->left;
        }
        return temp->data;
    }

    int getMaxHelper(node *temp)
    {
        if(temp->right!=NULL)
            return getMaxHelper(temp->right);
        else
            return temp->data;
    }

    int getMax_rec()
    {
        node*temp=root;
        if(temp->right!=NULL)
        {
            return getMaxHelper(temp->right);
        }
        return temp->data;
    }

    node* getMineHelper(node *temp)
    {
        if(temp->left!=NULL)
            getMineHelper(temp->left);
        return temp;
    }

    int getMin_rec()
    {
        node*temp=root;
        if(temp->left!=NULL)
        {
            temp=getMineHelper(temp->left);
        }
        return temp->data;
    }

    int getHightHelper(node *temp)
    {
        if(temp==NULL)
            return -1;

        int leftsub=getHightHelper(temp->left);
        int rightsub=getHightHelper(temp->right);

        return 1+max(leftsub,rightsub);
    }
    int getHight()
    {
        if(root ==NULL)
            return -1;
        else
            return getHightHelper(root);
    }


    void printBFS()
    {
        node*current=root;
        if(root==NULL)
            return;
        else
        {
            queue<node*>q;
            q.push(root);
            while(!q.empty())
            {
                current=q.front();
                cout<<current->data<<" ";
                q.pop();
                if(current->left!=NULL)
                    q.push(current->left);
                if(current->right!=NULL)
                    q.push(current->right);
            }
            cout<<endl;
        }
    }

    void preorder()
    {
        if(root==NULL)
            return;
        else
            preorderHelper(root);
    }
    void preorderHelper(node *temp)
    {
        if(temp==NULL)
            return;
        cout<<temp->data<<" ";
        preorderHelper(temp->left);
        preorderHelper(temp->right);
    }

    void inorder()
    {
        if(root==NULL)
            return;
        else
            inorderHelper(root);
    }
    void inorderHelper(node *temp)
    {
        if(temp==NULL)
            return;
        inorderHelper(temp->left);
        cout<<temp->data<<" ";
        inorderHelper(temp->right);
    }

    void postorder()
    {
        if(root==NULL)
            return;
        else
            postorderHelper(root);
    }
    void postorderHelper(node *temp)
    {
        if(temp==NULL)
            return;
        postorderHelper(temp->left);
        postorderHelper(temp->right);
        cout<<temp->data<<" ";
    }
};

int main()
{
    BST b;
    b.add_iter(10);
    b.add_iter(7);
    b.add_iter(3);
    b.add_iter(9);
    b.add_iter(15);
    b.add_iter(12);


    cout<<"Max: "<<b.getMax_rec()<<endl<<"Height: "<<b.getHight()<<endl;
    cout<<"Preorder: ";
    b.preorder();
    cout<<endl;
    cout<<"Inorder: ";
    b.inorder();
    cout<<endl;
    cout<<"Postorder: ";
    b.postorder();
    cout<<endl;
    return 0;
}
