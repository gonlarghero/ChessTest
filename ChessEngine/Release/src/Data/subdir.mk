################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Data/DataManager.cpp 

CPP_DEPS += \
./src/Data/DataManager.d 

OBJS += \
./src/Data/DataManager.o 


# Each subdirectory must supply rules for building sources it contributes
src/Data/%.o: ../src/Data/%.cpp src/Data/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Data

clean-src-2f-Data:
	-$(RM) ./src/Data/DataManager.d ./src/Data/DataManager.o

.PHONY: clean-src-2f-Data

