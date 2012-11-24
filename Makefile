CC = avr-gcc
LE = avr-gcc
OBJCOPY = avr-objcopy

FILES = ./src/controllers/source/main_module/main.c ./src/controllers/source/comm_module/comm_module.c ./src/controllers/source/protocols/ctrl_protocol.c ./src/controllers/source/protocols/info_protocol.c

OFILES = ./main.o ./comm_module.o ./ctrl_protocol.o ./info_protocol.o

EFILES = loopback.elf

HFILES = loopback.hex

OUT_DIR=./run
#OUT_EXE = $(addprefix $(OUT_DIR)/,server)
CFLAGS= -Wall -g -Os
LDFLAGS= -g 
OCFLAGS = -j .text -j .data -O ihex

MMCU = -mmcu=atmega8515

LEDS_INFO_FILES = ./src/controllers/source/utils/leds.c ./src/controllers/source/comm_module/info_module/leds_info_module.c 
LEDS_INFO_OBJ = ./leds.o ./leds_info_module.o

SWS_SEN_FILES = ./src/controllers/source/utils/switches.c ./src/controllers/source/sense_module/sw_sense_module.c
SWS_SEN_OBJ = ./switches.o ./sw_sense_module.o

USART_CTRL_FILES = ./src/controllers/source/utils/usart.c ./src/controllers/source/comm_module/ctrl_module/usart_ctrl_module.c
USART_CTRL_OBJ = ./usart.o ./usart_ctrl_module.o

stk_version: $(FILES)
	echo @@@@@@@@@@@@@@@@@@ COMPILING PROJECT @@@@@@@@@@@@@@@@@@
	$(CC) $(CFLAGS) $(MMCU) -c $(FILES) $(LEDS_INFO_FILES) $(SWS_SEN_FILES) $(USART_CTRL_FILES)
	echo @@@@@@@@@@@@@@@@@@@ LINKING PROJECT @@@@@@@@@@@@@@@@@@@ 
	$(LE) $(LDFLAGS) $(MMCU) -o $(EFILES) $(OFILES) $(LEDS_INFO_OBJ) $(SWS_SEN_OBJ) $(USART_CTRL_OBJ)
	echo @@@@@@@@@@@@@ CREATING OBJECT CODE PROJECT @@@@@@@@@@@@ 
	$(OBJCOPY) $(OCFLAGS) $(EFILES) $(LEDS_INFO_ELF) $(SWS_SEN_ELF) $(USART_CTRL_ELF) $(HFILES)
	echo @@@@@@@@@@@@@@@@@@ UPLOADING PROJECT @@@@@@@@@@@@@@@@@@ 
	avrdude -c stk500v2 -p m8515 -P /dev/ttyUSB0 -U flash:w:$(EFILES)


clean:
	rm -f *.o *.elf core

rebuild: clean build
