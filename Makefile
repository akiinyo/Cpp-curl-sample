all: clean build

build:
	g++ curlsample.cpp -o cppsample -lcurl

clean:
	rm -f cppsample
