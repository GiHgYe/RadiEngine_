#include "meta/reflection/reflection_register.h"
#include "meta/reflection/reflection.h"

#include "serializer/all_serializer.ipp"

namespace Reflection
{
    void TypeMetaRegister::metaUnregister() { TypeMetaRegisterinterface::unregisterAll(); }
}