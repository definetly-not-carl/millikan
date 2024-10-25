LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

all: millikan

millikan: millikan.cpp funzioni.h
	g++ millikan.cpp -o millikan ${INCS} ${LIBS}

clean:
	rm millikan
