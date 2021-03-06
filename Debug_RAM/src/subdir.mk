################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS_QUOTED += \
"../src/intc_sw_handlers.S" \

C_SRCS_QUOTED += \
"../src/MPC57xx__Interrupt_Init.c" \
"../src/SysClk.c" \
"../src/TB_25LC256.c" \
"../src/TB_ADC.c" \
"../src/TB_AnSPI.c" \
"../src/TB_CAN.c" \
"../src/TB_DS1302.c" \
"../src/TB_GPIO.c" \
"../src/TB_LTC6804.c" \
"../src/TB_PIT.c" \
"../src/TB_UART.c" \
"../src/Vector.c" \
"../src/intc_SW_mode_isr_vectors_MPC5744P.c" \
"../src/main.c" \

S_UPPER_SRCS += \
../src/intc_sw_handlers.S \

C_SRCS += \
../src/MPC57xx__Interrupt_Init.c \
../src/SysClk.c \
../src/TB_25LC256.c \
../src/TB_ADC.c \
../src/TB_AnSPI.c \
../src/TB_CAN.c \
../src/TB_DS1302.c \
../src/TB_GPIO.c \
../src/TB_LTC6804.c \
../src/TB_PIT.c \
../src/TB_UART.c \
../src/Vector.c \
../src/intc_SW_mode_isr_vectors_MPC5744P.c \
../src/main.c \

OBJS_OS_FORMAT += \
./src/MPC57xx__Interrupt_Init.o \
./src/SysClk.o \
./src/TB_25LC256.o \
./src/TB_ADC.o \
./src/TB_AnSPI.o \
./src/TB_CAN.o \
./src/TB_DS1302.o \
./src/TB_GPIO.o \
./src/TB_LTC6804.o \
./src/TB_PIT.o \
./src/TB_UART.o \
./src/Vector.o \
./src/intc_SW_mode_isr_vectors_MPC5744P.o \
./src/intc_sw_handlers.o \
./src/main.o \

C_DEPS_QUOTED += \
"./src/MPC57xx__Interrupt_Init.d" \
"./src/SysClk.d" \
"./src/TB_25LC256.d" \
"./src/TB_ADC.d" \
"./src/TB_AnSPI.d" \
"./src/TB_CAN.d" \
"./src/TB_DS1302.d" \
"./src/TB_GPIO.d" \
"./src/TB_LTC6804.d" \
"./src/TB_PIT.d" \
"./src/TB_UART.d" \
"./src/Vector.d" \
"./src/intc_SW_mode_isr_vectors_MPC5744P.d" \
"./src/main.d" \

OBJS += \
./src/MPC57xx__Interrupt_Init.o \
./src/SysClk.o \
./src/TB_25LC256.o \
./src/TB_ADC.o \
./src/TB_AnSPI.o \
./src/TB_CAN.o \
./src/TB_DS1302.o \
./src/TB_GPIO.o \
./src/TB_LTC6804.o \
./src/TB_PIT.o \
./src/TB_UART.o \
./src/Vector.o \
./src/intc_SW_mode_isr_vectors_MPC5744P.o \
./src/intc_sw_handlers.o \
./src/main.o \

OBJS_QUOTED += \
"./src/MPC57xx__Interrupt_Init.o" \
"./src/SysClk.o" \
"./src/TB_25LC256.o" \
"./src/TB_ADC.o" \
"./src/TB_AnSPI.o" \
"./src/TB_CAN.o" \
"./src/TB_DS1302.o" \
"./src/TB_GPIO.o" \
"./src/TB_LTC6804.o" \
"./src/TB_PIT.o" \
"./src/TB_UART.o" \
"./src/Vector.o" \
"./src/intc_SW_mode_isr_vectors_MPC5744P.o" \
"./src/intc_sw_handlers.o" \
"./src/main.o" \

C_DEPS += \
./src/MPC57xx__Interrupt_Init.d \
./src/SysClk.d \
./src/TB_25LC256.d \
./src/TB_ADC.d \
./src/TB_AnSPI.d \
./src/TB_CAN.d \
./src/TB_DS1302.d \
./src/TB_GPIO.d \
./src/TB_LTC6804.d \
./src/TB_PIT.d \
./src/TB_UART.d \
./src/Vector.d \
./src/intc_SW_mode_isr_vectors_MPC5744P.d \
./src/main.d \


# Each subdirectory must supply rules for building sources it contributes
src/MPC57xx__Interrupt_Init.o: ../src/MPC57xx__Interrupt_Init.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/MPC57xx__Interrupt_Init.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/MPC57xx__Interrupt_Init.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/SysClk.o: ../src/SysClk.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/SysClk.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/SysClk.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/TB_25LC256.o: ../src/TB_25LC256.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/TB_25LC256.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/TB_25LC256.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/TB_ADC.o: ../src/TB_ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/TB_ADC.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/TB_ADC.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/TB_AnSPI.o: ../src/TB_AnSPI.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/TB_AnSPI.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/TB_AnSPI.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/TB_CAN.o: ../src/TB_CAN.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/TB_CAN.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/TB_CAN.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/TB_DS1302.o: ../src/TB_DS1302.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/TB_DS1302.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/TB_DS1302.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/TB_GPIO.o: ../src/TB_GPIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/TB_GPIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/TB_GPIO.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/TB_LTC6804.o: ../src/TB_LTC6804.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/TB_LTC6804.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/TB_LTC6804.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/TB_PIT.o: ../src/TB_PIT.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/TB_PIT.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/TB_PIT.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/TB_UART.o: ../src/TB_UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/TB_UART.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/TB_UART.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Vector.o: ../src/Vector.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/Vector.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/Vector.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/intc_SW_mode_isr_vectors_MPC5744P.o: ../src/intc_SW_mode_isr_vectors_MPC5744P.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/intc_SW_mode_isr_vectors_MPC5744P.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/intc_SW_mode_isr_vectors_MPC5744P.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/intc_sw_handlers.o: ../src/intc_sw_handlers.S
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	powerpc-eabivle-gcc "@src/intc_sw_handlers.args" -c -o "src/intc_sw_handlers.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: ../src/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


