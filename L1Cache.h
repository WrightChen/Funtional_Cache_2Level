#ifndef _L1CACHE_H_
#define _L1CACHE_H_

#define L1_SET_NUM 64

#include <iostream>
#include <array>
#include "Set.h"
#include "Lru.h"

#include "L2Cache.h"

using namespace std;

class L1Cache
{
    public:
        L1Cache(unsigned int id);
        void Load(uint64_t addr);
        void Store(uint64_t addr);

        CacheMESI UpdateL1(uint64_t addr, CacheMESI mesi);

        void SetL2Ptr(L2Cache* l2_ptr){
            m_l2_ptr = l2_ptr;
        }

        void Statistics(){

            if(m_load_counter != 0)
            cout << "[L1_" << m_id << "][Statistics]" << endl 
                 << "[Load][Total] " << dec << m_load_counter << endl
                 << "[Load][Hit] " << dec << m_load_hit << endl
                 << "[Load][Hit Rate] " << double(m_load_hit) / double(m_load_counter) * 100 << "%" << endl
                 << endl;
                
            if(m_store_counter != 0)
            cout << "[L1_" << m_id << "][Statistics]" << endl 
                 << "[Store][Total] " << dec << m_store_counter << endl
                 << "[Store][Hit] " << dec << m_store_hit << endl
                 << "[Store][Hit Rate] " << double(m_store_hit) / double(m_store_counter) * 100 << "%" << endl
                 << endl;
        }


    private:
		unsigned int						m_id;
        unsigned int						m_l1_size;
		unsigned int						m_way_num;
		unsigned int						m_line_size;
		unsigned int						m_set_num;

        unsigned int                        m_load_counter;
        unsigned int                        m_load_hit;
        unsigned int                        m_store_counter;
        unsigned int                        m_store_hit;

        array<Set, L1_SET_NUM>              m_l1;

        Lru                                 m_lru;
        L2Cache*                            m_l2_ptr;

};

#endif