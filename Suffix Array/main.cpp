#include <iostream>

using namespace std;


int power(int n,int p)
{
    if(p==0)
        return 1;
    else
        return power(n,p-1)*2;
}

class SuffixArray
{
    char *arr;
    char *originalArr;
    int * index,*group;
    int arrSize=0;
public:
    SuffixArray(char a[])
    {
        int arrSize=0;
        while(a[arrSize]!='$')
            arrSize++;
        arrSize++;
        arr=new char[arrSize];
        originalArr=new char[2*arrSize];
        index=new int[arrSize];
        group=new int[arrSize];
        for(int i=0;i<arrSize;i++)
        {
            arr[i]=a[i];
            index[i]=i;
            group[i]=0;
            originalArr[i]=a[i];
            originalArr[arrSize+i]=' ';
        }
        setArrSize(arrSize);
    }

    void setArrSize(int s){arrSize=s;}
    int getArrSize(){return arrSize;}

    void ConstructUsingPrefixDoubling()
    {

        int grNo=0;
        int k=0;
        char smallestChar;

        MergeSort(0,getArrSize()-1,k);

        for(int i=0;i<arrSize;i++)
        {
            group[i]=grNo;
            if(arr[i]!=arr[i+1])
                grNo++;
        }

        k++;


        int prev;
        while(grNo<(arrSize)){
            prev=1;
            grNo=0;
            for(int i=1;i<arrSize;i++)
            {
                if(arr[i]==arr[i+1] &&( k==1 || group[i]==group[i+1]))
                {
                    continue;
                }
                else
                {
                    MergeSort(prev,i,k);
                    prev=i+1;
                }
            }
            for(int i=0;i<arrSize;i++)
            {
                group[i]=grNo;
                if(comparenotEqula(i,i+1,k))
                    grNo++;
            }
            k++;
        }




    }


    void Merge(int left, int middle, int right,int key)
    {
        int leftSize = (middle - left) + 1;
        int rightSize = right - middle;

        char* leftArray = new char[leftSize];
        char* rightArray = new char[rightSize];

        int*leftIndex=new int[leftSize];
        int*RightIndex=new int[rightSize];




        for (int i=0;i<leftSize;i++){
            leftArray[i]=arr[left+i];
            leftIndex[i]=index[left+i];
        }

        for (int i=0;i<rightSize;i++){
            rightArray[i]=arr[middle+1+i];
            RightIndex[i]=index[middle+1+i];
        }


        int L=0,R=0,K=left;
        while (L<leftSize && R<rightSize){
            if(key==0)
            {
                if (leftArray[L]<=rightArray[R]){
                arr[K]=leftArray[L];
                index[K]=leftIndex[L];
                L++;
                }

                else {
                    arr[K]=rightArray[R];
                    index[K]=RightIndex[R];
                    R++;
                }
                K++;
            }
            else
            {
                if (compare(key,L,R,leftIndex,RightIndex)){
                arr[K]=leftArray[L];
                index[K]=leftIndex[L];
                L++;
                }

                else {
                    arr[K]=rightArray[R];
                    index[K]=RightIndex[R];
                    R++;
                }
                K++;
            }
        }

        while (L<leftSize){
            arr[K]=leftArray[L];
            index[K]=leftIndex[L];
            L++;
            K++;
        }

        while (R<rightSize){
            arr[K]=rightArray[R];
            index[K]=RightIndex[R];
            R++;
            K++;
        }
    }


    void MergeSort( int left, int right,int k)
    {
        if (left < right){

            int middle = left + (right - left)/2;

            MergeSort(left, middle,k);
            MergeSort(middle+1, right,k);

            Merge(left, middle, right,k);

        }
    }

    bool compare(int key,int leftSize,int rightSize,int left[],int right[])
    {
        int pow=power(2,key);
        int prevpow=power(2,key-1);
        int counter=1;
        for(int i=prevpow;i<pow;i++)
        {
            if(originalArr[left[leftSize]+counter]>originalArr[right[rightSize]+counter]){
                return false;
            }

            counter++;
        }
        return true;
    }

    bool comparenotEqula(int n1,int n2,int k)
    {
        int pow=power(2,k);
        for(int i=0;i<pow;i++)
        {
            if(originalArr[index[n1]+i]!=originalArr[index[n2]+i])
                return true;
        }
        return false;
    }


    void Print()
    {
        for(int i=0;i<arrSize;i++)
            cout<<index[i]<<"    ";
    }

};


int main()
{
    SuffixArray t("ACGACTACGATAAC$");

    t.ConstructUsingPrefixDoubling();

    t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8 10  5

    return 0;
}
