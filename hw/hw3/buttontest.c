#include "button.h"
int msgID = 0;
//메시지를 받아서 작동하는듯
int main(int argc, char *argv[])
{

    msgID = buttonInit();

    BUTTON_MSG_T buttonMsg;
    int recievedVal = 0;
    recievedVal = msgrcv(msgID, &buttonMsg, sizeof(int), 0, 0);
    if(recievedVal <0)
    {printf("error");
    }

    while (1)
    {

        printf("EV_KEY(");
        switch (buttonMsg.keyInput)
        {
        case KEY_VOLUMEUP:
            printf("Volume up key):");
            break;
        case KEY_HOME:
            printf("Home key):");
            break;
        case KEY_SEARCH:
            printf("Search key):");
            break;
        case KEY_BACK:
            printf("Back key):");
            break;
        case KEY_MENU:
            printf("Menu key):");
            break;
        case KEY_VOLUMEDOWN:
            printf("Volume down key):");
            break;
        }
    }
    buttonExit();
    return 0;
}
