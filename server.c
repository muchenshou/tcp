#include "etcp.h"

static void server(SOCKET s, struct sockaddr_in* peerp) {
	fputs("send hello\n", stdout);
	send(s, "hello world\n", 13, 0);
}

int main(int argc, char const *argv[])
{
	
	//struct sockaddr_in local;
	struct sockaddr_in peer;
	char *hname, *sname;
	int peerlen;
	SOCKET s1,s;
	INIT();

	if (argc == 2)
	{
		/* code */
		hname = NULL;
		sname = argv[1];
	}
	else
	{
		hname = argv[1];
		sname = argv[2];
	}

	//set_address(hname, sname, &local, "tcp");
	s = tcp_server(hname, sname);
	do {
		peerlen = sizeof(peer);
		//bzero(&peer, peerlen);
		s1 = accept(s, (struct sockaddr *)&peer, &peerlen);
		if (!isvalidsock(s1))
		{
			error(1, errno, "accept failed");
		}
		server(s1, &peer);
		CLOSE(s1);
	}while(1);
	return 0;
}
