all:server client udpserver udpclient keep

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
.PHONY:clean
clean:
	rm server client udpserver udpclient keep
