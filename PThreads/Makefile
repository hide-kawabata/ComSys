#CXX = g++-11
#CXX = c++-13
CXX = clang

TARGET = hello

top: hello

hello: hello.o
	$(CXX) -o $@ $<

.c.o:
	$(CXX) -O3 -c $< -pthread

clean:
	rm -fr *.o a.out $(TARGET)
