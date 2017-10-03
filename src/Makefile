PRU_COMPILER_DIR=/usr/share/ti/cgt-pru
PRU_PKG_INC_DIR=/opt/source/pru-software-support-package/include
PRU_C_FLAGS=--silicon_version=2 --hardware_mac=on -i$(PRU_COMPILER_DIR)/include -i$(PRU_COMPILER_DIR)/lib -i$(PRU_PKG_INC_DIR) -i$(PRU_PKG_INC_DIR)/am335x 

PRU_LD_FLAGS=-llibc.a

HOST_C_FLAGS += -Wall -g -O2 -mtune=cortex-a8 -march=armv7-a -I/usr/local/include -I../include
HOST_LD_FLAGS += -lprussdrv -lpthread

SOURCE_FILES =  .obj/Sampler.o StdDeviation.cpp PWM.cpp GPIO.cpp Butterworth.cpp util.cpp

FIND_ADDRESS_COMMAND=`dispru .obj/pru.elf | grep _c_int00 | cut -f1 -d\  `

.PHONY: all
all:
	# Compile pru.c into pro.obj
	clpru $(PRU_C_FLAGS) -c pru.c -fr=.obj

	# Link pru.obj with libraries and output pru.map and pru.elf
	clpru $(PRU_C_FLAGS) -z .obj/pru.obj $(PRU_LD_FLAGS) -m pru.map -o .obj/pru.elf AM3359_PRU.cmd

	# Convert pru.elf into text.bin and data.bin
	hexpru ./bin.cmd ./.obj/pru.elf

	# Find address of start of program and compile host program
	export START_ADDR=0x$(FIND_ADDRESS_COMMAND) && \
	g++ $(HOST_C_FLAGS) -DSTART_ADDR=`echo $$START_ADDR` -c -o .obj/Sampler.o Sampler.cpp && \
	g++ $(HOST_C_FLAGS) -o ../bin/SoakTest SoakTest.cpp $(SOURCE_FILES) $(HOST_LD_FLAGS) && \
	g++ $(HOST_C_FLAGS) -o ../bin/Calibrate Calibrate.cpp $(SOURCE_FILES) $(HOST_LD_FLAGS)

.PHONY: clean
clean:
	-rm -f *.obj
	-rm -f .obj/*
	-rm -f *.map
	-rm -f *.elf
	-rm -f *.bin
	-rm -f *.o
	-rm -f ../bin/SoakTest
	-rm -f ../bin/Calibrate
	-rm -f out.wav
	 
