#include "kernel.h"
#include "aie_api/aie.hpp"
#include "aie_api/aie_adf.hpp"

void sum_kernel_fn(input_window<float> * in, output_window<float> * out) {
	float val=0;
	for (int i=0;i<SIZE;i++) {
		float d=window_readincr(in);
		printf("%f\n", d);
		val+=d;
	}
	window_writeincr(out, val);
}

void sum_kernel_fn_stream(input_stream<float> * in, output_window<float> * out) {
	float val=10;
	for (int i=0;i<SIZE;i++) {
		float d=readincr(in);
		printf("%f\n", d);
		val+=d;
	}
	window_writeincr(out, val);
}
