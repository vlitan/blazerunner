#pragma once


void mpu_setup(int x_off, int y_off, int z_off,int z_accel);

void update_ypr(float* yaw, float* pitch, float* roll);
