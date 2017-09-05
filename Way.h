#ifndef _WAY_H_
#define _WAY_H_

#include <stdint.h>

enum CacheMESI{M = 3, E = 2, S = 1, I = 0};

struct Way
{
    public:
        CacheMESI mesi = I;
        unsigned int loc = 0xff;
};

struct Way_l2
{
    public:
        CacheMESI mesi = I;
        unsigned int loc = 0xff;
        CacheMESI record[8] = {I, I, I, I, I, I, I, I};
};

#endif