all:
	chmod a+x myShell.c
	gcc -o myShell myShell.c
	gcc -o writef writef.c
	gcc -o execx execx.c
clean:
	rm myShell
	rm execx
	rm writef
