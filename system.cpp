
#include "system.h"

#include <set>
#include <iostream>


#define __compare__shared_ptr_computation_t bool(*)(std::shared_ptr<computation_t>,std::shared_ptr<computation_t>)
bool __compare__shared_ptr_computation(shared_ptr<computation_t> l, shared_ptr<computation_t> r) {
    return l->priority < r->priority;
}


shared_ptr<accelerator_t> system_t::choose_max_speedup() const {

    shared_ptr<accelerator_t> out = 0;
    double max_speedup = 1.0;

    for (auto a : accelerators) { // for every accelerator
        uint32_t homogenious_time = 0;
        uint32_t system_time = 0;
        uint32_t accelerator_time = fpga->p;
        for (auto c : computations) {
            if (
                (c->accelerators.find(a) != c->accelerators.end())
                && (c->accelerator_setup_time(a) < c->system_time())
            ) { // if computation can/should use accelerator
                accelerator_time += c->accelerator_setup_time(a);
                accelerator_time += c->accelerator_computation_time(a);
                // assume cpu has no delay due to setup
            } else {
                system_time += c->system_time();
            }
            homogenious_time += c->system_time();
        }
        double speedup = (double)homogenious_time / heterogeneous_time;
        cout << a->name << ": "<< speedup << endl;
        if (speedup > max_speedup) {
            out = a;
            max_speedup = speedup;
        }
    }

    return out;
}
