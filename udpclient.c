#include "etcp.h"

static void client(SOCKET s, struct sockaddr_in* peer)
{
	int rc;
	int peerlen;
	char buf[100];
	peerlen = sizeof(*peer);
	if (sendto(s, "",1, 0, (struct sockaddr*)peer, peerlen) < 0)
	{
		error(1, errno, "sendto failed");
	}
	rc = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)peer, &peerlen);
	if (rc<=0)
	{
		error(1, errno, "recvfrom failed");
	}
	write(1, buf, rc);
}
int main(int argc, char const *argv[])
{
	SOCKET s;
	struct sockaddr_in peer;
	char* hname;
	char* sname;
	INIT();
	hname = argv[1];
	sname = argv[2];
	s = udp_client(hname, sname, &peer);
	client(s, &peer);
	return 0;
}