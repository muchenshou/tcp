#include "etcp.h"

static void client(SOCKET s, struct sockaddr_in *peerp) 
{
	int rc;
	char buf[120];
	for (;;) {
		rc = recv(s, &buf[0], 120, 0);
		printf("recv :%d\n", rc);
		if (rc <=0)
		{
			error(1, errno, "recv failed");
			break;
		}
		write(1, buf, rc);
	}

}

int main(int argc, char const *argv[])
{
	SOCKET s;
	char* hname;
	char* sname;
	struct sockaddr_in peer;
	INIT();
	s = tcp_client(argv[1], argv[2], &peer);
	if (!isvalidsock(s))
	{
		error(1, errno, "invalid socket");
	}
	client(s, &peer);
	CLOSE(s);
	return 0;
}
