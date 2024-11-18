#pragma once
#include "..\Runtime\include\renderer\animation.h"

class Animation;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeAnimationOperator{
    public:
        static const char* getClassName(){ return "Animation";}
        static void* constructorWithJson(const Json& json_context){
            Animation* ret_instance= new Animation;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(Animation*)instance);
        }
        // base class
        static int getAnimationBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Component,static_cast<Animation*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Animation(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_Animation=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeAnimationOperator::getAnimationBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeAnimationOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeAnimationOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("Animation", class_function_tuple_Animation);
    }
namespace TypeWrappersRegister{
    void Animation()
    {
        TypeWrapperRegister_Animation();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


