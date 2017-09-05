#ifndef _FUNCTION_CACHE_H_
#define _FUNCTION_CACHE_H_

#define CORE_NUM 4

#include <iostream>
#include <stdint.h>
#include <assert.h>

#include "L1Cache.h"

class FunCache
{
	public:
		FunCache(unsigned int core_num);
		~FunCache();

		void Load(unsigned int l1_id,uint64_t addr);
		void Store(unsigned int l1_id,uint64_t addr);
		void Statistics();
		
	private:
		L1Cache*					m_l1i_ptr[CORE_NUM];
		L1Cache*					m_l1d_ptr[CORE_NUM];
		L2Cache*					m_l2_ptr;
		unsigned int 				core_num;

};

#endif
