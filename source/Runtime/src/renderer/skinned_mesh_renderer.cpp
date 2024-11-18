//#include "renderer/skinned_mesh_renderer.h"
//#include "component/game_object.h"
//#include "renderer/mesh_filter.h"
//#include "renderer/animation.h"
//#include "renderer/animation_clip.h"
//#include "utils/debug.h"
//
//SkinnedMeshRenderer::SkinnedMeshRenderer() :MeshRenderer() {
//
//}
//
//void SkinnedMeshRenderer::Update() {
//    //主动获取 MeshFilter 组件
//    MeshFilter* mesh_filter = game_object()->GetComponent<MeshFilter>();
//    if (!mesh_filter) {
//        LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get MeshFilter component");
//        return;
//    }
//    //获取 Mesh
//    auto mesh = mesh_filter->mesh();
//    if (!mesh) {
//        LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get Mesh");
//        return;
//    }
//    //获取顶点关联骨骼索引数组，长度为顶点个数
//    auto vertex_relate_bone_index_vec = mesh_filter->vertex_relate_bone_index_vec();
//    if (vertex_relate_bone_index_vec.empty()) {
//        LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get vertex relate bone index");
//        return;
//    }
//
//    //主动获取 Animation 组件
//    Animation* animation = game_object()->GetComponent<Animation>();
//    if (!animation) {
//        LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get Animation component");
//        return;
//    }
//    //获取当前播放的 AnimationClip
//    auto animation_clip = animation->current_animation_clip();
//    if (!animation_clip) {
//        LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get current AnimationClip");
//        return;
//    }
//    //获取当前帧最新的骨骼矩阵
//    std::vector<Matrix4x4>& bone_matrices = animation_clip->GetCurrentFrameBoneMatrix();
//    //获取 SkinnedMesh
//    MeshFilter::Mesh* skinned_mesh = mesh_filter->skinned_mesh();
//    if (skinned_mesh == nullptr) {
//        //拷贝Mesh整体
//        skinned_mesh = static_cast<MeshFilter::Mesh*>(malloc(mesh->size()));
//        memcpy(skinned_mesh, mesh, mesh->size());
//        mesh_filter->set_skinned_mesh(skinned_mesh);
//
//        //拷贝顶点数据 vertex_data_
//        skinned_mesh->vertex_data = static_cast<MeshFilter::Vertex*>(malloc(mesh->vertex_num * sizeof(MeshFilter::Vertex)));
//        memcpy(skinned_mesh->vertex_data, mesh->vertex_data, mesh->vertex_num * sizeof(MeshFilter::Vertex));
//    }
//    //计算当前帧顶点位置
//    for (int i = 0; i < skinned_mesh->vertex_num; i++) {
//        auto& vertex = mesh->vertex_data[i];
//        auto& bone_index = vertex_relate_bone_index_vec[i];
//
//        //获取当前顶点关联的骨骼T-Pos矩阵
//        Matrix4x4& bone_t_pose_matrix = animation_clip->GetBoneTPose(bone_index);
//        //获取T-Pos矩阵的逆矩阵
//        Matrix4x4 bone_t_pose_matrix_inverse = bone_t_pose_matrix.Inverse();
//        //将顶点坐标转换到骨骼空间
//        Vector4 vertex_position = bone_t_pose_matrix_inverse * Vector4(vertex.position, 1.0f);
//
//        //当前帧顶点关联的骨骼矩阵
//        auto& bone_matrix = bone_matrices[bone_index];
//        //计算当前帧顶点位置(模型坐标系，bone_matrix里带了相对于模型坐标系的位置，作用到骨骼坐标系的位置上，就转换到了模型坐标系)
//        Vector4 pos_in_world = bone_matrix * vertex_position;
//
//        skinned_mesh->vertex_data[i].position = Vector3{ pos_in_world.x,pos_in_world.y,pos_in_world.z };
//    }
//}
//
//SkinnedMeshRenderer::~SkinnedMeshRenderer() {
//
//}