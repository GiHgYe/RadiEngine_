#pragma once
#include "..\Runtime\include\ui\ui_button.h"

class UIButton;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeUIButtonOperator{
    public:
        static const char* getClassName(){ return "UIButton";}
        static void* constructorWithJson(const Json& json_context){
            UIButton* ret_instance= new UIButton;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(UIButton*)instance);
        }
        // base class
        static int getUIButtonBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Component,static_cast<UIButton*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_UIButton(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_UIButton=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeUIButtonOperator::getUIButtonBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeUIButtonOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeUIButtonOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("UIButton", class_function_tuple_UIButton);
    }
namespace TypeWrappersRegister{
    void UiButton()
    {
        TypeWrapperRegister_UIButton();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


