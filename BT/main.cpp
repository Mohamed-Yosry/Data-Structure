#include <iostream>
#include<vector>
using namespace std;

int power(int n,int p)
{
    if(p==0)
        return 1;
    else
        return n*power(n,p-1);
}

template<typename T>
struct Tree {
Tree(const T &v) : value(v), left(NULL), right(NULL) {}
T value;
Tree *left;
Tree *right;
};
Tree<int>*roo=NULL;
/////////////////////////////////////////////
/////////////////Tree printing /////////////
void Inorder(Tree<int>*node=roo)
{
    if (node == NULL)
        return;
    else
    {
        Inorder(node->left);
        cout <<node->value << " ";
        Inorder(node->right);
    }
}

void Preorder(Tree<int>* node=roo)
{
    if (node == NULL)
        return;
    cout << node->value << " ";
    Preorder(node->left);
    Preorder(node->right);
}


void Postorder(Tree<int>* node=roo)
{
    if (node == NULL)
        return;
    Postorder(node->left);
    Postorder(node->right);
    cout << node->value<< " ";
}


//////////////////////////////////////////////////
//   Tree flipping    //

void flip(Tree<int>*obj=roo)
{
    if(obj->left==NULL &&obj->right==NULL)
        return;
    if(obj!=NULL)
    {
        swap(obj->left,obj->right);
    }
    flip(obj->left);
    flip(obj->right);
}


//          Digit Sum               //
void branchesSumHelper(vector<int>digits,Tree<int>*obj,int&sum)
{
    if(obj==NULL)
        return;
    if(obj!=NULL)
    {
        digits.push_back(obj->value);
    }
    if(obj->left==NULL && obj->right==NULL)
    {
        for(int i=0;i<digits.size();i++)
        {
            sum+=(digits[i]*power(10,(digits.size()-i-1)));
        }
        digits.pop_back();
    }
    branchesSumHelper(digits,obj->left,sum);
    branchesSumHelper(digits,obj->right,sum);
}

long branchesSum(Tree <int>*obj)
{
    int sum=0;
    vector<int>digits;
    branchesSumHelper(digits,obj,sum);
    return sum;
}

////////////////////////////////////////////////////////////
//          largest value               //
void largestValuesHelper(Tree<int>*current,vector<int>&arr,int level)
{
    if(current==NULL)
        return;
    if(current!=NULL && level==arr.size())
    {
        arr.push_back(current->value);
    }
    else if(current!=NULL && level!=arr.size())
    {
        if(current->value>arr[level])
            arr[level]=current->value;
    }
    largestValuesHelper(current->left,arr,level+1);
    largestValuesHelper(current->right,arr,level+1);
}

void largestValues(Tree<int>*obj)
{
    int level=0;
    vector<int>arr;
    largestValuesHelper(obj,arr,level);
    cout<<"[ ";
    for(int i=0;i<arr.size();i++)
        cout<<arr[i]<<" ";
    cout<<"]"<<endl;
}






int main()
{
    Tree<int>* t = new Tree<int>(1);
    Tree<int>* _1_left = new Tree<int>(2);
    Tree<int>* _1_right = new Tree<int>(3);
    t->left = _1_left; t->right = _1_right;
    Tree<int>* _2_left = new Tree<int>(4);
    Tree<int>* _2_right = new Tree<int>(5);
    _1_left->left = _2_left; _1_left->right = _2_right;
    roo=t;

    cout<<"Inorder: ";
    Inorder(t);
    cout<<endl;
    cout<<"Preorder: ";
    Preorder(t);
    cout<<endl;
    cout<<"postorder: ";
    Postorder(t);
    cout<<endl;


    cout<<"Largest values: ";
    largestValues(t);
    cout<<endl;

    cout<<"Branch sum: ";
    cout<<branchesSum(t)<<endl;
    cout<<endl;

    cout<<"Flip: ";
    flip();
    cout<<endl;

    cout<<"Inorder: ";
    Inorder(t);
    cout<<endl;
    cout<<"Preorder: ";
    Preorder(t);
    cout<<endl;
    cout<<"postorder: ";
    Postorder(t);
    cout<<endl;

    return 0;
}
