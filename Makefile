.SUFFIXES : .x .o .c .s

HMI_DIR := .
HMI := ByteSizedDemo

CC := arm-linux-gcc
STRIP := arm-linux-strip
OBJCOPY := arm-linux-objcopy 

INCLUDE := -I./out
LIBDIRS := -L./out
LIBS := -laltia
OBJFILES := $(HMI_DIR)/out/reflash/$(HMI)/altia_table_bin.o $(HMI_DIR)/out/reflash/$(HMI)/images/altia_images_bin.o $(HMI_DIR)/out/reflash/$(HMI)/fonts/altia_fonts_bin.o

TARGET = bytesizeddemo
SRCS := bytesizeddemo.c

prebuild:
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm --rename-section .data=.rodata,alloc,load,readonly,data,contents $(HMI_DIR)/out/reflash/$(HMI)/table.bin $(HMI_DIR)/out/reflash/$(HMI)/altia_table_bin.o;
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm --rename-section .data=.rodata,alloc,load,readonly,data,contents $(HMI_DIR)/out/reflash/$(HMI)/images/altiaImageDataPartition0.bin $(HMI_DIR)/out/reflash/$(HMI)/images/altia_images_bin.o;
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm --rename-section .data=.rodata,alloc,load,readonly,data,contents $(HMI_DIR)/out/reflash/$(HMI)/fonts/altiaImageDataPartition0.bin $(HMI_DIR)/out/reflash/$(HMI)/fonts/altia_fonts_bin.o;

all: 
	$(CC) -Wl,-Map -Wl,bytesizeddemo.map -mthumb -static -DMINIGL_UNICODE $(INCLUDE) $(SRCS) $(LIBDIRS) $(LIBS) $(OBJFILES) -o $(TARGET)
#	$(STRIP) $(TARGET) 

clean:
	rm -f *.o 
	rm -f *.x 
	rm -f *.flat
	rm -f *.map
	rm -f temp
	rm -f *.img
	rm -f $(TARGET)	
	rm -f *.gdb
	rm -f *.bak
