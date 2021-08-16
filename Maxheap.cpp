#include "Maxheap.h"
using namespace std;

Maxheap::Maxheap(int k) : maxnumofscores(k), currnumofscores(0)
{
    heap = (double *)malloc(maxnumofscores * sizeof(double));
    ids = (int *)malloc(maxnumofscores * sizeof(int));
}

int Maxheap::minindex(int low, int high)
{
    int min = -1;
    double minscore = 1000000.0;
    for (int i = low; i < high; i++)
    {
        if (heap[i] < minscore)
        {
            min = i;
            minscore = heap[i];
        }
    }
    return min;
}

void Maxheap::swapscores(int index1, int index2)
{
    double temp = 0.0;
    temp = heap[index1];
    int tempid = ids[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
    ids[index1] = ids[index2];
    ids[index2] = tempid;
}

void Maxheap::insert(double score, int id)
{
    int index;
    if (currnumofscores != maxnumofscores)
    {
        index = currnumofscores;
        currnumofscores++;
    }
    else
    {
        int tempindex = minindex(maxnumofscores / 2, maxnumofscores);
        if (score > heap[tempindex])
            index = tempindex;
        else
            return;
    }
    heap[index] = score;
    ids[index] = id;
    while (heap[index] > heap[(index - 1) / 2])
    {
        swapscores(index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
}

int Maxheap::Maxchild(int number1, int number2)
{   
    if(number1<currnumofscores && number2<currnumofscores)
    {
        if(heap[number1>heap[number2]])
            return number1;
        else
            return number2;
    }
    else if(number1<currnumofscores)
        return number1;
    else if(number2<currnumofscores)
        return number2;
    return -1;
}

double Maxheap::remove()
{
    int index = 0, Chosenchild;
    double Returnvalue = 0.0;
    if (currnumofscores > 0)
    {
        Returnvalue = heap[0];
        currnumofscores--;
        heap[0] = heap[currnumofscores];
        ids[0] = ids[currnumofscores];
        while (1)
        {
            Chosenchild = Maxchild(2 * index + 1, 2 * index + 2);
            if (Chosenchild != -1 && heap[Chosenchild] > heap[index])
            {
                swapscores(Chosenchild, index);
                index = Chosenchild;
            }
            else
                break;
        }
    }
    return Returnvalue;
}