#ifndef _LRU_H_
#define _LRU_H_

#include <stdint.h>
#include <iostream>

struct Lru
{
    public:
        void updlru(bool m_lru[], uint8_t m_loc);
        uint8_t getlru(bool m_lru[]);
        uint8_t getfree(uint64_t m_lrurec[]);
        
        void updlru_16(bool m_lru[], uint8_t m_loc);
        uint8_t getlru_16(bool m_lru[]);
        uint8_t getfree_16(uint64_t m_lrurec[]);
};

#endif