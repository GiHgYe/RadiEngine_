#pragma once
#include "..\Runtime\include\renderer\skinned_mesh_renderer.h"

class SkinnedMeshRenderer;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeSkinnedMeshRendererOperator{
    public:
        static const char* getClassName(){ return "SkinnedMeshRenderer";}
        static void* constructorWithJson(const Json& json_context){
            SkinnedMeshRenderer* ret_instance= new SkinnedMeshRenderer;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(SkinnedMeshRenderer*)instance);
        }
        // base class
        static int getSkinnedMeshRendererBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(MeshRenderer,static_cast<SkinnedMeshRenderer*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_SkinnedMeshRenderer(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_SkinnedMeshRenderer=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeSkinnedMeshRendererOperator::getSkinnedMeshRendererBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeSkinnedMeshRendererOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeSkinnedMeshRendererOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("SkinnedMeshRenderer", class_function_tuple_SkinnedMeshRenderer);
    }
namespace TypeWrappersRegister{
    void SkinnedMeshRenderer()
    {
        TypeWrapperRegister_SkinnedMeshRenderer();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


