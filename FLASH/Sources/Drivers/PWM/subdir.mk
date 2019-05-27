################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/PWM/PWM.c" \

C_SRCS += \
../Sources/Drivers/PWM/PWM.c \

OBJS += \
./Sources/Drivers/PWM/PWM.o \

C_DEPS += \
./Sources/Drivers/PWM/PWM.d \

OBJS_QUOTED += \
"./Sources/Drivers/PWM/PWM.o" \

C_DEPS_QUOTED += \
"./Sources/Drivers/PWM/PWM.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/PWM/PWM.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/PWM/PWM.o: ../Sources/Drivers/PWM/PWM.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/PWM/PWM.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/PWM/PWM.o"
	@echo 'Finished building: $<'
	@echo ' '


