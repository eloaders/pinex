#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <linux/input.h>

int main(int argc, char** argv) {
    uint8_t keys[128];
    int fd;

    fd = open("/dev/input/event0", O_RDONLY);
    for (;;) {
        memset(keys, 0, 128);
        ioctl (fd, EVIOCGKEY(sizeof keys), keys);

        int i, j;
        for (i = 0; i < sizeof keys; i++)
            for (j = 0; j < 8; j++)
                if (keys[i] & (1 << j))
                    printf ("key code %d\n", (i*8) + j);
    }

    return 0;
}
