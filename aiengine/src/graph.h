#include <adf.h>
#include "kernel.h"

using namespace adf;

class simpleGraph : public graph {
private:
  kernel sum_kernel;
public:
  input_plio in;
  output_plio out;

  simpleGraph(){

	sum_kernel = kernel::create(sum_kernel_fn);

    in = input_plio::create("s0", plio_32_bits, "data/input.txt");
    out = output_plio::create("s1", plio_32_bits, "data/output.txt");
    connect< window<4*SIZE> > net0 (in.out[0], sum_kernel.in[0]);
    //connect<stream>(in.out[0], sum_kernel.in[0]);
    connect< window<4> > net1 (sum_kernel.out[0], out.in[0]);

    source(sum_kernel) = "kernel.cpp";

    runtime<ratio>(sum_kernel) = 0.9;
  }
};
