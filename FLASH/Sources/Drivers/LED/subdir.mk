################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/LED/LED_25.c" \
"../Sources/Drivers/LED/LED_46.c" \

C_SRCS += \
../Sources/Drivers/LED/LED_25.c \
../Sources/Drivers/LED/LED_46.c \

OBJS += \
./Sources/Drivers/LED/LED_25.o \
./Sources/Drivers/LED/LED_46.o \

C_DEPS += \
./Sources/Drivers/LED/LED_25.d \
./Sources/Drivers/LED/LED_46.d \

OBJS_QUOTED += \
"./Sources/Drivers/LED/LED_25.o" \
"./Sources/Drivers/LED/LED_46.o" \

C_DEPS_QUOTED += \
"./Sources/Drivers/LED/LED_25.d" \
"./Sources/Drivers/LED/LED_46.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/LED/LED_25.o \
./Sources/Drivers/LED/LED_46.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/LED/LED_25.o: ../Sources/Drivers/LED/LED_25.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/LED/LED_25.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/LED/LED_25.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/LED/LED_46.o: ../Sources/Drivers/LED/LED_46.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/LED/LED_46.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/LED/LED_46.o"
	@echo 'Finished building: $<'
	@echo ' '


