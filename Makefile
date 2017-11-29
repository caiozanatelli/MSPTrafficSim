.PHONY: default all clean

all: parteA parteB

parteA:
	msp430-gcc -Os -mmcu=msp430g2553 src/ParteA/interruption.c -o interruption.elf
	msp430-gcc -Os -mmcu=msp430g2553 src/ParteA/traffic_light.c -o traffic_light.elf
parteB:
	msp430-gcc -Os -mmcu=msp430g2553 src/ParteB/scheduler.c -o scheduler.elf

clean:
	rm *.elf