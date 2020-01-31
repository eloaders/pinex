DEBUG = -O3
CC = gcc
INCLUDE = -I./mongoose -I./ -I/usr/include -I/opt/vc/include -I/opt/vc/include/interface/vmcs_host/linux -I/opt/vc/include/interface/vcos/pthreads
DEFINES = -DRPI -DMG_ENABLE_SSL
CFLAGS = $(DEBUG) -Wall $(INCLUDE) -g $(DEFINES)
LDFLAGS = -L/usr/lib -L/opt/vc/lib
LDLIBS = -lcjson -ldl -lssl -lcrypto -lsndio -lbcm_host -lvchostif -lvcos -lvchiq_arm -pthread -lrt -lwiringPi -lwiringPiDev

##INCLUDES+=PINEX_WEB_INCLUDES
##CFLAGS+=-DMG_ENABLE_SSL  -Wall $(INCLUDES) -g -O3

##CFLAGS += -pipe -marm -mfpu=vfp -mtune=arm1176jzf-s -march=armv6zk -mabi=aapcs-linux -mfloat-abi=hard

SRC =	cpu_usage.c \
	DS3231.c \
	i2c.c \
	mem_info.c \
	raspberry_pi_revision.c \
	mongoose/mongoose.c


OBJ = $(SRC:.c=.o)

BINS = pi-nex-web

all: $(BINS)

clean:
	@echo "Cleaning directory..."
	$(RM) $(BINS)

pi-nex-web: pi-nex-web.c $(OBJ)
	@echo [Building $@]
	@$(CC) $(CFLAGS) -o $@ pi-nex-web.c $(OBJ) $(LDFLAGS) $(LDLIBS) -lm -I .
