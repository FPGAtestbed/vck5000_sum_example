#include "kernel.h"
#include "aie_api/aie.hpp"
#include "aie_api/aie_adf.hpp"
#include <aie_api/utils.hpp>

void sum_kernel_fn_stream(input_stream<float> * in, output_stream<float> * out, input_stream<int32>* number_elements) {
  float val=0;
  int32 numels=readincr(number_elements);
  int32 raw_addv=readincr(number_elements);

  float add_val=as_float(raw_addv); //or can use *((float*) &(raw_addv))
  aie::vector<float,8> rhs_numbers = aie::broadcast<float,8>(add_val);

  aie::vector<float,8> lhs_numbers;
  for (int i=0;i<numels;i++) {
    lhs_numbers.insert(0,readincr_v<4>(in));
    lhs_numbers.insert(1,readincr_v<4>(in));

    aie::vector<float,8> vadd=aie::add(lhs_numbers,rhs_numbers);

    // Printing useful for debugging
    //float* print_ptr =(float*)&vadd;
    //printf("%f %f\n", print_ptr[0],print_ptr[1]);

    writeincr(out, vadd.extract<4>(0));
    writeincr(out, vadd.extract<4>(1));
  }
}
