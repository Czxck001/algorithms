CC=g++ -std=c++1y
LDFLAGS=
TARGETS= bisection fft mom

all: $(TARGETS)

bisection: src/bisection.cc
	$(CC) $< -o $@

fft: src/fft.cc
	$(CC) $< -o $@

mom: src/mom.cc
	$(CC) $< -o $@

clean:
	rm $(TARGETS)
