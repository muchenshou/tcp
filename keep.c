#include "etcp.h"

int readline(SOCKET fd, char* bufptr, size_t len)
{
	char* bufx = bufptr;
	static char* bp;
	static int cnt;
	static char b[1500];
	char c;
	while( --len>0 ) {
		if (--cnt <= 0)
		{
			cnt = recv(fd, b, sizeof(b), 0);
			if (cnt < 0)
			{
				if (errno == EINTR)
				{
					len++;
					continue;
				}
				return -1;
			}
			if (cnt == 0)
			{
				return 0;
			}
			bp = b;
		}
		c = *bp++;
		*bufptr++ = c;
		if (c == '\n')
		{
			*bufptr = '\0';
			return bufptr - bufx;
		}
	}
	// set_errno(EMSGSIZE);
	return -1;
}

int main(int argc, char const *argv[])
{
	SOCKET s,s1;
	int on = 1;
	char buf[1024];
	int rc;
	s = tcp_server(NULL, argv[1]);
	s1 = accept(s, NULL, NULL);
	if (!isvalidsock(s1))
	{
		error(1, errno, "accept failed");
	}
	if (setsockopt(s1, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof(on)))
	{
		error(1, errno, "setsockopt failed");
	}
	for (;;) {
		rc = readline(s1, buf, sizeof(buf));
		if (rc == 0)
		{
			error(1, 0, "peer disconnected\n");
		}
		if (rc < 0)
		{
			error(1, errno, "recv failure\n");
		}
		write(1, buf, rc);
	}
	return 0;
}
