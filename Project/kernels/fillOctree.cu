#include <stdio.h>
#include <cuda_runtime.h>
#include "fillOctree.cuh"

surface<void, cudaSurfaceType3D> surfRef;

__global__
void testFilling(dim3 texture_dim)
{
    int x = blockIdx.x*blockDim.x + threadIdx.x;
    int y = blockIdx.y*blockDim.y + threadIdx.y;
    int z = blockIdx.z*blockDim.z + threadIdx.z;

    if(x >= texture_dim.x || y >= texture_dim.y || z >= texture_dim.z)
    {
        return;
    }

    float4 element = make_float4(1.0f, 1.0f, 1.0f, 1.0f);
    surf3Dwrite(element, surfRef, x*sizeof(float4), y, z);
}

cudaError_t updateBrickPool(cudaArray_t &brickPool, dim3 textureDim)
{
    const surfaceReference* surfRefPtr;
    cudaGetSurfaceReference(&surfRefPtr, "surfRef");
    cudaChannelFormatDesc channelDesc;
    cudaGetChannelDesc(&channelDesc, brickPool);
    cudaBindSurfaceToArray(&surfRef, brickPool, &channelDesc);

    dim3 block_dim(8, 8, 6);
    dim3 grid_dim(textureDim.x/block_dim.x, textureDim.y/block_dim.y, textureDim.z/block_dim.z);
    testFilling<<<grid_dim, block_dim>>>(textureDim);
    printf("ich fülle den brickpool..\n");
}

void updateNodePool(cudaArray_t &voxel)
{
    printf("ich fülle den nodepool..\n");
}