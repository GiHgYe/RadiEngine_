#pragma once
#include "..\Runtime\include\ui\ui_camera.h"

class UICamera;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeUICameraOperator{
    public:
        static const char* getClassName(){ return "UICamera";}
        static void* constructorWithJson(const Json& json_context){
            UICamera* ret_instance= new UICamera;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(UICamera*)instance);
        }
        // base class
        static int getUICameraBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Camera,static_cast<UICamera*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_UICamera(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_UICamera=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeUICameraOperator::getUICameraBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeUICameraOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeUICameraOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("UICamera", class_function_tuple_UICamera);
    }
namespace TypeWrappersRegister{
    void UiCamera()
    {
        TypeWrapperRegister_UICamera();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


