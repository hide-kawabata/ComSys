CC = mpicc

TARGET = hello sendrecv recvanon sendrecv0 sendrecv_dl sendrecv_sb bcast

top: hello

hello: hello.o
	$(CC) -o $@ $<

bcast: bcast.o
	$(CC) -o $@ $<

sendrecv_dl: sendrecv_dl.o
	$(CC) -o $@ $<

sendrecv_sb: sendrecv_sb.o
	$(CC) -o $@ $<

sendrecv0: sendrecv0.o
	$(CC) -o $@ $<

recvanon: recvanon.o
	$(CC) -o $@ $<

sendrecv: sendrecv.o
	$(CC) -o $@ $<

.c.o:
	$(CC) -O3 -c $<

clean:
	rm -fr *.o a.out $(TARGET)
