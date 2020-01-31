#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void INThandler(){
        exit(0);
}

int main()
{
        char devname[] = "/dev/input/event0";
        int device = open(devname, O_RDONLY);
        struct input_event ev;

        signal(SIGINT, INThandler);

        while(1)
        {
                read(device,&ev, sizeof(ev));
                if(ev.type == 1 && ev.value == 1){
                        printf("Key: %i State: %i\n",ev.code,ev.value);
			printf("%ld,%ld %s %s %d\n",ev.time.tv_sec, ev.time.tv_usec, ev.type, ev.code, ev.value);
                }
        }
}
