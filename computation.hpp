
#ifndef __COMPUTATION_H
#define __COMPUTATION_H

#include "accelerator.h"

#include <unordered_set>
#include <memory>
#include <iostream>
#include <string>
#include "fpga.h"

using namespace std;


struct computation_t {
    const uint32_t priority;
    const uint32_t g; // granularity
    const uint32_t cs; // system computational index
    const std::unordered_set< std::shared_ptr<accelerator_t> > accelerators;
    const std::shared_ptr<fpga_t> fpga;
    const std::string name;

    class InvalidAccelerator { };
    uint32_t accelerator_computation_time(const std::shared_ptr<accelerator_t> a) const {
        if (accelerators.find(a)==accelerators.end()) throw InvalidAccelerator();
        return (a->ca * g);
    }
    uint32_t accelerator_setup_time(const std::shared_ptr<accelerator_t> a, const bool bitstream_loaded=true) const {
        if (accelerators.find(a)==accelerators.end()) throw InvalidAccelerator();
        uint32_t time = 0;
        time += bitstream_loaded ? 0 : fpga->p; // fpga program time
        time += (a->strict ? g : 1) * fpga->l; // latency
        time += a->o; // overhead
        return time;
    }
    uint32_t system_time(void) const {
        return cs * g;
    }
};

#endif
