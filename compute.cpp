#include "compute.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_SOURCE_SIZE (0x100000)

char* readFile(const char* filename, size_t &size) {
    FILE *fp;
    char *source_str;

    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
	source_str = new char[MAX_SOURCE_SIZE];
    size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );
	return source_str;
}

cl_device_id getCLDeviceID() {
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1, 
            &device_id, &ret_num_devices);
    
    return device_id;
}

cl_context createCLContext(cl_device_id device_id) {
    cl_int ret;
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
    return context;
}

cl_command_queue createCLCommandQueue(cl_context context, cl_device_id device_id) {
    cl_int ret;
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    return command_queue;
}

cl_mem createCLBuffer(cl_context context, size_t size) {
    cl_int ret;
    cl_mem mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, &ret);
    return mem_obj;
}

void uploadDataToCLBuffer(cl_command_queue command_queue, cl_mem buffer, void* data, size_t size) {
    cl_int ret;
    ret = clEnqueueWriteBuffer(command_queue, buffer, CL_TRUE, 0, size, data, 0, NULL, NULL);
}

cl_program createCLProgram(cl_context context, cl_device_id device_id, const char* source_str, size_t source_size) {
    cl_int ret;
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    return program;
}

cl_kernel getKernel(cl_program program, const char* name) {
    cl_int ret;
    cl_kernel kernel = clCreateKernel(program, name, &ret);
    return kernel;
}

void setCLKernelArg(cl_kernel kernel, cl_uint index, cl_mem buffer) {
    cl_int ret;
    ret = clSetKernelArg(kernel, index, sizeof(cl_mem), (void *)&buffer);
}

void downloadDataFromCLBuffer(cl_command_queue command_queue, cl_mem buffer, void *data, size_t size) {
    cl_int ret;
    ret = clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0, size, data, 0, NULL, NULL);
}

void executeCLKernel(cl_command_queue command_queue, cl_kernel kernel, size_t global_item_size, size_t local_item_size) {
    cl_int ret;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
            &global_item_size, &local_item_size, 0, NULL, NULL);
}

void flushCLCommandQueue(cl_command_queue command_queue) {
    cl_int ret;
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
}

void cleanCLCommandQueue(cl_command_queue command_queue) {
    cl_int ret;
    ret = clReleaseCommandQueue(command_queue);
}

void cleanCLKernel(cl_kernel kernel) {
    cl_int ret;
    ret = clReleaseKernel(kernel);
}

void cleanCLProgram(cl_program program) {
    cl_int ret;
    ret = clReleaseProgram(program);
}

void cleanCLBuffer(cl_mem buffer) {
    cl_int ret;
    ret = clReleaseMemObject(buffer);
}

void cleanCLContext(cl_context context) {
    cl_int ret;
    ret = clReleaseContext(context);
}
