__kernel void gravity(__global const float *G, __global float *V) {
    
    // Get the index of the current element to be processed
    int i = get_global_id(0);
 
    // Do the operation
    V[i*3] = V[i*3] + G[0];
    V[i*3+1] = V[i*3+1] + G[1];
    V[i*3+2] = V[i*3+2] + G[2];
}