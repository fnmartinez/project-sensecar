################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
sensecar_arduino2.lss \

FLASH_IMAGE += \
sensecar_arduino2.hex \

EEPROM_IMAGE += \
sensecar_arduino2.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: sensecar_arduino2.elf secondary-outputs

# Tool invocations
sensecar_arduino2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ --cref -s -Os -o"sensecar_arduino2.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm -Wl,-Map,sensecar_arduino2.map,--cref -L"/home/facundo/workspace/ArduinoEthernet/Release" -mmcu=atmega2560
	@echo 'Finished building target: $@'
	@echo ' '

sensecar_arduino2.lss: sensecar_arduino2.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S sensecar_arduino2.elf  >"sensecar_arduino2.lss"
	@echo 'Finished building: $@'
	@echo ' '

sensecar_arduino2.hex: sensecar_arduino2.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex sensecar_arduino2.elf  "sensecar_arduino2.hex"
	@echo 'Finished building: $@'
	@echo ' '

sensecar_arduino2.eep: sensecar_arduino2.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex sensecar_arduino2.elf  "sensecar_arduino2.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: sensecar_arduino2.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 sensecar_arduino2.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) sensecar_arduino2.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
