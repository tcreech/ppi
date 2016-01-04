BINS = ppi ppi_threads

all:	$(BINS)

LDFLAGS += -lm -fopenmp -lpthread
CFLAGS += -O2 -fopenmp

%:	%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LDFLAGS)

clean:
	-rm -f $(BINS)

test:	all
	./ppi_threads 4 10
	OMP_NUM_THREADS=4 ./ppi 10

