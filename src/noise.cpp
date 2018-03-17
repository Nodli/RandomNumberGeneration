#include <iostream>
#include <common.h>
#include <random.h>
#include <noise.h>

float* noise::white(uint& seed, uint steps, float* out){
  for(int istep = 0; istep != steps; ++istep){
    out[istep] = rand::lcg_range_float(-1.f, 1.f, seed);
  }
  return out;
}

float* noise::brownian(uint& seed, uint steps, float* out){
  float start = 0;
    for(int istep = 0; istep != steps; ++istep){
    start += rand::lcg_range_float(-1.f, 1.f, seed);
    out[istep] = start;
  }
  return out;
}

float* noise::brownian_min_max(float min, float max, float amplitude,
                                uint& seed, uint steps, float* out){
  float start = 0.5f * (min + max);
  for(int istep = 0; istep != steps; ++istep){
    float rnumber;
    do{
      rnumber = rand::lcg_range_float(- amplitude / 2.f, amplitude / 2.f, seed);
    } while((start + rnumber) < min || (start + rnumber) > max);
    start += rnumber;
    out[istep] = start;
  }
  return out;
}

float* noise::perlin(uint& seed, uint steps, float* out){
  
}
