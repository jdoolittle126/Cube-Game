################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Entity/Entity.cpp 

OBJS += \
./src/Entity/Entity.o 

CPP_DEPS += \
./src/Entity/Entity.d 


# Each subdirectory must supply rules for building sources it contributes
src/Entity/%.o: ../src/Entity/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"../Cube Game/Cube Game/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


