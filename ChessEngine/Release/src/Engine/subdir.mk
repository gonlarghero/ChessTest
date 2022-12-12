################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Engine/EngineManager.cpp 

CPP_DEPS += \
./src/Engine/EngineManager.d 

OBJS += \
./src/Engine/EngineManager.o 


# Each subdirectory must supply rules for building sources it contributes
src/Engine/%.o: ../src/Engine/%.cpp src/Engine/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Engine

clean-src-2f-Engine:
	-$(RM) ./src/Engine/EngineManager.d ./src/Engine/EngineManager.o

.PHONY: clean-src-2f-Engine

