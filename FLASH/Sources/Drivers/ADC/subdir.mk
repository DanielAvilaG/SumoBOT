################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/ADC/ADC_I.c" \
"../Sources/Drivers/ADC/ADC_P.c" \

C_SRCS += \
../Sources/Drivers/ADC/ADC_I.c \
../Sources/Drivers/ADC/ADC_P.c \

OBJS += \
./Sources/Drivers/ADC/ADC_I.o \
./Sources/Drivers/ADC/ADC_P.o \

C_DEPS += \
./Sources/Drivers/ADC/ADC_I.d \
./Sources/Drivers/ADC/ADC_P.d \

OBJS_QUOTED += \
"./Sources/Drivers/ADC/ADC_I.o" \
"./Sources/Drivers/ADC/ADC_P.o" \

C_DEPS_QUOTED += \
"./Sources/Drivers/ADC/ADC_I.d" \
"./Sources/Drivers/ADC/ADC_P.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/ADC/ADC_I.o \
./Sources/Drivers/ADC/ADC_P.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/ADC/ADC_I.o: ../Sources/Drivers/ADC/ADC_I.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/ADC/ADC_I.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/ADC/ADC_I.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/ADC/ADC_P.o: ../Sources/Drivers/ADC/ADC_P.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/ADC/ADC_P.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/ADC/ADC_P.o"
	@echo 'Finished building: $<'
	@echo ' '


