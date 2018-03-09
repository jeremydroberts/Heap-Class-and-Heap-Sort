/* Jeremy Roberts
 * 1 March 2018
 * 
 * Heapsort
 * 
 * This is the implementation of Heap Class
 */
#include "heap.h"

int main()
{
	
	//initialized array of integers to test methods
	int a[7] = {2, 3, 4, 5, 6, 7, 8};
	
	//initialize instance of heapsort for testing
	Heap<int> intHeap(a, 7);
	cout << endl;
	intHeap.PrintHeap();
	intHeap.OutputTestResults();

	//test insert method
	cout << "\nTest Insert:\n";
	intHeap.Insert(9);
	intHeap.PrintHeap();
	intHeap.OutputTestResults();

	//test GetRoot method
	cout << "\nTest GetRoot:\n";
	cout << "Root: " << intHeap.GetRoot() << endl;
	intHeap.PrintHeap();

	//Test RemoveRoot method
	cout << "\nTest RemoveRoot:\n";
	cout << "Root: " << intHeap.RemoveRoot() << endl;
	intHeap.PrintHeap();
	intHeap.OutputTestResults();

	//Test Modify method with larger and smaller value
	cout << "\nTest Modify:\n" << "Larger Value:\n";
	intHeap.Modify(8, 10);
	intHeap.PrintHeap();
	intHeap.OutputTestResults();

	cout << "\nSmaller Value:\n";
	intHeap.Modify(8, 1);
	intHeap.PrintHeap();
	intHeap.OutputTestResults();

   //Test heap sort algorithm and output results
   cout << "\nTest Heap Sort:\n";
	intHeap.Heapsort();
	intHeap.PrintHeap();
	cout << endl;
}
