#pragma once
#include "freeList.h"
#include <vector>


/**
 * \brief Pool Memory Allocator that dynamically grows as the amount of current chunks is exceeded.
 * Allocates more memory by itself, that will only be freed with the destruction of the allocator.
 */
class GrowingPoolAllocator
{
public:
    /**
     * \param chunkSize Size of one chunk of the pool in bytes
     * \param growPoolByChunkAmount Defines with how many chunks the allocator starts and
     * by how many chunks the allocator grows when no chunks are available
     */
    GrowingPoolAllocator(size_t chunkSize, size_t growPoolByChunkAmount); 
    ~GrowingPoolAllocator(); //Deletes all pools in the allocator

    /**
     * \param size in bytes
     * \return Memory address of the requested chunk
     */
    void* alloc(size_t size);

    /**
     * \param Pointer that should be freed
     */
    void free(void* ptr);
	
private:
    /**
     * \brief Creates a new pool based m_chunkSize and m_growPoolByAmountOfChunks. This method allocates additional memory!
    */
    unsigned char* allocatePool();
    Freelist m_freeList; 
    size_t m_chunkSize; //Indicates the size of a chunk in bytes
    size_t m_growPoolByAmountOfChunks; //Indicates how many chunks the allocator should add once it is full
    std::vector<unsigned char*> m_pools; //references all created pools
};

