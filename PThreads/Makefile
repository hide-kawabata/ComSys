#CXX = g++-11
#CXX = c++-13
CXX = clang

TARGET = hello mc_pth countup race norace

top: hello

hello: hello.o
	$(CXX) -o $@ $< -pthread

mc_pth: mc_pth.o
	$(CXX) -o $@ $< -pthread

countup: countup.o
	$(CXX) -o $@ $< -pthread

race: race.o
	$(CXX) -o $@ $< -pthread

norace: norace.o
	$(CXX) -o $@ $< -pthread

.c.o:
	$(CXX) -O3 -c $< -pthread

clean:
	rm -fr *.o a.out $(TARGET)
