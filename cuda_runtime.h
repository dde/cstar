#define cudaHostToDevice 1
#define cudaDeviceToHost 1
#define cudaDeviceToDevice 0
struct threadIdx
{
    int x;
    int y;
};
struct blockDim
{
    int x;  /* number of thread rows in a block */
    int y;  /* number of threads in a block row */
};
struct blockIdx
{
    int x;
    int y;
};
struct gridDim
{
    int x;  /* number of block rows in a grid */
    int y;  /* number of blocks in a grid row */
};
void *memcpy(void *dev, void *hst, int len);
void cudaMalloc(void **mem, int sz)
{
  void *bytes;
  bytes = malloc(sz);
  *mem = bytes;
}
void cudaFree(void *mem)
{
  free(mem);
}
void cudaMemcpy(void *dev, void *hst, int sz, int dir)
{
    memcpy(dev, hst, sz);
}
