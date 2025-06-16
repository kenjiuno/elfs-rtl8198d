all: print.elf

%.o: %.c
	${GCC} -c $< -o $@

%.elf: %.o
	${LD} -o $@ -Ttext-segment 0x80000000 --entry=entry $^
	cp $@ /srv/tftp/

print.elf: m0crt.o print.o

