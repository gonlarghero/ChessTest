################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Interface/InterfaceManager.cpp 

CPP_DEPS += \
./src/Interface/InterfaceManager.d 

OBJS += \
./src/Interface/InterfaceManager.o 


# Each subdirectory must supply rules for building sources it contributes
src/Interface/%.o: ../src/Interface/%.cpp src/Interface/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Interface

clean-src-2f-Interface:
	-$(RM) ./src/Interface/InterfaceManager.d ./src/Interface/InterfaceManager.o

.PHONY: clean-src-2f-Interface

