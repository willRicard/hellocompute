kernel void add(device float *x,
                device const float *y,
                uint index [[thread_position_in_grid]])
{
  x[index] = x[index] + y[index];
}
