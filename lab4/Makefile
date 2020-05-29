all: lab4 

lab4: lab4_c.c lab4_dodawanie.s lab4_dodawanie_simple.s lab4_odejmowanie.s lab4_odejmowanie_simple.s lab4_mnozenie.s mnozenie_simple.s lab4_dzielenie.s lab4_dzielenie_simple.s timestamp.s
	gcc -m32 timestamp.s lab4_dodawanie.s lab4_dodawanie_simple.s lab4_odejmowanie.s lab4_odejmowanie_simple.s lab4_mnozenie.s mnozenie_simple.s lab4_dzielenie.s lab4_dzielenie_simple.s lab4_c.c -o lab4

clean:
	rm lab4 wyniki_ssid.txt wyniki_simd.txt
