#include <adf.h>
#include "kernel.h"

using namespace adf;

class simpleGraph : public graph {
private:
  kernel sum_kernel;
public:
  input_plio in, num_elements;
  output_plio out;

  simpleGraph(){
    sum_kernel = kernel::create(sum_kernel_fn_stream);

    in = input_plio::create("s0", plio_128_bits, "data/input.txt");
    num_elements  = input_plio::create("numels", plio_32_bits, "data/num_elements.txt");
    out = output_plio::create("s1", plio_128_bits, "data/output.txt");

    connect<stream>(in.out[0], sum_kernel.in[0]);
    connect<stream>(num_elements.out[0], sum_kernel.in[1]);
    connect<stream>(sum_kernel.out[0], out.in[0]);

    source(sum_kernel) = "kernel.cpp";

    runtime<ratio>(sum_kernel) = 0.9;
  }
};
