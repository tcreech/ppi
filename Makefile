BINS = ppi

all:	ppi

LDFLAGS += -lm -fopenmp
CFLAGS += -O2 -fopenmp

clean:
	-rm -f $(BINS)

