    #include "../../device/libs/button.h"
    #include "select_player_btn.h"
    // button start



    int select_player(int argc, char *argv[])
    {
        int msgID = buttonInit();
        printf("buttonInit . . .\n");

        BUTTON_MSG_T buttonMsg;
        int recievedVal = 0;


        while (1)
        {
            recievedVal = msgrcv(msgID, &buttonMsg, sizeof(buttonMsg) - 4, 0, 0);
        
            switch (buttonMsg.keyInput)
            {
            case KEY_VOLUMEUP:
                printf("Volume up key):");
                break;
            case KEY_HOME:
                printf("PALYER 1:");
                break;
            case KEY_SEARCH:
                printf("Search key):");
                break;
            case KEY_BACK:
                printf("PLAYER 2:");
                break;
            case KEY_MENU:
                printf("Menu key):");
                break;
            case KEY_VOLUMEDOWN:
                printf("Volume down key):");
                break;
        }

        if (buttonMsg.pressed)
        {
            printf("select ");
        }
        else
        {
            printf("complete\n"); 
        }

    }
    buttonExit();

        
    }


	