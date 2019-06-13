################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/brain.c" \
"../Sources/calibrate.c" \
"../Sources/combat.c" \
"../Sources/common.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/brain.c \
../Sources/calibrate.c \
../Sources/combat.c \
../Sources/common.c \
../Sources/main.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/brain.o \
./Sources/calibrate.o \
./Sources/combat.o \
./Sources/common.o \
./Sources/main.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/brain.d \
./Sources/calibrate.d \
./Sources/combat.d \
./Sources/common.d \
./Sources/main.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/brain.o" \
"./Sources/calibrate.o" \
"./Sources/combat.o" \
"./Sources/common.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/brain.d" \
"./Sources/calibrate.d" \
"./Sources/combat.d" \
"./Sources/common.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/brain.o \
./Sources/calibrate.o \
./Sources/combat.o \
./Sources/common.o \
./Sources/main.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/brain.o: ../Sources/brain.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/brain.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/brain.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/calibrate.o: ../Sources/calibrate.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/calibrate.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/calibrate.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/combat.o: ../Sources/combat.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/combat.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/combat.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common.o: ../Sources/common.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/common.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/common.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


