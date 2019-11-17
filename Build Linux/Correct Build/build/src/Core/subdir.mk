################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Core/GameObject.cpp \
../src/Core/Libraries.cpp \
../src/Core/Model.cpp \
../src/Core/ShaderManager.cpp \
../src/Core/WorldObject.cpp 

OBJS += \
./src/Core/GameObject.o \
./src/Core/Libraries.o \
./src/Core/Model.o \
./src/Core/ShaderManager.o \
./src/Core/WorldObject.o 

CPP_DEPS += \
./src/Core/GameObject.d \
./src/Core/Libraries.d \
./src/Core/Model.d \
./src/Core/ShaderManager.d \
./src/Core/WorldObject.d 


# Each subdirectory must supply rules for building sources it contributes
src/Core/%.o: ../src/Core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"../Cube Game/Cube Game/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


