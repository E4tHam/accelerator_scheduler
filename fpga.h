
#ifndef __FPGA_H
#define __FPGA_H

#include <memory>
#include "accelerator.h"
#include <string>
#include <iostream>

struct fpga_t {
    const uint32_t l; // communication latency
    const uint32_t p; // programming latency
    std::shared_ptr<accelerator_t> bitstream = 0;
};

#endif
