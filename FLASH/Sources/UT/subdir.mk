################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/UT/HC_Test.c" \
"../Sources/UT/IR_Test.c" \
"../Sources/UT/PWM_Test.c" \

C_SRCS += \
../Sources/UT/HC_Test.c \
../Sources/UT/IR_Test.c \
../Sources/UT/PWM_Test.c \

OBJS += \
./Sources/UT/HC_Test.o \
./Sources/UT/IR_Test.o \
./Sources/UT/PWM_Test.o \

C_DEPS += \
./Sources/UT/HC_Test.d \
./Sources/UT/IR_Test.d \
./Sources/UT/PWM_Test.d \

OBJS_QUOTED += \
"./Sources/UT/HC_Test.o" \
"./Sources/UT/IR_Test.o" \
"./Sources/UT/PWM_Test.o" \

C_DEPS_QUOTED += \
"./Sources/UT/HC_Test.d" \
"./Sources/UT/IR_Test.d" \
"./Sources/UT/PWM_Test.d" \

OBJS_OS_FORMAT += \
./Sources/UT/HC_Test.o \
./Sources/UT/IR_Test.o \
./Sources/UT/PWM_Test.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/UT/HC_Test.o: ../Sources/UT/HC_Test.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/UT/HC_Test.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/UT/HC_Test.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/UT/IR_Test.o: ../Sources/UT/IR_Test.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/UT/IR_Test.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/UT/IR_Test.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/UT/PWM_Test.o: ../Sources/UT/PWM_Test.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/UT/PWM_Test.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/UT/PWM_Test.o"
	@echo 'Finished building: $<'
	@echo ' '


