#ifndef FUNCTION_KERNELS_H
#define FUNCTION_KERNELS_H

#include "aie_api/aie.hpp"
#include "aie_api/aie_adf.hpp"

#define SIZE 10

void sum_kernel_fn(input_window<float> * in, output_window<float> * out);
void sum_kernel_fn_stream(input_stream<float> * in, output_window<float> * out);

#endif
