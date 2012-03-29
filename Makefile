all: clean build

build:
	g++ curlsample.cpp -o cppsample

clean:
	rm -f cppsample
