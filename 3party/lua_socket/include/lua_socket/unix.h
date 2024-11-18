#ifndef UNIX_H
#define UNIX_H
/*=========================================================================*\
* Unix domain object
* LuaSocket toolkit
*
* This module is just an example of how to extend LuaSocket with a new 
* domain.
\*=========================================================================*/
#include "lua_socket/luasocket.h"

#include "lua_socket/buffer.h"
#include "lua_socket/timeout.h"
#include "lua_socket/socket.h"

typedef struct t_unix_ {
    t_socket sock;
    t_io io;
    t_buffer buf;
    t_timeout tm;
} t_unix;
typedef t_unix *p_unix;

LUASOCKET_API int luaopen_socket_unix(lua_State *L);

#endif /* UNIX_H */
