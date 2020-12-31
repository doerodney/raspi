#include <stdio.h>
#include "car.h"

int main(int argc, char** argv) {
  car_t car;

  car_construct(&car, "Subaru");
  car_refuel(&car, 100.0);
  printf("Car refueled.  Fuel level: %f\n", car.fuel);

  while (car.fuel > 0.0) {
    printf("Fuel level: %f\n", car.fuel);

    if (car.speed < 80.0) {
      car_accelerate(&car);
    } else {
      car_brake(&car);
    }
    printf("Speed: %f\n", car.speed);
  }

  printf("Fuel level: %f\n", car.fuel);
  while (car.speed > 0.0) {
    car_brake(&car);
    printf("Speed: %f\n", car.speed);
  }

  car_destruct(&car);
  return 0;
}

