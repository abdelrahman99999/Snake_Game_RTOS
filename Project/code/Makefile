 ###############################################################
 #
 # File Name: Makefile
 #
 # Description: make file which is responsible for building our project
 #
 #################################################################

include makedefs

RTOS_SOURCE_DIR=../freertos/Source

CFLAGS+=-I APP -I MCAL -I . -I ${RTOS_SOURCE_DIR}/include -I ${RTOS_SOURCE_DIR}/Source/portable/cli -I ${RTOS_SOURCE_DIR}/portable/GCC/ARM_CM3 -I ../Common/include  -D inline= 

VPATH=${RTOS_SOURCE_DIR}:${RTOS_SOURCE_DIR}/portable/MemMang:${RTOS_SOURCE_DIR}/portable/GCC/ARM_CM3:${RTOS_SOURCE_DIR}/portable/cli:MCAL:APP

OBJS=${COMPILER}/main.o                \
	  ${COMPILER}/FreeRTOS_CLI.o       \
	  ${COMPILER}/CLI.o      	   	   \
      ${COMPILER}/list.o               \
      ${COMPILER}/queue.o              \
      ${COMPILER}/tasks.o              \
      ${COMPILER}/port.o               \
      ${COMPILER}/heap_1.o             \
	  ${COMPILER}/snake_game.o         \
	  ${COMPILER}/uart.o               \
	  

INIT_OBJS= ${COMPILER}/startup.o


all: ${COMPILER}           \
	${COMPILER}/Snake.axf \
	 
clean:
	@rm -rf ${COMPILER} ${wildcard *.bin} Snake.axf
	
${COMPILER}:
	@mkdir ${COMPILER}

${COMPILER}/Snake.axf: ${INIT_OBJS} ${OBJS} ${LIBS}
SCATTER_Snake=linkerscript.ld
ENTRY_Snake=ResetISR

-include ${wildcard ${COMPILER}/*.d} __dummy__
