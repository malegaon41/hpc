#include <iostream>
#include <cuda_runtime.h>

using namespace std;

// CUDA Kernel
__global__ void vectorAdd(int *A, int *B, int *C, int n) {

    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n) {

        C[i] = A[i] + B[i];
    }
}

int main() {

    int n;

    cout << "Enter size of vectors: ";
    cin >> n;

    int size = n * sizeof(int);

    // Host arrays
    int *h_A = new int[n];
    int *h_B = new int[n];
    int *h_C = new int[n];

    cout << "Enter elements of Vector A:\n";

    for (int i = 0; i < n; i++) {

        cin >> h_A[i];
    }

    cout << "Enter elements of Vector B:\n";

    for (int i = 0; i < n; i++) {

        cin >> h_B[i];
    }

    // Device arrays
    int *d_A, *d_B, *d_C;

    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    // Copy data from CPU to GPU
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // Kernel Launch
    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    vectorAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, n);

    // Copy result back to CPU
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    // Output
    cout << "\nResult Vector:\n";

    for (int i = 0; i < n; i++) {

        cout << h_C[i] << " ";
    }

    // Free memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    delete[] h_A;
    delete[] h_B;
    delete[] h_C;

    return 0;
}