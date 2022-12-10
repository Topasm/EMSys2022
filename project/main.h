#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include "device/driver.h"
#include "frontend/display/move_left.h"
#include "frontend/display/menu.h"
#include "device/libs/button.h"
#include "backend/PEobject.h"
#include "backend/PEcollide.h"
#include "backend/PEworld.h"
#include "device/libs/gyro.h"
#include "device/Server.h"
#include "device/Client.h"


object *ball;
object *mari_obj;
object *maru_obj;
