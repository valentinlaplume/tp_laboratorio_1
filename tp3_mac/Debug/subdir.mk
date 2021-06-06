################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Controller.c \
../Employee.c \
../laplume.c \
../main_TP3.c \
../parser.c \
../serializer.c \
../utn.c 

OBJS += \
./Controller.o \
./Employee.o \
./laplume.o \
./main_TP3.o \
./parser.o \
./serializer.o \
./utn.o 

C_DEPS += \
./Controller.d \
./Employee.d \
./laplume.d \
./main_TP3.d \
./parser.d \
./serializer.d \
./utn.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


