# Snake_Game_RTOS
## Prerequests
- GNU Make
- Qemu emulator
  
## Build commands
```
make clean
make 
```

## Debug commands
```
qemu-system-arm -M lm3s6965evb -m 128M  -s -S  -nographic -kernel gcc/Snake.axf
arm-none-eabi-gdb.exe gcc/Snake.axf
target remote localhost:1234
```
## RUN commands #########
```
 qemu-system-arm -M lm3s6965evb -nographic -kernel gcc/Snake.bin
```
## Demo

Link: https://drive.google.com/drive/folders/1ec0S2Njf6rQPxsSqO6VrZqBw8PvzBWFP
