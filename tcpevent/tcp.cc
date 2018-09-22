#include "tcp.h"
#include <fcntl.h>
namespace zsy{
int setnonblocking(int fd)
{
	if(fcntl( fd, F_SETFL, fcntl( fd, F_GETFD, 0 )|O_NONBLOCK ) == -1 )
	{
		return -1;
	}
	return 0;
}
}
