__kernel void gravity(__global const int *V, __global const int *G) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
 
    // Do the operation
}