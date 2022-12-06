#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../libfbdev/libfbdev.h"
#include "../lodepng/lodepng.h"
#include "../../device/libs/gyro.h"
#include "drawLCD.h"




//player 변수
int player = 1; //1p or 2p
int x1=0, x2=520;
int dx1=0, dx2=0; //하나는 본인 키트에서 dx 받기 / 하나는 상대방 키트의 dx. 

int move_left(void)
{   
   
   while (1)
   {
        //1p: player==1
        if(player==1)
        {
        	update_background();
          	update_mari(x1,200);
            update_maru(x2,200);
          	update_screen();

            //mari
            if(x1>=240)   //not to over net
          	{
         		printf("mari saturation\n");
         		dx1=get_dx();
         		if(dx1>0)
            		x1=x1-dx1;
         		else
            		x1=295;
          	}   

          	else if(x1<=0) // not to over left wall
          	{
         		printf("mari saturation\n");
         		dx1=get_dx();
         		if(dx1<0)
            		x1=x1-dx1;
         		else
            		x1=0;
          	}

            else    //normal
          	{
         		printf("%d\n",x1);
         		dx1=get_dx();
         		x1=x1-dx1;
         		printf("%d, %d\n",x1,dx1);
          	}

        //maru
        	if(x2<=520)  //not to over net
        	{
        		printf("maru saturation\n");
            	dx2=get_dx();
            	if(dx2<0)
                	x2=x2-dx2;
            	else
                	dx2=520;
        	}

        	else if(x2>=830)  //not to over right wall
        	{
            	printf("maru saturation\n");
            	dx2=get_dx();
         		if(dx2>0)
            		x2=x2-dx2;
         		else
            		x2=830;
        	}

        	else    //normal
        	{
        		printf("%d\n",x1);
         		dx2=get_dx();
         		x2=x2-dx2;
         		printf("%d, %d\n",x2,dx2);
        	}


        }

        /* //2p: player==2
        else
        {
            update_background();
          update_mari(x1,200);
            update_maru(x2,200);
          update_screen();

            //maru
            if(x2<=300)  //not to over net
            {
            printf("maru saturation\n");
            dx2=get_dx();
            if(dx2<0)
                x2=x2-dx2;
            else
                dx2=300;
            }

            else if(x2>=550)  //not to over right wall
            {
            printf("maru saturation\n");
            dx2=get_dx();
         if(dx2>0)
            x2=x2-dx2;
         else
            x2=550;
            }

            else    //normal
          {
         printf("%d\n",x1);
         dx2=get_dx();
         x2=x2-dx2;
         printf("%d, %d\n",x2,dx2);
          }

            //mari
            if(x1>=240)   //not to over net
          {
         printf("mari saturation\n");
         dx1=get_dx();
         if(dx1>0)
            x1=x1-dx1;
         else
            x1=295;
          }   

          else if(x1<=0) // not to over left wall
          {
         printf("mari saturation\n");
         dx1=get_dx();
         if(dx1<0)
            x1=x1-dx1;
         else
            x1=0;
          }

            else    //normal
          {
         printf("%d\n",x1);
         dx1=get_dx();
         x1=x1-dx1;
         printf("%d, %d\n",x1,dx1);
          }

        }    */
   }
   fb_close();
   return 0;
}


//origianl code
/* int move_left(void)
{	
	int x=0;
	int dx=0;
	while (1)
	{
		
		update_background();
		update_mari(x,200);
		update_screen();

		if(x>=240)	
		{
			printf("saturation\n");
			dx=get_dx();
			if(dx>0)
				x=x-dx;
			else
				x=295;
		}		
		else if(x<=0)
		{
			printf("saturation\n");
			dx=get_dx();
			if(dx<0)
				x=x-dx;
			else
				x=0;
		}
		else
		{
			printf("%d\n",x);
			dx=get_dx();
			x=x-dx;
			printf("%d, %d\n",x,dx);
		}
	}
	fb_close();
	return 0;
} */
