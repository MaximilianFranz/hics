// We can't define those parameters dynamically as we use
// offline compilation for the FPGA.
// Make sure the parameters match what's used in FpgaConvolutionFunction.
#define TS 32
#define WIDTH 4

__attribute__((reqd_work_group_size(TS/WIDTH, TS, 1)))

// Use wider data types
__kernel void GEMM4(const int M, const int N, const int K,
                    const __global float4* restrict A,
                    const __global float4* restrict B,
                    __global float4* C,
                    const __global float4* restrict D) {

    // Thread identifiers
    const int row = get_local_id(0); // Local row ID (max: TS/WIDTH)
    const int col = get_local_id(1); // Local col ID (max: TS)
    const int globalRow = (TS/WIDTH)*get_group_id(0) + row; // 0..M/WIDTH
    const int globalCol = TS*get_group_id(1) + col; // 0..N

    // Local memory to fit a tile of TS*TS elements of A and B
    __local float4 Asub[TS][TS/WIDTH];
    __local float4 Bsub[TS][TS/WIDTH];

    // Initialise the accumulation registers
    float4 acc = { 0.0f, 0.0f, 0.0f, 0.0f };

    // Loop over all tiles
    const int numTiles = K/TS;
    for (int t=0; t<numTiles; t++) {

        // Load one tile of A and B into local memory
        const int tiledRow = (TS/WIDTH)*t + row;
        const int tiledCol = TS*t + col;
        Asub[col][row] = A[tiledCol*(M/WIDTH) + globalRow];
        Bsub[col][row] = B[globalCol*(K/WIDTH) + tiledRow];

        // Synchronise to make sure the tile is loaded
        barrier(CLK_LOCAL_MEM_FENCE);

        // Perform the computation for a single tile
        float4 vecA, vecB;
        float valB;
        for (int k=0; k<TS/WIDTH; k++) {
            vecB = Bsub[col][k];
            for (int w=0; w<WIDTH; w++) {
                vecA = Asub[WIDTH*k + w][row];
                    switch (w) {
                        case 0: valB = vecB.x; break;
                        case 1: valB = vecB.y; break;
                        case 2: valB = vecB.z; break;
                        case 3: valB = vecB.w; break;
                    }
                    acc.x += vecA.x * valB;
                    acc.y += vecA.y * valB;
                    acc.z += vecA.z * valB;
                    acc.w += vecA.w * valB;
            }
        }

        // Synchronise before loading the next tile
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    // Store the final results in C
    C[globalCol*(M/WIDTH) + globalRow] = acc + D[globalRow];
}
