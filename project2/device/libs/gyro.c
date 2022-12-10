#include "gyro.h"

int dx;

int get_dx (void)
{
int fd = 0;
FILE *fp = NULL;

//Gyroscope



    fd = open (GYROPATH "enable",O_WRONLY);
    dprintf (fd,"1");
    close(fd);
    fp = fopen (GYROPATH "data", "rt");
    int gyro[3];
    fscanf(fp,"%d, %d, %d",&gyro[0],&gyro[1],&gyro[2]);
    dx=gyro[1]/10;
    fclose(fp);


return dx;
}
