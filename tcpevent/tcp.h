#ifndef	TCP_CON_H
#define TCP_CON_H
namespace zsy{
int setnonblocking(int fd);
class TcpInterface{
	public:
	virtual bool OnIncomingEvent()=0;
	virtual void OnWriteEvent()=0;
	virtual ~TcpInterface(){}
};
}
#endif
