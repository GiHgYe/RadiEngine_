#pragma once
#include "..\Runtime\include\ui\ui_text.h"

class UIText;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeUITextOperator{
    public:
        static const char* getClassName(){ return "UIText";}
        static void* constructorWithJson(const Json& json_context){
            UIText* ret_instance= new UIText;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(UIText*)instance);
        }
        // base class
        static int getUITextBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Component,static_cast<UIText*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_UIText(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_UIText=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeUITextOperator::getUITextBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeUITextOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeUITextOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("UIText", class_function_tuple_UIText);
    }
namespace TypeWrappersRegister{
    void UiText()
    {
        TypeWrapperRegister_UIText();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


