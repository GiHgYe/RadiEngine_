#pragma once
#include "..\Runtime\include\ui\ui_mask.h"

class UIMask;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeUIMaskOperator{
    public:
        static const char* getClassName(){ return "UIMask";}
        static void* constructorWithJson(const Json& json_context){
            UIMask* ret_instance= new UIMask;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(UIMask*)instance);
        }
        // base class
        static int getUIMaskBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Component,static_cast<UIMask*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_UIMask(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_UIMask=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeUIMaskOperator::getUIMaskBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeUIMaskOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeUIMaskOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("UIMask", class_function_tuple_UIMask);
    }
namespace TypeWrappersRegister{
    void UiMask()
    {
        TypeWrapperRegister_UIMask();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


