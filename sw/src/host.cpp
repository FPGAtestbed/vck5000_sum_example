#define _GLIBCXX_USE_CXX11_ABI 0

#include "experimental/xrt_kernel.h"
#include "experimental/xrt_uuid.h"
#include <stdio.h>
#include <sys/time.h>

#define DATA_SIZE 10
#define DEVICE_ID   0

static void init_problem();

float * input_data, *result_data;

int main(int argc, char * argv[]) {   
  input_data=new float[DATA_SIZE];
  result_data=new float[1];
  init_problem();
  
  std::string xclbin_file=std::string(argv[1]);
  
  std::cout << "Load " << xclbin_file << std::endl;
  xrt::device device = xrt::device(DEVICE_ID);
  xrt::uuid xclbin_uuid = device.load_xclbin(xclbin_file);
  
  std::cout << "Create kernels" << std::endl;
  xrt::kernel sum_kernel = xrt::kernel(device, xclbin_uuid, "sum_kernel");
  
  // get memory bank groups for device buffer
  xrtMemoryGroup bank_input  = sum_kernel.group_id(0);
  xrtMemoryGroup bank_result  = sum_kernel.group_id(1);
  
  // create device buffer objects
  std::cout << "Create input and output device buffers for JPEG decoder" << std::endl;
  xrt::bo input_buffer  = xrt::bo(device, DATA_SIZE * sizeof(float),    xrt::bo::flags::normal, bank_input);
  xrt::bo result_buffer   = xrt::bo(device, 1*sizeof(float), xrt::bo::flags::normal, bank_result);
  
  // create JPEG kernel runner instance
  std::cout << "Create runner" << std::endl;
  xrt::run run_kernel(sum_kernel); 

  // set jpeg kernel arguments
  run_kernel.set_arg(0, input_buffer);
  run_kernel.set_arg(1, result_buffer);
  //run_kernel.set_arg(2, 50.0);    
  //run_kernel.set_arg(3, DATA_SIZE);
  
  std::cout << "Transfer data to device... "; 
  input_buffer.write(input_data);  
  input_buffer.sync(XCL_BO_SYNC_BO_TO_DEVICE);
  std::cout << "Done" << std::endl;
  
  std::cout << "Run kernel... " ;
  run_kernel.start();
  run_kernel.wait();
  std::cout << "Finish" << std::endl; 
  
  std::cout << "Transfer Info data to host... ";
  result_buffer.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
  result_buffer.read(result_data);
  std::cout << "Done" << std::endl;   

  printf("Data is %f\n", result_data[0]);
  
  return 0;
}

static void init_problem() {
	unsigned int i;
  for (i=0;i<DATA_SIZE;i++) {
        input_data[i]=i;
   }
}
