################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Map/MapTile.cpp \
../src/Map/WorldMap.cpp 

OBJS += \
./src/Map/MapTile.o \
./src/Map/WorldMap.o 

CPP_DEPS += \
./src/Map/MapTile.d \
./src/Map/WorldMap.d 


# Each subdirectory must supply rules for building sources it contributes
src/Map/%.o: ../src/Map/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"../Cube Game/Cube Game/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


