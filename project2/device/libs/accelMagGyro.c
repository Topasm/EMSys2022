#include "accelMagGyro.h"

//int fd=0;
//FILE *fp=NULL;

int fd_accel = 0;
int fd_mag = 0;
int fd_gyro = 0;

FILE *fp_accel = NULL;
FILE *fp_mag = NULL;
FILE *fp_gyro = NULL;


int init_accel(void){
    //Accelerometer
    fd_accel = open (ACCELPATH "enable",O_WRONLY);
    dprintf (fd_accel,"1");
    close(fd_accel);
    fp_accel = fopen (ACCELPATH "data", "rt");
    int accel[3];
    fscanf(fp_accel,"%d, %d, %d",&accel[0],&accel[1],&accel[2]);
    printf ("I read Accel %d, %d, %d\r\n",accel[0],accel[1],accel[2]);
    fclose(fp_accel);
    return 0;
}

int init_mag(void){
    //Magnetometer
    fd_mag = open (MAGNEPATH "enable",O_WRONLY);
    dprintf (fd_mag,"1");
    close(fd_mag);
    fp_mag = fopen (MAGNEPATH "data", "rt");
    int magne[3];
    fscanf(fp_mag,"%d, %d, %d",&magne[0],&magne[1],&magne[2]);
    printf ("I read Magneto %d, %d, %d\r\n",magne[0],magne[1],magne[2]);
    fclose(fp_mag);
    return 0;
}

int init_gyro(void){
    //Gyroscope
    fd_gyro = open (GYROPATH "enable",O_WRONLY);
    dprintf (fd_gyro,"1");
    close(fd_gyro);
    fp_gyro = fopen (GYROPATH "data", "rt");
    int gyro[3];
    fscanf(fp_gyro,"%d, %d, %d",&gyro[0],&gyro[1],&gyro[2]);
    printf ("I read Gyroscope %d, %d, %d\r\n",gyro[0],gyro[1],gyro[2]);
    fclose(fp_gyro);
    return 0;
}

