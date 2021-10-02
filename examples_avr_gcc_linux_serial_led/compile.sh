rm  -rf main.elf main.hex
avr-gcc -g -Os -mmcu=at90usb1287 main.c -o main.elf
avr-objcopy -j .text -j .data -O ihex main.elf main.hex

