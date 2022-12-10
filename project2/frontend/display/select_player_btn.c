    #include "../../device/libs/button.h"
    #include "select_player_btn.h"
    // button start
    
    int select_player(int argc, char *argv[])
    {
        int msgID = buttonInit();
        printf("buttonInit . . .\n");

        BUTTON_MSG_T buttonMsg;
        int recievedVal = 0;
        PLAYER=0;
        buttonMsg.keyInput=0;
        
        while (1)
        {
            recievedVal = msgrcv(msgID, &buttonMsg, sizeof(buttonMsg) - 4, 0, 0);
            //printf("i'm in while... key=%d\n", buttonMsg.keyInput);
            switch (buttonMsg.keyInput)
            {
            case KEY_VOLUMEUP:
                PLAYER=0;
                break;
            case KEY_HOME:
                PLAYER=1;
                break;                 
            case KEY_SEARCH:
                PLAYER=0;
                break;
            case KEY_BACK:
                PLAYER=2;
                break;
            case KEY_MENU:
                PLAYER=0;
                break;
            case KEY_VOLUMEDOWN:
                PLAYER=0;
                break;
            
            printf("%d // ",PLAYER);
        }

        if (buttonMsg.pressed)
        {
            printf("select ");
        }
        else
        {
            printf("select_player fin\n");
	        if(PLAYER==1){
                printf("Your mari\n");
                return 1;
            }
            else if(PLAYER==2){
            printf("Your maru\n");
            return 2;
	        }
            
    }

    }
    printf("exit 실행...?\n");
    buttonExit();

     
    }


