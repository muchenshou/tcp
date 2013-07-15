EXE=server client udpserver udpclient keep xout1 xout2
all:$(EXE)

server:server.c etcp.c
	gcc -o $@ $^ -I./
client:client.c etcp.c
	gcc -o $@ $^ -I./

udpserver:udpserver.c etcp.c
	gcc -o $@ $^ -I./
udpclient:udpclient.c etcp.c
	gcc -o $@ $^ -I./
keep:keep.c etcp.c
	gcc -o $@ $^ -I./
xout1:xout1.c etcp.c
	gcc -o $@ $^ -I./
xout2:xout2.c etcp.c
	gcc -o $@ $^ -I./
.PHONY:clean
clean:
	rm $(EXE)
