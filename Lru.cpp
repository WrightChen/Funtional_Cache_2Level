#include "Lru.h"

uint8_t 
Lru::getlru(bool m_lru[]){
    if(m_lru[0] == 0){
        m_lru[0] = !m_lru[0];
        if(m_lru[1] == 0){
            m_lru[1] = !m_lru[1];
            if(m_lru[3] == 0){
                m_lru[3] = !m_lru[3];
                return 0;
            }
            else{
                m_lru[3] = !m_lru[3];
                return 1;
            }
        }
        else{
            m_lru[1] = !m_lru[1];
            if(m_lru[4] == 0){
                m_lru[4] = !m_lru[4];
                return 2;
            }
            else{
                m_lru[4] = !m_lru[4];
                return 3;
            }
        }
    }
    else{
        m_lru[0] = !m_lru[0];
        if(m_lru[2] == 0){
            m_lru[2] = !m_lru[2];
            if(m_lru[5] == 0){
                m_lru[5] = !m_lru[5];
                return 4;
            }
            else{
                m_lru[5] = !m_lru[5];
                return 5;
            }
        }
        else{
            m_lru[2] = !m_lru[2];
            if(m_lru[6] == 0){
                m_lru[6] = !m_lru[6];
                return 6;
            }
            else{
                m_lru[6] = !m_lru[6];
                return 7;
            }
        }
    }
}

uint8_t 
Lru::getfree(uint64_t m_lrurec[]){
    uint8_t i;
    for(i = 0; i < 8; ++i){
        if(m_lrurec[i] == 0)
            return i;
    }
    return 0xff;
}

void 
Lru::updlru(bool m_lru[], uint8_t m_loc){
    switch(m_loc){
        case 0 :
            m_lru[0] = 1;
            m_lru[1] = 1;
            m_lru[3] = 1;
            break;
        case 1 :
            m_lru[0] = 1;
            m_lru[1] = 1;
            m_lru[3] = 0;
            break;
        case 2 :
            m_lru[0] = 1;
            m_lru[1] = 0;
            m_lru[4] = 1;
            break;
        case 3 :
            m_lru[0] = 1;
            m_lru[1] = 0;
            m_lru[4] = 0;
            break;
        case 4 :
            m_lru[0] = 0;
            m_lru[2] = 1;
            m_lru[5] = 1;
            break;
        case 5 :
            m_lru[0] = 0;
            m_lru[2] = 1;
            m_lru[5] = 0;
            break;
        case 6 :
            m_lru[0] = 0;
            m_lru[2] = 0;
            m_lru[6] = 1;
            break;
        case 7 :
            m_lru[0] = 0;
            m_lru[2] = 0;
            m_lru[6] = 0;
            break;
        default :
            std::cout << "Error: The wrong lru number(L1). Error Loc: " << std::dec << m_loc <<std::endl;
    }
}


uint8_t 
Lru::getlru_16(bool m_lru[]){
    if(m_lru[0] == 0){
        m_lru[0] = !m_lru[0];
        if(m_lru[1] == 0){
            m_lru[1] = !m_lru[1];
            if(m_lru[3] == 0){
                m_lru[3] = !m_lru[3];
                if(m_lru[7] == 0){
                    m_lru[7] = !m_lru[7];
                    return 0;
                }
                else{
                    m_lru[7] = !m_lru[7];
                    return 1;
                }
            }
            else{
                m_lru[3] = !m_lru[3];
                if(m_lru[8] == 0){
                    m_lru[8] = !m_lru[8];
                    return 2;
                }
                else{
                    m_lru[8] = !m_lru[8];
                    return 3;
                }
            }
        }
        else{
            m_lru[1] = !m_lru[1];
            if(m_lru[4] == 0){
                m_lru[4] = !m_lru[4];
                if(m_lru[9] == 0){
                    m_lru[9] = !m_lru[9];
                    return 4;
                }
                else{
                    m_lru[9] = !m_lru[9];
                    return 5;
                }
            }
            else{
                m_lru[4] = !m_lru[4];
                if(m_lru[10] == 0){
                    m_lru[10] = !m_lru[10];
                    return 6;
                }
                else{
                    m_lru[10] = !m_lru[10];
                    return 7;
                }
            }
        }
    }
    else{
        m_lru[0] = !m_lru[0];
        if(m_lru[2] == 0){
            m_lru[2] = !m_lru[2];
            if(m_lru[5] == 0){
                m_lru[5] = !m_lru[5];
                if(m_lru[11] == 0){
                    m_lru[11] = !m_lru[11];
                    return 8;
                }
                else{
                    m_lru[11] = !m_lru[11];
                    return 9;
                }
            }
            else{
                m_lru[5] = !m_lru[5];
                if(m_lru[12] == 0){
                    m_lru[12] = !m_lru[12];
                    return 10;
                }
                else{
                    m_lru[12] = !m_lru[12];
                    return 11;
                }
            }
        }
        else{
            m_lru[2] = !m_lru[2];
            if(m_lru[6] == 0){
                m_lru[6] = !m_lru[6];
                if(m_lru[13] == 0){
                    m_lru[13] = !m_lru[13];
                    return 12;
                }
                else{
                    m_lru[13] = !m_lru[13];
                    return 13;
                }
            }
            else{
                m_lru[6] = !m_lru[6];
                if(m_lru[14] == 0){
                    m_lru[14] = !m_lru[14];
                    return 14;
                }
                else{
                    m_lru[14] = !m_lru[14];
                    return 15;
                }
            }
        }
    }
}

void 
Lru::updlru_16(bool m_lru[], uint8_t m_loc){
    switch(m_loc){
        case 0 :
            m_lru[0] = 1;
            m_lru[1] = 1;
            m_lru[3] = 1;
            m_lru[7] = 1;
            break;
        case 1 :
            m_lru[0] = 1;
            m_lru[1] = 1;
            m_lru[3] = 1;
            m_lru[7] = 0;
            break;
        case 2 :
            m_lru[0] = 1;
            m_lru[1] = 1;
            m_lru[3] = 0;
            m_lru[8] = 1;
            break;
        case 3 :
            m_lru[0] = 1;
            m_lru[1] = 1;
            m_lru[3] = 0;
            m_lru[8] = 0;
            break;
        case 4 :
            m_lru[0] = 1;
            m_lru[1] = 0;
            m_lru[4] = 1;
            m_lru[9] = 1;
            break;
        case 5 :
            m_lru[0] = 1;
            m_lru[1] = 0;
            m_lru[4] = 1;
            m_lru[9] = 0;
            break;
        case 6 :
            m_lru[0] = 1;
            m_lru[1] = 0;
            m_lru[4] = 0;
            m_lru[10] = 1;
            break;
        case 7 :
            m_lru[0] = 1;
            m_lru[1] = 0;
            m_lru[4] = 0;
            m_lru[10] = 0;
            break;
        case 8 :
            m_lru[0] = 0;
            m_lru[2] = 1;
            m_lru[5] = 1;
            m_lru[11] = 1;
            break;
        case 9 :
            m_lru[0] = 0;
            m_lru[2] = 1;
            m_lru[5] = 1;
            m_lru[11] = 0;
            break;
        case 10 :
            m_lru[0] = 0;
            m_lru[2] = 1;
            m_lru[5] = 0;
            m_lru[12] = 1;
            break;
        case 11 :
            m_lru[0] = 0;
            m_lru[2] = 1;
            m_lru[5] = 0;
            m_lru[12] = 0;
            break;
        case 12 :
            m_lru[0] = 0;
            m_lru[2] = 0;
            m_lru[6] = 1;
            m_lru[13] = 1;
            break;
        case 13 :
            m_lru[0] = 0;
            m_lru[2] = 0;
            m_lru[6] = 1;
            m_lru[13] = 0;
            break;
        case 14 :
            m_lru[0] = 0;
            m_lru[2] = 0;
            m_lru[6] = 0;
            m_lru[14] = 1;
            break;
        case 15 :
            m_lru[0] = 0;
            m_lru[2] = 0;
            m_lru[6] = 0;
            m_lru[14] = 0;
            break;
        default :
            std::cout << "Error: The wrong lru number(L2). Error Loc: " << std::dec << m_loc <<std::endl;
    }
}

uint8_t 
Lru::getfree_16(uint64_t m_lrurec[]){
    uint8_t i;
    for(i = 0; i < 16; ++i){
        if(m_lrurec[i] == 0)
            return i;
    }
    return 0xff;
}