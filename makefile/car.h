#ifndef INCLUDES_CAR_H
#define INCLUDES_CAR_H

typedef struct {
  char name[32];
  double speed;
  double fuel;
} car_t;

void car_construct(car_t* car, const char* name);
void car_destruct(car_t*);
void car_accelerate(car_t*);
void car_brake(car_t*);
void car_refuel(car_t*, double amount);

#endif
