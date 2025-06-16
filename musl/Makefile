all: truec.elf

truec.elf: truec.c
	./gcc.sh -static -Wl,-Ttext-segment=0x80000000 truec.c -o truec.elf
	cp truec.elf /srv/tftp/
