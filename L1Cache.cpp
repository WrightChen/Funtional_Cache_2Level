#include "L1Cache.h"

L1Cache::L1Cache(unsigned int id)
: m_id(id)
, m_l1_size(32*1024)
, m_way_num(8)
, m_line_size(64)
, m_set_num(64)
, m_load_counter(0)
, m_load_hit(0)
, m_store_counter(0)
, m_store_hit(0)
{
    
}

/*---------------------------------------------------------------------------------------------------------------------------------------------*/

void 
L1Cache::Load(uint64_t addr)
{
    unsigned int t_num, t_loc;
    uint64_t t_tag, t_addr, t_evict;
    Way t_way;

    ++m_load_counter;
    // cout  << endl << hex << addr << " L " << m_id;

    //cout << "[L1][Load] " << "Address = " << addr << endl;

    t_tag = addr >> 12;
    t_num = (addr & L1_OFFSET) >> 6;
    
    //cout << "[L1][Load] " << "Set_num = " << t_num << endl;

    if(m_l1[t_num].way.find(t_tag) == m_l1[t_num].way.end()){
        // L1 Cache Miss.
        // cout << " 1M";
        if(m_l1[t_num].way.size() < m_way_num){
            //--------------------------------------------- Have free entry. ---------------------------------------------
            t_loc = m_lru.getfree(m_l1[t_num].lrurec);
            m_lru.updlru(m_l1[t_num].lru, t_loc);

            t_way.mesi = E;
            t_way.loc = t_loc;
            m_l1[t_num].way.insert({t_tag, t_way});
            m_l1[t_num].lrurec[t_loc] = addr;

            m_l2_ptr->Load(addr, m_id);

            //cout << "[L1][Load][Located] " << t_loc << endl;
        }
        else{
            //--------------------------------------------- No free entry, need evict. ---------------------------------------------
            t_loc = m_lru.getlru(m_l1[t_num].lru);
            t_addr = m_l1[t_num].lrurec[t_loc];
            t_evict = t_addr >> 12;

            //Evict and update L2
            if(m_l1[t_num].way[t_evict].mesi == M){
                m_l2_ptr->UpdateL2(t_addr, M, m_id, I);
            }
            else{
                m_l2_ptr->UpdateL2Record(t_addr, m_id, I);
            }

            //Update L1
            m_l1[t_num].lrurec[m_l1[t_num].way[t_evict].loc] = 0;
            m_l1[t_num].way.erase(t_evict);
            t_way.mesi = E;
            t_way.loc = t_loc;
            m_l1[t_num].way.insert({t_tag, t_way});
            m_l1[t_num].lrurec[t_loc] = addr;

            m_l2_ptr->Load(addr, m_id);

            //cout << "[L1][Load][Located] " << t_loc << endl;
        }
    }
    else{
        //------------------------------------------------ L1 Cache Hit. ------------------------------------------------
        ++m_load_hit;
        // cout << " 1H";
        t_loc = m_l1[t_num].way[t_tag].loc;
        m_lru.updlru(m_l1[t_num].lru, t_loc);

        //cout << "[L1][Load][Located] " << t_loc << endl;
    }
        

    //cout << "[L1][Load][Size] " << m_l1[t_num].way.size() << endl;
}


/*----------------------------------------------------------------------------------------------------------------------------------------------*/


void 
L1Cache::Store(uint64_t addr)
{
    unsigned int t_num, t_loc;
    uint64_t t_tag, t_addr, t_evict;
    Way t_way;

    ++m_store_counter;
    // cout  << endl << hex << addr << " S " << m_id;
    //cout << "[L1][Store] " << "Address = " << addr << endl;

    t_tag = addr >> 12;
    t_num = (addr & L1_OFFSET) >> 6;
    
    //cout << "[L1][Store] " << "Set_num = " << t_num << endl;

    if(m_l1[t_num].way.find(t_tag) == m_l1[t_num].way.end()){
        //-------------------------------------------------  L1 Cache Miss.  ------------------------------------------------- 
        // cout << " 1M";
        if(m_l1[t_num].way.size() < m_way_num){
            //--------------------------------------------- Have free entry. ---------------------------------------------
            t_loc = m_lru.getfree(m_l1[t_num].lrurec);
            m_lru.updlru(m_l1[t_num].lru, t_loc);
            
            t_way.mesi = M;
            t_way.loc = t_loc;
            m_l1[t_num].way.insert({t_tag, t_way});
            m_l1[t_num].lrurec[t_loc] = addr;

            m_l2_ptr->LoadInv(addr, m_id, false);

            //cout << "[L1][Store][Located] " << t_loc << endl;
        }
        else{
            //--------------------------------------------- No free entry, need evict. ---------------------------------------------
            t_loc = m_lru.getlru(m_l1[t_num].lru);
            t_addr = m_l1[t_num].lrurec[t_loc];
            t_evict = t_addr >> 12;

            //Evict and update L2
            if(m_l1[t_num].way[t_evict].mesi == M){
                m_l2_ptr->UpdateL2(t_addr, M, m_id, I);
            }
            else{
                m_l2_ptr->UpdateL2Record(t_addr, m_id, I);
            }
            
            //Update L1
            m_l1[t_num].lrurec[m_l1[t_num].way[t_evict].loc] = 0;
            m_l1[t_num].way.erase(t_evict);
            t_way.mesi = M;
            t_way.loc = t_loc;
            m_l1[t_num].way.insert({t_tag, t_way});
            m_l1[t_num].lrurec[t_loc] = addr;

            m_l2_ptr->LoadInv(addr, m_id, false);

            //cout << "[L1][Store][Located] " << t_loc << endl;
        }
    }
    else{
        //------------------------------------------------ L1 Cache Hit. ------------------------------------------------
        ++m_store_hit;
        // cout << " 1H";
        if(m_l1[t_num].way[t_tag].mesi != S){
            m_l1[t_num].way[t_tag].mesi = M;
            t_loc = m_l1[t_num].way[t_tag].loc;
            m_lru.updlru(m_l1[t_num].lru, t_loc);
        }
        else{
            m_l1[t_num].way[t_tag].mesi = M;
            t_loc = m_l1[t_num].way[t_tag].loc;
            m_lru.updlru(m_l1[t_num].lru, t_loc);
            m_l2_ptr->LoadInv(addr, m_id, true);
        }
        

        //cout << "[L1][Store][Located] " << t_loc << endl;
    }
        

    //cout << "[L1][Store][Size] " << m_l1[t_num].way.size() << endl;
}




CacheMESI 
L1Cache::UpdateL1(uint64_t addr, CacheMESI mesi)
{
    unsigned int t_num;
    uint64_t t_tag;
    CacheMESI t_mesi;

    t_tag = addr >> 12;
    t_num = (addr & L1_OFFSET) >> 6;

    t_mesi = m_l1[t_num].way[t_tag].mesi;

    if(mesi != I)
        m_l1[t_num].way[t_tag].mesi = mesi;
    else{
        m_l1[t_num].lrurec[m_l1[t_num].way[t_tag].loc] = 0;
        m_l1[t_num].way.erase(t_tag);
    }

    return t_mesi;
}