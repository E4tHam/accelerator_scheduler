
#ifndef __ACCELERATOR_H
#define __ACCELERATOR_H

#include <string>
#include <iostream>
#include <string>

struct accelerator_t {
    const uint32_t ca; // accelerator computational index
    const uint32_t o; // overheads of interface
    const bool strict; // requires entire block to be sent before computation begins
    const std::string name;
};

#endif
