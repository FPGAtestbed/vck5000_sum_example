#ifndef FUNCTION_KERNELS_H
#define FUNCTION_KERNELS_H

#include "aie_api/aie.hpp"
#include "aie_api/aie_adf.hpp"

void sum_kernel_fn_stream(input_stream<float>*, output_stream<float>*, input_stream<int32>*);

#endif
