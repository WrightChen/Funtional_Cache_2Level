#include "FunCache.h"

int main()
{
    FunCache m_cache(4);

    m_cache.Load(0, 0x111111);std::cout << std::endl;
    m_cache.Load(0, 0x222111);std::cout << std::endl;
    m_cache.Load(0, 0x333111);std::cout << std::endl;
    m_cache.Load(0, 0x444111);std::cout << std::endl;
    m_cache.Load(0, 0x555111);std::cout << std::endl;
    m_cache.Load(0, 0x666111);std::cout << std::endl;
    m_cache.Load(0, 0x111111);std::cout << std::endl;
    m_cache.Load(0, 0x777111);std::cout << std::endl;
    m_cache.Load(0, 0x888111);std::cout << std::endl;
    m_cache.Load(0, 0x999111);std::cout << std::endl;
    m_cache.Load(0, 0x1999111);std::cout << std::endl;
    m_cache.Load(0, 0x2999111);std::cout << std::endl;
    std::cout << std::endl;
    m_cache.Store(0, 0x111111);std::cout << std::endl;
    m_cache.Store(0, 0x222111);std::cout << std::endl;
    m_cache.Store(0, 0x333111);std::cout << std::endl;
    m_cache.Store(0, 0x444111);std::cout << std::endl;
    m_cache.Store(0, 0x555111);std::cout << std::endl;
    m_cache.Store(0, 0x666111);std::cout << std::endl;
    m_cache.Store(0, 0x111111);std::cout << std::endl;
    m_cache.Store(0, 0x777111);std::cout << std::endl;
    m_cache.Store(0, 0x888111);std::cout << std::endl;
    m_cache.Store(0, 0x999111);std::cout << std::endl;
    m_cache.Store(0, 0x1999111);std::cout << std::endl;
    m_cache.Store(0, 0x2999111);std::cout << std::endl;


    m_cache.Statistics();


    return 0;
}