    #include "../../device/libs/button.h"
    #include "select_player_btn.h"
    // button start
    
    int select_player(int argc, char *argv[])
    {
        int msgID = buttonInit();
        printf("buttonInit . . .\n");

        BUTTON_MSG_T buttonMsg;
        int recievedVal = 0;
        int player=1;
        buttonMsg.keyInput=0;
        
        while (1)
        {
            recievedVal = msgrcv(msgID, &buttonMsg, sizeof(buttonMsg) - 4, 0, 0);
            printf("i'm in while... key=%d\n", buttonMsg.keyInput);
            switch (buttonMsg.keyInput)
            {
            case KEY_VOLUMEUP:
                player=0;
                break;
            case KEY_HOME:
                player=1;
                break;                 
            case KEY_SEARCH:
                player=0;
                break;
            case KEY_BACK:
                player=2;
                break;
            case KEY_MENU:
                player=0;
                break;
            case KEY_VOLUMEDOWN:
                player=0;
                break;
            
            printf("%d // ",player);
        }

        if (buttonMsg.pressed)
        {
            printf("select ");
        }
        else
        {
            if(player==1||player==2){
                printf("\nfinal player: %d ", player);
                printf("complete\n"); 
                return player; 
            }
            
    }

    }
    printf("exit 실행...?\n");
    buttonExit();

     
    }

