#include <iostream>
#include "freeList.h"
#include "growingPoolAllocator.h"

/***
 * UE2 - GROWING POOL ALLOCATOR
 * Markus Karner
 * Theodor Knab
 * Oliver Schmidt 
 */

int main()
{	
    //TEST-CASE 1 | Create allocator and have it automatically increase its size
    GrowingPoolAllocator allocator(8, 2);

	void* testPtr0 = allocator.alloc(8);
    void* testPtr1 = allocator.alloc(8);
    void* testPtr2 = allocator.alloc(4);

    //TEST-CASE 2 | Asign value to Pointer, then free it from the allocator and try to read its value again
    *static_cast<int*>(testPtr0) = 5;	
    std::cout << *static_cast<int*>(testPtr0) << std::endl;
	
    allocator.free(testPtr0);	
    std::cout << *static_cast<int*>(testPtr0) << std::endl;

    allocator.free(testPtr1);
    allocator.free(testPtr2);
    

    //Edge-case testcases commented out to keep the programming running normally


    //TEST-CASE 3 | Assert on allocated size greater than chunk size from allocator
	//void* testPtr2 = allocator.alloc(16);

	
	//TEST-CASE 4 | Assert on freeing an already free positions
    //allocator.free(testPtr1);
    //allocator.free(testPtr0);
    //allocator.free(testPtr0);
	

    //TEST-CASE 5 | Assert on freeing allocation with a pointer that doesn't point to an address of the allocator
	//GrowingPoolAllocator allocator2(8, 2);
	//void* wrongPtr = allocator2.alloc(4);	
	//allocator.free(wrongPtr);
	//allocator2.~GrowingPoolAllocator();
	
    allocator.~GrowingPoolAllocator();
}