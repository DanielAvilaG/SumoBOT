################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/UART/UART.c" \

C_SRCS += \
../Sources/Drivers/UART/UART.c \

OBJS += \
./Sources/Drivers/UART/UART.o \

C_DEPS += \
./Sources/Drivers/UART/UART.d \

OBJS_QUOTED += \
"./Sources/Drivers/UART/UART.o" \

C_DEPS_QUOTED += \
"./Sources/Drivers/UART/UART.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/UART/UART.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/UART/UART.o: ../Sources/Drivers/UART/UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/UART/UART.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/UART/UART.o"
	@echo 'Finished building: $<'
	@echo ' '


