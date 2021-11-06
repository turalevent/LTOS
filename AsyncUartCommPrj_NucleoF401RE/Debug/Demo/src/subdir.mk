################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Demo/src/demo.c 

OBJS += \
./Demo/src/demo.o 

C_DEPS += \
./Demo/src/demo.d 


# Each subdirectory must supply rules for building sources it contributes
Demo/src/%.o: ../Demo/src/%.c Demo/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401xE -DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/google_drive_sync/prj/GitHub/LTOS/AsyncUartCommPrj_NucleoF401RE/AsyncComm/inc" -I"D:/google_drive_sync/prj/GitHub/LTOS/AsyncUartCommPrj_NucleoF401RE/LTOS/inc" -I"D:/google_drive_sync/prj/GitHub/LTOS/AsyncUartCommPrj_NucleoF401RE/Demo/inc" -I"D:/google_drive_sync/prj/GitHub/LTOS/AsyncUartCommPrj_NucleoF401RE/Blink/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

