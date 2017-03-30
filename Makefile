
install : main.o fakeip_set.o interf.o fetcharpt.o attack.o
	gcc -o arp_spoof main.o fakeip_set.o interf.o fetcharpt.o attack.o 

main.o : main.c
	gcc -c main.c

fakeip_set.o : fakeip_set.h fakeip_set.c
	gcc -c fakeip_set.c

interf.o : interf.h interf.c
	gcc -c interf.c

fetcharp.o : fetcharpt.c fetcharpt.h
	gcc -c fetcharpt.c

attack.o : attack.c attack.h arp_struct.h
	gcc -c attack.c

clean : 
	rm -f *~ *.o arp_spoof

