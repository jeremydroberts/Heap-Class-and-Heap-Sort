/* Jeremy Roberts
 * 
 * 1 March 2018
 * 
 * Heapsort
 * 
 * This is the header file for template of Heap Class,
 * containing class definition and implementation of
 * all member functions.
 */

#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

/* Note the type T needs to implement comparison operators */
template <class T>
class Heap{

public:
   Heap();

   //Initialize the heap with the given data, and call build_heap to make it a heap
   //initData is initialized starting at index 0
   Heap(T initData[], int len);

   //return true if heap property is satisfied, false if violated
   bool IsHeap();

   /* precondition:
   *   1) heapLength>=i>1
   *   2) node i's left subtree and right subtree meet the heap property, 
   *      node i might violate heap property, 
   * postcondition: the subtree rooted at node i met heap property */
   void heapify(int i);

   /* insert a new item into the heap. 
   * Precondition: length+1<MAX_SIZE; //We have room to grow 
   1. increment heap length by 1
   2. store new item at the end of the heap, say the location is j
   3. walk your way up from node j to root, compare values stored at a node with its parent and swap
   the items if necessary.
   */
   void Insert(T item);

   /*  modify item stored in position i to the newValue, and repair heap property.
   *   Precondition: heap property is statisfied, 
   *   	        1<=i<=length
   *   Postcondition: i-th element is modified, and heap property is satisfied 
   *   Note that you cannot just call build_heap, which is overkill, instead you 
   *   need to repair heap property as efficient as possible).
   When node i's value is changed to a smaller value, then heapify(i) can fix the whole heap.
   When node i's value is changed to a larger value, then the tree rooted at i is still a heap, 
    but the whole tree might not. Think about how to fix! 
   */
   void Modify(int i, T newValue);

   // return the item stored in the root node of the heap
   T GetRoot(); 

   // remove and return item stored in root from the heap
   T RemoveRoot();

   /* display elements of data onto screen
    * Precondition: initialized data[], not necessarily sorted
    * Postcondition: elements displayed onto screen
   */
   void PrintHeap();

   /* Display results of test for heap property
    * Precondition: initialized data[], not necessarily sorted
    * Postcondition: results of IsHeap test output onto screen
    */
   void OutputTestResults();

   /* arrange values in array a in ascending order
   param a: the array
   param size: the length of array (# of element)
   */
   void Heapsort();

   /* Precondition: the array has been filled with elements, but heap property is not satisfied
   Postcondition:  rearrange elements so that the whole heap statisfies heap property. 
   *This method should be called in the second constructor*/
   void build_heap();
   
private:
   //Precondition: i is the numbering of node (starting from 1)
   //              i is not 1 (as root node has no parent)
   //Postcondition: the numbering of node i's parent is returned
   inline int parent(int i)
   {
      //return i/2 (calculating i/2 using bitewise shift operators)
      return(i>>1);
   }

   //return the numbering of the left child of node i
   // if node i has no left child, return -1 (note use heapLength to see if there is one)
   inline int leftchild (int i)
   {
      //return 2*i (calculated using bitwise shift operators)
      if((i<<1)<=heapLength)
         return(i<<1);
      else
         return(-1);
   }

   //return the numbering of the right child of node i
   // if node i has no right child, return -1 (note use heapLength to see if there is one)
   inline int rightchild (int i)
   {
      // return 2*i+1 (left shift, bitwise OR)
      if((i<<1|1)<=heapLength)
         return(i<<1|1);
      else
         return(-1);
   }
   
   //swap two elements of the heap
   //Precondition: the array is filled with elements
   //Postcondition: specified elements are swapped
   inline void swap(int i, int j)
   {
      T temp = data[i];
      data[i] = data[j];
      data[j] = temp;
   }

   T data[MAX_SIZE]; //You could store elements from index 1 (i.e., leave
   //first slot of the array empty), this way, you can use abvoe parent(),leftchild(),
   //rightchild() function to return the location of the nodes
   
   int heapLength;  // the actual number of elements in the heap
};

//Member function definitions

template <class T>
Heap<T>::Heap()
{
   int heapLength = 0;
}

template <class T>
Heap<T>::Heap(T initData[], int len)
{
   for(int i=0; i<len; i++)
   {
      //data is initialized from index 1s
      //initData initialized from index 0
      data[i+1] = initData[i];
   }

   heapLength = len;

   build_heap();
   return;
}

template <class T>
bool Heap<T>::IsHeap()
{
   bool isHeap = true;
   for(int i=(heapLength/2); i>=1; i--)
   {
      if(data[i]<data[leftchild(i)] || data[i]<data[rightchild(i)])
         isHeap = false;
   }
   return(isHeap);
}

template <class T>
void Heap<T>::heapify(int i)
{
   int l = leftchild(i);
   int r = rightchild(i);
   int largest;

   if(l<=heapLength && data[i]<data[l])
      largest = l;
   else
      largest = i;

   if(r<=heapLength && data[largest]<data[r])
      largest = r;

   if(largest != i)
   {
      swap(i,largest);
      heapify(largest);
   }
   return; 
}

template <class T>
void Heap<T>::Insert(T item)
{
   if(heapLength+1<MAX_SIZE)
   {
      int j=heapLength+1;
      data[j] = item;
      heapLength++;

      while(!IsHeap())
      {
         heapify(parent(j));
         j = parent(j);
      }
   }
   return;
}

template <class T>
void Heap<T>::Modify(int i, T newValue)
{
   T old_key = data[i];
   data[i] = newValue;

   if(newValue<old_key)
   {
      heapify(i);
   }
   else if(old_key<newValue)
   {
      while(!IsHeap())
      {
         heapify(parent(i));
         i = parent(i);
      }
   }
   return;
}

template<class T>
T Heap<T>::GetRoot()
{
   return(data[1]);
}

template<class T>
T Heap<T>::RemoveRoot()
{
   T root = data[1];
   for(int i=1; i<=heapLength; i++)
   {
      data[i] = data[i+1];
   }

   //re-build heap with new root
   build_heap();

   heapLength--;
   return(root);
}

template<class T>
void Heap<T>::PrintHeap()
{
   cout << "Data: ";
   for(int i=1; i<=heapLength; i++)
      cout << data[i] << " ";
   cout << endl;
   return;
}

template<class T>
inline void Heap<T>::OutputTestResults()
{
   if(IsHeap())
      cout << "Satisfies Heap Property!\n";
   else
      cout << "Something is wrong!\n";
}

template<class T>
void Heap<T>::Heapsort()
{
   //variable to hold length
   int len = heapLength;
   
   //swap, shorten, heapify
   for(int i=heapLength; i>=1; i--)
   {
      swap(i, 1);
      heapLength--;
      heapify(1);
   }
   //reset heaplength to include sorted elements
   heapLength = len;
   return;
}

template<class T>
void Heap<T>::build_heap()
{
   for(int i=(heapLength/2); i>=1; i--)
   {
      heapify(i);
   }
   return;
}

//Comparison operator for template
//Precondition: initialized objects of class T
//Postcondition: return comparison
template<class T>
bool operator<(const T& rhs, const T& lhs)
{
   return(rhs<lhs);
}

