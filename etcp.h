#ifndef __ETCP_H__
#define __ETCP_H__ 
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include "skel.h"
extern const char* program_name;
void error(int status, int err, char *fmt, ...);
void set_address
	(char* hname, char*sname, struct sockaddr_in *sap, char *protocol);
#endif
