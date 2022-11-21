#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
// first read input device
#define INPUT_DEVICE_LIST "/dev/input/event"
//실제 디바이스 드라이버 노드파일: 뒤에 숫자가 붙음., ex)/dev/input/event5
#define PROBE_FILE "/proc/bus/input/devices"
//PPT에 제시된 "이 파일을 까보면 event? 의 숫자를 알수 있다"는 바로 그 파일
