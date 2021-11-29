#pragma once

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

char* readFile(const char* filename, size_t &size);
cl_device_id getCLDeviceID();
cl_context createCLContext(cl_device_id device_id);
cl_command_queue createCLCommandQueue(cl_context context, cl_device_id device_id);
cl_mem createCLBuffer(cl_context context, size_t size);
void uploadDataToCLBuffer(cl_command_queue command_queue, cl_mem buffer, void* data, size_t size);
cl_program createCLProgram(cl_context context, cl_device_id device_id, const char* source_str, size_t source_size);
cl_kernel getKernel(cl_program program, const char* name);
void setCLKernelArg(cl_kernel kernel, cl_uint index, cl_mem buffer);
void downloadDataFromCLBuffer(cl_command_queue command_queue, cl_mem buffer, void* data, size_t size);
void executeCLKernel(cl_command_queue command_queue, cl_kernel kernel, size_t global_item_size, size_t local_item_size);
void flushCLCommandQueue(cl_command_queue command_queue);
void cleanCLCommandQueue(cl_command_queue command_queue);
void cleanCLKernel(cl_kernel kernel);
void cleanCLProgram(cl_program program);
void cleanCLBuffer(cl_mem buffer);
void cleanCLContext(cl_context context);
