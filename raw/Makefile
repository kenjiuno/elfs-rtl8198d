all: true.elf

true.elf: true.c
	${GCC} -c true.c -o true.o
	${LD} -o true.elf -Ttext-segment 0x80000000 --entry=entry true.o
	cp true.elf /srv/tftp/
