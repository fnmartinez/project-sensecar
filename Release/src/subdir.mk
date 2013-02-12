################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main.cpp 

OBJS += \
./src/main.o 

CPP_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/home/facundo/arduino-1.0.2/libraries/Ethernet/utility -I/home/facundo/arduino-1.0.2/libraries/Ethernet -I/home/facundo/arduino-1.0.2/libraries/SPI -I/home/facundo/arduino-1.0.2/hardware/arduino/variants/mega -I/home/facundo/arduino-1.0.2/hardware/arduino/cores/arduino -I"/home/facundo/workspace/sensecar_arduino2/hdr" -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


