#pragma once

/***
 * \brief
 * Linked List, one element stores only a pointer to the next element in the list
 * Based on molecular musings free list implementation
 * https://blog.molecular-matters.com/2012/09/17/memory-allocation-strategies-a-pool-allocator/ 
 */
class Freelist
{
public:
    Freelist();
	
    /**
     * \param start
     * Pointer to the start of the memory buffer
     * \param chunkSize
     * Size of one chunk
     * \param chunkAmount
     * Defines how many chunks/elements the list contains
     */
    Freelist(void* start, size_t chunkSize, size_t chunkAmount);
	
    /**
     * \return a free address of the list
     */
    inline void* Obtain() {
        // is there an entry left?
        if (m_next == nullptr)
        {
            // we are out of entries
            return nullptr;
        }

        // obtain one chunk from the head of the free list
        Freelist* head = m_next;
        m_next = head->m_next;
        return head;
    }

	
    /**
     * \param ptr address to return to the list
     */
    inline void Return(void* ptr) {
        // put the returned chunk at the head of the free list
        Freelist* head = static_cast<Freelist*>(ptr);
        head->m_next = m_next;
        m_next = head;
    }

    const Freelist* getNext() const;

private:
    Freelist* m_next;
};
