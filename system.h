
#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "fpga.h"
#include <unordered_set>
#include <memory>
#include <vector>
#include "computation.hpp"
#include "accelerator.h"
#include <string>
#include <iostream>

struct system_t {
    shared_ptr<fpga_t> fpga;
    std::unordered_set< std::shared_ptr<computation_t> > computations;
    std::unordered_set< std::shared_ptr<accelerator_t> > accelerators;
    shared_ptr<accelerator_t> choose_max_speedup(const bool parallel=true) const;
};

#endif
