#pragma once
#include <libds/heap_monitor.h>
template <typename A, typename B, typename C>
inline void algoritmus(A begin, A end, B podmienka, C vykonaj)
{
    while (begin != end)
    {
        if (podmienka(*begin))
        {
            vykonaj(*begin);
        }
        ++begin;
    }
}