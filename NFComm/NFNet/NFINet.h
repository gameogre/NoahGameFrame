#ifndef __NFI_NET_H__
#define __NFI_NET_H__

#include <cstring>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <iostream>
#include <map>
#include <xtree>

#ifndef WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include "NFIPacket.h"

#include <event2/event.h> 
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/thread.h>
#include <event2/event_compat.h>
#include <event2/event.h>

#pragma pack(push, 1)

class NFINet
{
public:
	virtual  bool Execute(const float fLasFrametime, const float fStartedTime) = 0;

	virtual  int Initialization(const char* strIP, const unsigned short nPort, const bool bUsePacket = true) = 0;
	virtual  int Initialization(const unsigned int nMaxClient, const unsigned short nPort, const int nCpuCount = 4, const bool bUsePacket = true) = 0;

	virtual  bool Final() = 0;
    virtual  bool Reset() = 0;

	virtual bool SendMsg(const NFIPacket& msg, const uint16_t nSockIndex = 0, bool bBroadcast = false) = 0;
	virtual bool SendMsg(const uint16_t msgID, const char* msg, const uint16_t nLen, const uint16_t nSockIndex = 0, bool bBroadcast = false) = 0;
	
	virtual int OnRecivePacket(const NFIPacket& msg){return 1;};
	virtual int OnRecivePacket(const uint16_t nSockIndex, const uint16_t msgID, const char* msg, const uint16_t nLen){return 1;};
	virtual int OnConnectEvent(const uint16_t nSockIndex, short events){return 1;};

	virtual bool CloseSocket(const uint16_t nSockIndex) = 0;
	virtual bool AddBan(const uint16_t nSockIndex, const int32_t nTime = -1) = 0;
	virtual bool RemoveBan(const uint16_t nSockIndex) = 0;

	virtual void HeartPack() = 0;

protected:
private:
};

#pragma pack(pop)

#endif