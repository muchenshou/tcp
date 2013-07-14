#include "etcp.h"
static void server(SOCKET s, struct sockaddr* local)
{
	struct sockaddr_in peer;
	int peerlen;
	char buf[1];
	for(;;) {
		peerlen = sizeof(peer);
		if (recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&peer, &peerlen) < 0)
		{
			error(1, errno, "recvfrom failed");
		}
		if (sendto(s, "hello world\n", 13, 0,(struct sockaddr*)&peer, peerlen) < 0 )
		{
			error(1, errno, "sendto failed");
		}
	}
}

int main(int argc, char const *argv[])
{
	char* hname;
	char* sname;
	INIT();
	if (argc == 2)
	{
		hname = NULL;
		sname = argv[1];
	}
	else
	{
		hname = argv[1];
		sname = argv[2];
	}
	SOCKET s = udp_server(hname, sname);
	server(s, NULL);
	return 0;
}