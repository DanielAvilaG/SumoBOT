################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/HC/HC.c" \

C_SRCS += \
../Sources/Drivers/HC/HC.c \

OBJS += \
./Sources/Drivers/HC/HC.o \

C_DEPS += \
./Sources/Drivers/HC/HC.d \

OBJS_QUOTED += \
"./Sources/Drivers/HC/HC.o" \

C_DEPS_QUOTED += \
"./Sources/Drivers/HC/HC.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/HC/HC.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/HC/HC.o: ../Sources/Drivers/HC/HC.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/HC/HC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/HC/HC.o"
	@echo 'Finished building: $<'
	@echo ' '


