BINS = ppi ppi_threads

all:	$(BINS)

LDFLAGS += -lm -fopenmp -lpthread
CFLAGS += -O2 -fopenmp

clean:
	-rm -f $(BINS)

