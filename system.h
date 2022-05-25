
#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "fpga.h"
#include <unordered_set>
#include <memory>
#include <vector>
#include "computation.hpp"
#include <string>
#include <iostream>

struct system_t {
    shared_ptr<fpga_t> fpga;
    std::unordered_set< std::shared_ptr<computation_t> > computations;
    shared_ptr<accelerator_t> choose_one_accelerator(const bool parallel=true) const;
};

#endif
