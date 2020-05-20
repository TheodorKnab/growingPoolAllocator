#include "freeList.h"

Freelist::Freelist()
{
	m_next = nullptr;
}


Freelist::Freelist(void* start, size_t chunkSize, size_t chunkAmount)
{
    union
    {
        void* as_void;
        char* as_char;
        Freelist* as_self;
    };

    // first chunk points to the start of the pool
    as_void = start;
    m_next = as_self;
    as_char += chunkSize;

    // initialize the free list - make every m_next of each chunk point to the next chunk in the list
    Freelist* runner = m_next;
    for (size_t i = 1; i < chunkAmount; ++i)
    {
        runner->m_next = as_self;
        runner = as_self;
        as_char += chunkSize;
    }

    runner->m_next = nullptr;
}

const Freelist* Freelist::getNext() const
{
    return m_next;
}
