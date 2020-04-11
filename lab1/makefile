all: hello writeText compareText

hello: hello.o
	ld -melf_i386 hello.o -o hello	

hello.o: hello.s
	as --32 hello.s -o hello.o


writeText: writeText.o
	ld -melf_i386 writeText.o -o writeText	

writeText.o: writeText.s
	as --32 writeText.s -o writeText.o


compareText: compareText.o
	ld -melf_i386 compareText.o -o compareText	

compareText.o: compareText.s
	as --32 compareText.s -o compareText.o

clean:
	rm hello hello.o writeText.o writeText compareText compareText.o
