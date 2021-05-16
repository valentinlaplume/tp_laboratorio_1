################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ArrayEmployees.c \
../src/TrabajoPractico2_Labo1.c \
../src/utn.c 

OBJS += \
./src/ArrayEmployees.o \
./src/TrabajoPractico2_Labo1.o \
./src/utn.o 

C_DEPS += \
./src/ArrayEmployees.d \
./src/TrabajoPractico2_Labo1.d \
./src/utn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


