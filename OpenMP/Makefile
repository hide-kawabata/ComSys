#CXX = g++-11
#CXX = c++-13
CXX = clang

TARGET = mc mc_serial mc_integral mc_integral_serial array mc2

top: array

array: array.o
	$(CXX) -o $@ $< -fopenmp

mc_integral_serial: mc_integral_serial.o
	$(CXX) -o $@ $< -fopenmp

mc_integral: mc_integral.o
	$(CXX) -o $@ $< -fopenmp

mc_serial: mc_serial.o
	$(CXX) -o $@ $< -fopenmp

mc: mc.o
	$(CXX) -o $@ $< -fopenmp

mc2: mc2.o
	$(CXX) -o $@ $< -fopenmp

.c.o:
	$(CXX) -O3 -c $< -fopenmp

clean:
	rm -fr *.o a.out $(TARGET)
