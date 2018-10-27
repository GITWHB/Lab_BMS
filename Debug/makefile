################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 18
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
TestBorad.elf \

EXECUTABLES_QUOTED += \
"TestBorad.elf" \

EXECUTABLES_OS_FORMAT += \
TestBorad.elf \

SECONDARY_SIZE += \
TestBorad.siz \

SECONDARY_SIZE_QUOTED += \
"TestBorad.siz" \

SECONDARY_SIZE_OS_FORMAT += \
TestBorad.siz \


# All Target
all: warning-messages explicit-dependencies TestBorad.elf secondary-outputs

# Tool invocations
TestBorad.elf: $(OBJS) D:/MPC5744P/Project/Power1.2/TestBorad/Project_Settings/Linker_Files/57xx_flash.ld D:/MPC5744P/Project/Power1.2/TestBorad/Project_Settings/Linker_Files/libs.ld $(OSPT) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #19 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	powerpc-eabivle-gcc -o "TestBorad.elf" "@TestBorad.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED) $(OSPT)
	@echo 'Finished building target: $@'
	@echo ' '

TestBorad.siz: $(EXECUTABLES)
	@echo 'Executing target #20 $@'
	@echo 'Invoking: Standard S32DS Print Size'
	powerpc-eabivle-size --format=berkeley $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*/*.d  ./*/*/*.o ./*/*.o  $(SECONDARY_SIZE_QUOTED) $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

