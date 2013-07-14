#ifndef __SKEL_H__
#define __SKEL_H__
#define INIT() (program_name=strrchr(argv[0],'/')) ? program_name++:(program_name=argv[0])
#define EXIT(s) exit(s)
#define CLOSE(s) if(close(s)) error(1,errno, "close failed")
#define isvalidsock(s) ((s)>=0)
typedef int SOCKET;
#define NLISTEN 10
#endif
