maxflow : maxflow.o
	cc -o maxflow maxflow.o

maxflow.o : maxflow.c
	cc -c maxflow.c

clean : 
	rm maxflow.o