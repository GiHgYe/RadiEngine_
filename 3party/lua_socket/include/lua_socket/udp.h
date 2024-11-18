#ifndef UDP_H
#define UDP_H
/*=========================================================================*\
* UDP object
* LuaSocket toolkit
*
* The udp.h module provides LuaSocket with support for UDP protocol
* (AF_INET, SOCK_DGRAM).
*
* Two classes are defined: connected and unconnected. UDP objects are
* originally unconnected. They can be "connected" to a given address
* with a call to the setpeername function. The same function can be used to
* break the connection.
\*=========================================================================*/
#include "lua_socket/luasocket.h"

#include "lua_socket/timeout.h"
#include "lua_socket/socket.h"

#define UDP_DATAGRAMSIZE 8192

typedef struct t_udp_ {
    t_socket sock;
    t_timeout tm;
    int family;
} t_udp;
typedef t_udp *p_udp;

#ifndef _WIN32
#pragma GCC visibility push(hidden)
#endif

int udp_open(lua_State *L);

#ifndef _WIN32
#pragma GCC visibility pop
#endif

#endif /* UDP_H */