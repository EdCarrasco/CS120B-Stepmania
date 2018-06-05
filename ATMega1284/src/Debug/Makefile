################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../controllerSM.c \
../eeprom.c \
../globals.c \
../lcdSM.c \
../lcd_4bit.c \
../lcd_customs.c \
../music_playerSM.c \
../pwm.c \
../snes.c \
../stepmania.c \
../tabula.c \
../timer.c \
../usart.c \
../usartSM.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
controllerSM.o \
eeprom.o \
globals.o \
lcdSM.o \
lcd_4bit.o \
lcd_customs.o \
music_playerSM.o \
pwm.o \
snes.o \
stepmania.o \
tabula.o \
timer.o \
usart.o \
usartSM.o

OBJS_AS_ARGS +=  \
controllerSM.o \
eeprom.o \
globals.o \
lcdSM.o \
lcd_4bit.o \
lcd_customs.o \
music_playerSM.o \
pwm.o \
snes.o \
stepmania.o \
tabula.o \
timer.o \
usart.o \
usartSM.o

C_DEPS +=  \
controllerSM.d \
eeprom.d \
globals.d \
lcdSM.d \
lcd_4bit.d \
lcd_customs.d \
music_playerSM.d \
pwm.d \
snes.d \
stepmania.d \
tabula.d \
timer.d \
usart.d \
usartSM.d

C_DEPS_AS_ARGS +=  \
controllerSM.d \
eeprom.d \
globals.d \
lcdSM.d \
lcd_4bit.d \
lcd_customs.d \
music_playerSM.d \
pwm.d \
snes.d \
stepmania.d \
tabula.d \
timer.d \
usart.d \
usartSM.d

OUTPUT_FILE_PATH +=stepmania.elf

OUTPUT_FILE_PATH_AS_ARGS +=stepmania.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler





























./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"../../header" -I"D:\Program Files\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -mmcu=atmega1284 -B "D:\Program Files\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\gcc\dev\atmega1284" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)D:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="stepmania.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mrelax -mmcu=atmega1284 -B "D:\Program Files\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.2.150\gcc\dev\atmega1284"  
	@echo Finished building target: $@
	"D:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "stepmania.elf" "stepmania.hex"
	"D:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "stepmania.elf" "stepmania.eep" || exit 0
	"D:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "stepmania.elf" > "stepmania.lss"
	"D:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "stepmania.elf" "stepmania.srec"
	"D:\Program Files\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "stepmania.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "stepmania.elf" "stepmania.a" "stepmania.hex" "stepmania.lss" "stepmania.eep" "stepmania.map" "stepmania.srec" "stepmania.usersignatures"
	