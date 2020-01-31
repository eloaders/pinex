##
## Makefile for GUIslice library - LINUX
## - Calvin Hass
## - https://www.impulseadventure.com/elec/guislice-gui.html
## - https://github.com/ImpulseAdventure/GUIslice
##
## NOTE: This Makefile handles both SDL1.2 and SDL2 compilation.
##       A simpler Makefile can be used if this flexibility is
##       not required.

DEBUG = -O3
CC = gcc
INCLUDE = -I./mongoose -I./CONFIG -I./MEMINFO -I./CPUUSAGE -I./DS3231 -I./GUIslice/src -I/usr/include -I/opt/vc/include -I/opt/vc/include/interface/vmcs_host/linux -I/opt/vc/include/interface/vcos/pthreads
CFLAGS = $(DEBUG) -Wall $(INCLUDE) -Winline -pipe -g
LDFLAGS = -L/usr/lib -L/opt/vc/lib
LDLIBS = -lssl -lcrypto -ldl -lsndio -lbrcmEGL -lbrcmGLESv2 -lbcm_host -lvchostif -lvcos -lvchiq_arm -pthread -lrt 
CFLAGS += -DMG_ENABLE_SSL 

GSLC_CORE = ./GUIslice/src/GUIslice.c ./GUIslice/src/GUIslice_ex.h ./GUIslice/src/GUIslice_config_linux.h

GSLC_DRV := SDL1
#GSLC_DRV := SDL2

GSLC_LDLIB_EXTRA := -lm -lts -lwiringPi -lwiringPiDev -lconfig 
DS3231 = ./DS3231/DS3231.c ./DS3231/i2c.c
CPUUSAGE = ./CPUUSAGE/cpu_usage.c
MEMINFO = ./MEMINFO/mem_info.c
CONFIG = ./CONFIG/config.c
#MONGOOSE = ./mongoose/mongoose.c

COMPONENTS = $(DS3231) $(CPUUSAGE) $(MEMINFO) $(CONFIG)
#COMPONENTS += $(MONGOOSE)
# === SDL1.2 ===
ifeq (SDL1,${GSLC_DRV})
  $(info GUIslice driver mode: SDL1)
  GSLC_SRCS = ./GUIslice/src/GUIslice_drv_sdl.c
  # - Add extra linker libraries if needed
  LDLIBS += -lSDL -lSDL_ttf ${GSLC_LDLIB_EXTRA}
endif

# === SDL2.0 ===
ifeq (SDL2,${GSLC_DRV})
  $(info GUIslice driver mode: SDL2)
  GSLC_SRCS = ./GUIslice/src/GUIslice_drv_sdl.c
  # - Add extra linker libraries if needed
  LDLIBS += `sdl2-config --libs --cflags` -lSDL2_ttf -lSDL2_image ${GSLC_LDLIB_EXTRA}
endif

SRC =   pi-nex.c

OBJ = $(SRC:.c=.o)

BINS = $(SRC:.c=)

all: $(BINS)

clean:
	@echo "Cleaning directory..."
	$(RM) $(BINS)

pi-nex: pi-nex.c $(GSLC_CORE) $(GSLC_SRCS) $(COMPONENTS)
	@echo [Building $@]
	@$(CC) $(CFLAGS) -o $@ pi-nex.c $(GSLC_CORE) $(GSLC_SRCS) $(COMPONENTS) $(LDFLAGS) $(LDLIBS) -lm -I .
