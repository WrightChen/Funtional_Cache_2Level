#include "L1Cache.h"
#include "L2Cache.h"
#include <assert.h>

L2Cache::L2Cache(unsigned int id)
: m_id(id)
, m_l2_size(4*1024*1024)
, m_way_num(16)
, m_line_size(64)
, m_set_num(4096)
, m_load_counter(0)
, m_load_hit(0)
, m_loadinv_counter(0)
, m_loadinv_hit(0)
{
    
}


/*----------------------------------------------------------------------------------------------------------------------------------------------*/


void 
L2Cache::Load(uint64_t addr, unsigned int l1_id)
{
    bool t_share = false, t_modify = false;
    unsigned int t_num, t_loc;
    uint64_t t_tag, t_addr, t_evict;
    Way_l2 t_way;

    ++m_load_counter;

    cout << "[L2][Load] " << "Address = " << addr << endl;

    t_tag = addr >> 18;
    t_num = (addr & L2_OFFSET) >> 6;

    cout << "[L2][Load] " << "Set_num = " << t_num << endl;

    if(m_l2[t_num].way.find(t_tag) == m_l2[t_num].way.end()){
        // L2 Cache Miss.
        if(m_l2[t_num].way.size() < m_way_num){
            //--------------------------------------------- Have free entry. ---------------------------------------------
            t_loc = m_lru.getfree_16(m_l2[t_num].lrurec);
            m_lru.updlru_16(m_l2[t_num].lru, t_loc);
            t_way.mesi = E;
            t_way.loc = t_loc;
            t_way.record[l1_id] = E;
            m_l2[t_num].way.insert({t_tag, t_way});
            m_l2[t_num].lrurec[t_loc] = addr;

            cout << "[L2][Load][Located] " << t_loc << endl;

        }
        else{
            //--------------------------------------------- No free entry, need evict. ---------------------------------------------
            t_loc = m_lru.getlru_16(m_l2[t_num].lru);
            t_addr = m_l2[t_num].lrurec[t_loc];
            t_evict = t_addr >> 18;

            for(unsigned int i = 0; i < 8; ++i)
            {
                if(m_l2[t_num].way[t_evict].record[i] != I){
                    m_l1_ptr[i]->UpdateL1(t_addr, I);
                }
            }

            m_l2[t_num].way.erase(t_evict);
            t_way.mesi = E;
            t_way.loc = t_loc;
            t_way.record[l1_id] = E;
            m_l2[t_num].way.insert({t_tag, t_way});
            m_l2[t_num].lrurec[t_loc] = addr;

            cout << "[L2][Load][Located] " << t_loc << endl;
            
        }
    }
    else{
        //------------------------------------------------ L2 Cache Hit. ------------------------------------------------
        ++m_load_hit;
        for(unsigned int i = 0; i < 8; ++i)
        {
            if(i != l1_id){
                if(m_l2[t_num].way[t_tag].record[i] != I){
                    if((m_l1_ptr[i]->UpdateL1(addr, S)) == M)
                        t_modify = true;
                    t_share= true;
                }
            }
        }
        
        if(t_share){
            m_l1_ptr[l1_id]->UpdateL1(addr, S);
            m_l2[t_num].way[t_tag].record[l1_id] = S;
        }
        else{
            m_l2[t_num].way[t_tag].record[l1_id] = E;
        }

        if(t_modify)
            m_l2[t_num].way[t_tag].mesi = M;

        t_loc = m_l2[t_num].way[t_tag].loc;
        m_lru.updlru_16(m_l2[t_num].lru, t_loc);

        cout << "[L2][Load][Located] " << t_loc << endl;
    }
        

    cout << "[L2][Load][Size] " << m_l2[t_num].way.size() << endl;
}


/*----------------------------------------------------------------------------------------------------------------------------------------------*/


void 
L2Cache::LoadInv(uint64_t addr, unsigned int l1_id, bool l2_hit)
{
    bool t_modify = false;
    unsigned int t_num, t_loc;
    uint64_t t_tag, t_addr, t_evict;
    Way_l2 t_way;

    if(!l2_hit)
        ++m_loadinv_counter;

    cout << "[L2][LoadInv] " << "Address = " << addr << endl;

    t_tag = addr >> 18;
    t_num = (addr & L2_OFFSET) >> 6;

    cout << "[L2][LoadInv] " << "Set_num = " << t_num << endl;

    if(m_l2[t_num].way.find(t_tag) == m_l2[t_num].way.end()){
        // L2 Cache Miss.
        if(m_l2[t_num].way.size() < m_way_num){
            //--------------------------------------------- Have free entry. ---------------------------------------------
            t_loc = m_lru.getfree_16(m_l2[t_num].lrurec);
            m_lru.updlru_16(m_l2[t_num].lru, t_loc);
            t_way.mesi = E;
            t_way.loc = t_loc;
            t_way.record[l1_id] = E;
            m_l2[t_num].way.insert({t_tag, t_way});
            m_l2[t_num].lrurec[t_loc] = addr;

            cout << "[L2][LoadInv][Located] " << t_loc << endl;
        }
        else{
            //--------------------------------------------- No free entry, need evict. ---------------------------------------------
            t_loc = m_lru.getlru_16(m_l2[t_num].lru);
            t_addr = m_l2[t_num].lrurec[t_loc];
            t_evict = t_addr >> 18;

            for(unsigned int i = 0; i < 8; ++i)
            {
                if(m_l2[t_num].way[t_evict].record[i] != I){
                    m_l1_ptr[i]->UpdateL1(t_addr, I);
                }
            }

            m_l2[t_num].way.erase(t_evict);
            t_way.mesi = E;
            t_way.loc = t_loc;
            t_way.record[l1_id] = E;
            m_l2[t_num].way.insert({t_tag, t_way});
            m_l2[t_num].lrurec[t_loc] = addr;
        }
    }
    else{
        //------------------------------------------------ L2 Cache Hit. ------------------------------------------------
        if(!l2_hit)
            ++m_loadinv_hit;
        for(unsigned int i = 0; i < 8; ++i)
        {
            if(i != l1_id){
                if(m_l2[t_num].way[t_tag].record[i] != I){
                    if((m_l1_ptr[i]->UpdateL1(addr, I)) == M)
                        t_modify = true;
                    m_l2[t_num].way[t_tag].record[i] = I;
                }
            }
        }

        if(t_modify)
            m_l2[t_num].way[t_tag].mesi = M;

        m_l2[t_num].way[t_tag].record[l1_id] = E;
        t_loc = m_l2[t_num].way[t_tag].loc;

        m_lru.updlru_16(m_l2[t_num].lru, t_loc);

        cout << "[L2][LoadInv][Located] " << t_loc << endl;
    }
        

    cout << "[L2][LoadInv][Size] " << m_l2[t_num].way.size() << endl;
}



void 
L2Cache::UpdateL2Record(uint64_t addr, uint8_t core_num, CacheMESI r_mesi)
{
    unsigned int t_num;
    uint64_t t_tag;

    t_tag = addr >> 18;
    t_num = (addr & L2_OFFSET) >> 6;
    
    m_l2[t_num].way[t_tag].record[core_num] = r_mesi;
}




void 
L2Cache::UpdateL2(uint64_t addr, CacheMESI mesi, uint8_t core_num, CacheMESI r_mesi)
{
    unsigned int t_num;
    uint64_t t_tag;

    t_tag = addr >> 18;
    t_num = (addr & L2_OFFSET) >> 6;

    m_l2[t_num].way[t_tag].mesi = mesi;
    m_l2[t_num].way[t_tag].record[core_num] = r_mesi;

}