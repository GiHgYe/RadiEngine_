#pragma once
#include "..\Runtime\include\audio\core\audio_listener.h"

class AudioListener;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeAudioListenerOperator{
    public:
        static const char* getClassName(){ return "AudioListener";}
        static void* constructorWithJson(const Json& json_context){
            AudioListener* ret_instance= new AudioListener;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(AudioListener*)instance);
        }
        // base class
        static int getAudioListenerBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Component,static_cast<AudioListener*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_AudioListener(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_AudioListener=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeAudioListenerOperator::getAudioListenerBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeAudioListenerOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeAudioListenerOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("AudioListener", class_function_tuple_AudioListener);
    }
namespace TypeWrappersRegister{
    void AudioListener()
    {
        TypeWrapperRegister_AudioListener();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


