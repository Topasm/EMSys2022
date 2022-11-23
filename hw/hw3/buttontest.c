#include "button.h"
int msgID = 0;

int main(int argc, char *argv[])
{

    msgID = buttonInit();
    printf("buttondriver\n");

    BUTTON_MSG_T buttonMsg;
    int recievedVal = 0;

    while (1)
    {
        recievedVal = msgrcv(msgID, &buttonMsg, sizeof(buttonMsg) - 4, 0, IPC_NOWAIT);
        if (recievedVal == -1)
        {
            break;
        }
    }

    while (1)
    {
        recievedVal = msgrcv(msgID, &buttonMsg, sizeof(buttonMsg) - 4, 0, 0);
        if (recievedVal < 0)
        {
            printf("error");
        }

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
        if (buttonMsg.pressed)
        {
            printf("pressed\n");
        }
        else
        {
            printf("released\n");
        }
    }
    buttonExit();
    return 0;
}
