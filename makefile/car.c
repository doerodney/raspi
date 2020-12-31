#include <string.h>

#include "car.h"

void car_construct(car_t* car, const char* name) {
  strcpy(car->name, name);
  car->speed = 0.0;
  car->fuel = 0.0;
}

void car_destruct(car_t* car) {
  /*  Nothing to do */
}

void car_accelerate(car_t* car) {
  car->speed += 0.05;
  car->fuel -= 1.0;
  if (car->fuel < 0.0) {
    car->fuel = 0.0;
  }
}

void car_brake(car_t* car) {
  car->speed -= 0.07;
  if (car->speed < 0.0) {
    car->speed = 0.0;
  }

  car->fuel -= 2.0;
  if (car->fuel < 0.0) {
    car->fuel = 0.0;
  }
}

void car_refuel(car_t* car, double amount) {
  car->fuel += amount;
}
