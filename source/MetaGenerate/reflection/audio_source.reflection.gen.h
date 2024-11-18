#pragma once
#include "..\Runtime\include\audio\core\audio_source.h"

class AudioSource;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeAudioSourceOperator{
    public:
        static const char* getClassName(){ return "AudioSource";}
        static void* constructorWithJson(const Json& json_context){
            AudioSource* ret_instance= new AudioSource;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(AudioSource*)instance);
        }
        // base class
        static int getAudioSourceBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Component,static_cast<AudioSource*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_AudioSource(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_AudioSource=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeAudioSourceOperator::getAudioSourceBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeAudioSourceOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeAudioSourceOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("AudioSource", class_function_tuple_AudioSource);
    }
namespace TypeWrappersRegister{
    void AudioSource()
    {
        TypeWrapperRegister_AudioSource();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


