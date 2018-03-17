#include <iostream>
#include <common.h>
#include <array.h>
#include <random.h>
#include <noise.h>

int main(){
  uint seed = rand::time_seed();
  float alt[1000u];
  noise::brownian_min_max(0.f, 20.f, 5, seed, 1000u, alt)[10];
  array::add(alt, 1000u, -10.f);
  array::display(alt, 1000u);

  return 0;
}
