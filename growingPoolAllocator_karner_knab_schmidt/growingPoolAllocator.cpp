#include "growingPoolAllocator.h"
#include <cassert>

GrowingPoolAllocator::GrowingPoolAllocator(size_t chunkSize, size_t growPoolByChunkAmount){	
    assert(chunkSize >= 8);	
    m_chunkSize = chunkSize;
    m_growPoolByAmountOfChunks = growPoolByChunkAmount;
    m_freeList = Freelist(allocatePool(), m_chunkSize, m_growPoolByAmountOfChunks);
}


GrowingPoolAllocator::~GrowingPoolAllocator() 
{
    for (auto pool : m_pools)
    {
        delete[] pool;
    }
    m_pools.clear();
}


void* GrowingPoolAllocator::alloc(size_t size) {
    assert(size <= m_chunkSize);
    void* memoryLocation = m_freeList.Obtain();

    if (memoryLocation == nullptr)
    {
    	
        m_freeList.~Freelist();
        new (&m_freeList) Freelist(allocatePool(), m_chunkSize, m_growPoolByAmountOfChunks);
    	
        memoryLocation = m_freeList.Obtain();
    }
    return memoryLocation;
}


void GrowingPoolAllocator::free(void* ptr) {

#ifdef _DEBUG
    if (!ptr) {
        return;
    }

    //check if pointer is already in the list (and is therefore already free)
    const Freelist* next = m_freeList.getNext();
    while (next != nullptr)
    {
        assert(ptr != next);
        if (ptr == next) return;
        
        next = next->getNext();
    }

    //check if address is contained in pools
    bool ptrInPool = false;
    for (auto pool : m_pools)
    {
        if (pool <= ptr && ptr < &pool[m_chunkSize * m_growPoolByAmountOfChunks])
        {
            ptrInPool = true;
        }
    }
    assert(ptrInPool);
#endif

    //check if pointer is actually in pool
    m_freeList.Return(ptr);
    ptr = nullptr;
}


unsigned char* GrowingPoolAllocator::allocatePool() {
    unsigned char* pool = new unsigned char[m_chunkSize * m_growPoolByAmountOfChunks];
    m_pools.push_back(pool);
    return pool;
}
