all: dodawanie odejmowanie mnozenie long-mul

dodawanie: dodawanie.s
	gcc -m32 dodawanie.s -o dodawanie

odejmowanie: odejmowanie.s
	gcc -m32 odejmowanie.s -o odejmowanie

mnozenie: mnozenie.s
	gcc -m32 mnozenie.s -o mnozenie

long-mul: long-mul.s
	gcc -m32 long-mul.s -o long-mul

clean:
	rm dodawanie odejmowanie mnozenie
