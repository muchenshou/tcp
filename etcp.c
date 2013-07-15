#include "etcp.h"

const char *program_name;

void error(int status, int err, char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, "%s:", program_name);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	if (err)
	{
		fprintf(stderr, ":%s(%d)\n", strerror(err), err);
	}
	if (status)
	{
		EXIT(status);
	}
}

void set_address
	(char* hname, char*sname, struct sockaddr_in *sap, char *protocol) {
	struct servent *sp;
	struct hostent *hp;
	char* endptr;
	short port;

	bzero(sap, sizeof(*sap));
	sap->sin_family = AF_INET;
	if (hname != NULL)
	{
		if (!inet_aton(hname, &sap->sin_addr))
		{
			hp = gethostbyname(hname);
			if (hp == NULL)
			{
				error(1, 0, "unkown host:%s\n", hname);
				sap->sin_addr.s_addr = *hp->h_addr;
			}
		}
	}
	else
	{
		sap->sin_addr.s_addr = htonl(INADDR_ANY);
	}

	port = strtol(sname, &endptr, 0);
	if (*endptr == '\0') {
		sap->sin_port = htons(port);
	} else {
		sp = getservbyname(sname, protocol);
		if (sp == NULL)
		{
			error(1, 0, "unkown service:%d\n", sname);
		}
		sap->sin_port = sp->s_port;
	}
}

SOCKET tcp_server(char* hname, char* sname){
	struct sockaddr_in local;
	const int on = 1;
	set_address(hname, sname, &local, "tcp");
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (!isvalidsock(s)) {
		error(1, errno, "socket create failed");
	}
	if ( setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) )
	{
		error(1, errno, "setsockopt failed");
	}

	if (bind(s, (struct sockaddr*)&local, sizeof(local)))
	{
		error(1, errno, "bind failed");
	}
	if (listen(s, NLISTEN))
	{
		error(1, errno, "listen failed");
	}
	return s;
}

SOCKET tcp_client(const char* hname,const char* sname , struct sockaddr_in* peer) {
	set_address(hname, sname, peer, "tcp");
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (!isvalidsock(s)) {
		error(1, errno, "socket create failed");
	}
	if (connect(s, (struct sockaddr*)peer, sizeof(*peer)))
	{
		/* code */
		error(1, error, "connect failed");
	}
	return s;
}

SOCKET udp_server(char* hname, char* sname)
{
	struct sockaddr_in local;
	set_address(hname, sname, &local, "udp");
	SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
	if (!isvalidsock(s))
	{
		error(1, errno, "socket failed");
	}
	if (bind(s, (struct sockaddr*)&local, sizeof(local)))
	{
		error(1, errno, "bind failed");
	}
	return s;
}

SOCKET udp_client(char* hname, char* sname, struct sockaddr_in* peer)
{
	SOCKET s;
	printf("udp_client1");
	set_address(hname, sname, peer, sizeof(*peer));
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (!isvalidsock(s))
	{
		error(1, errno, "socket failed");
	}
	return s;
}
