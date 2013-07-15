#include "etcp.h"

#define ACK 0x6

int main(int argc, char const *argv[])
{
	fd_set allreads;
	fd_set readmask;
	fd_set sockonly;
	SOCKET s;
	int rc;
	char buf[128];
	struct timeval tv;
	struct timeval *tvp = NULL;
	const static struct timeval T0 = {2, 0};

	INIT();
	s = tcp_client(argv[1], argv[2]);
	FD_ZERO( &allreads);
	FD_SET(s, &allreads);
	sockonly = allreads;
	FD_SET(0, &allreads);
	readmask = allreads;
	for ( ; ; )
	{
		rc = select(s+1, &readmask, NULL, NULL, NULL);
		if (rc < 0)
		{
			error(1, errno, "select failure");
		}
		if (FD_ISSET(0, &readmask))
		{
			rc = read(0, buf, sizeof(buf)-1);
			if (rc < 0)
			{
				error(1, errno, "read failure");
			}
			if (send(s, buf, rc, 0)<0)
			{
				error(1, errno, "send failure");
			}
			tvp = &T0;
			readmask = sockonly;
		}
		if (FD_ISSET(s, &readmask))
		{
			rc = recv(s, buf, sizeof(buf)-1, 0);
			if (rc < 0)
			{
				error(1, errno, "recv failure");
			}
			else if (rc == 0)
			{
				error(1, 0, "server disconnected");
			}
			else if (rc != 1 || buf[0] != ACK)
			{
				buf[rc] = '\0';
				error(1, 0, "unexpected input [%s]\n", buf);
			}
			tvp = NULL;
			readmask = sockonly;
		}
	}
	return 0;
}
