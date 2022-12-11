#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "../libfbdev/libfbdev.h"
#include "../lodepng/lodepng.h"
#include "../../device/libs/gyro.h"
#include "../../device/libs/led.h"
#include "drawLCD.h"



//player 변수
int player = 1; //1p or 2p
int x1=120, x2=700;
int dx1=0, dx2=0; //하나는 본인 키트에서 dx 받기 / 하나는 상대방 키트의 dx. 
SATU_MARI=4;
SATU_MARU=4;
int pre_satu_mari=4;
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
         		//printf("mari saturation\n");
         		dx1=get_dx();
         		if(dx1>0)
            		x1=x1-dx1;
         		else
            		x1=295;
          	}   

          	else if(x1<=0) // not to over left wall
          	{
         		//printf("mari saturation\n");
				    SATU_MARI--;	
				    SATU_MARU++;
         		dx1=get_dx();
         		if(dx1<0)
            		x1=x1-dx1;
         		else
            		x1=0;
          	}

            else    //normal
          	{
         		//printf("%d\n",x1);
         		dx1=get_dx();
         		x1=x1-dx1;
         		//printf("%d, %d\n",x1,dx1);
          	}

        //maru
        	if(x2<=520)  //not to over net
        	{
        		//printf("maru saturation\n");
            	dx2=get_dx();
            	if(dx2<0)
                	x2=x2-dx2;
            	else
                	dx2=520;
        	}

        	else if(x2>=830)  //not to over right wall
        	{
            	//printf("maru saturation\n");
				    SATU_MARI++;	
				    SATU_MARU--;
            	dx2=get_dx();
         		if(dx2>0)
            		x2=x2-dx2;
         		else
            		x2=830;
        	}

        	else    //normal
        	{
        		//printf("%d\n",x1);
         		dx2=get_dx();
         		x2=x2-dx2;
         		//printf("%d, %d\n",x2,dx2);
        	}
        }
		
		if(SATU_MARI==pre_satu_mari-1 || SATU_MARI==pre_satu_mari-1 || SATU_MARI==pre_satu_mari+2 || SATU_MARI==pre_satu_mari-2 )
		{
			x1=120;
			x2=700;
			pre_satu_mari=SATU_MARI;

			if(SATU_MARI==0)
      {
          dispaly_menu();
          sleep(3);
          SATU_MARI=4;
          pre_satu_mari=4;
          SATU_MARU=4;
      }
				

		}
		
   }
   fb_close();
   return 0;
}