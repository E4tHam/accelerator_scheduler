
using namespace std;

#include "accelerator.h"
#include "computation.hpp"
#include "fpga.h"
#include "system.h"

int main() {
    shared_ptr<fpga_t> fpga{new fpga_t{
        .l = 1000,
        .p = 100000
    }};

    shared_ptr<accelerator_t> a0{new accelerator_t{
        .ca = 25,
        .o = 30,
        .strict = false,
        .name = "a0"
    }};
    shared_ptr<accelerator_t> a1{new accelerator_t{
        .ca = 50,
        .o = 30,
        .strict = false,
        .name = "a1"
    }};
    shared_ptr<accelerator_t> a2{new accelerator_t{
        .ca = 25,
        .o = 30,
        .strict = false,
        .name = "a2"
    }};

    shared_ptr<computation_t> c0{new computation_t{ // big, good accel
        .priority = 1,
        .g = 100000,
        .cs = 100,
        .accelerators = {a0},
        .fpga = fpga
    }};
    shared_ptr<computation_t> c1{new computation_t{ // big, bad accel
        .priority = 2,
        .g = 100000,
        .cs = 100,
        .accelerators = {a1},
        .fpga = fpga
    }};
    shared_ptr<computation_t> c2{new computation_t{ // small, 2 accel
        .priority = 3,
        .g = 1000,
        .cs = 200,
        .accelerators = {a1, a2},
        .fpga = fpga
    }};

    system_t s{
        .fpga = fpga,
        .computations = {c0, c1, c2}
    };

    auto a = s.choose_one_accelerator(false);
    if (a)
        cout << a->name << " chosen" << endl;
    else
        cout << "No accelerator chosen" << endl;
}
