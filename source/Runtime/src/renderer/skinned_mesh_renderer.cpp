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
//    //������ȡ MeshFilter ���
//    MeshFilter* mesh_filter = game_object()->GetComponent<MeshFilter>();
//    if (!mesh_filter) {
//        LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get MeshFilter component");
//        return;
//    }
//    //��ȡ Mesh
//    auto mesh = mesh_filter->mesh();
//    if (!mesh) {
//        LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get Mesh");
//        return;
//    }
//    //��ȡ������������������飬����Ϊ�������
//    auto vertex_relate_bone_index_vec = mesh_filter->vertex_relate_bone_index_vec();
//    if (vertex_relate_bone_index_vec.empty()) {
//        LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get vertex relate bone index");
//        return;
//    }
//
//    //������ȡ Animation ���
//    Animation* animation = game_object()->GetComponent<Animation>();
//    if (!animation) {
//        LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get Animation component");
//        return;
//    }
//    //��ȡ��ǰ���ŵ� AnimationClip
//    auto animation_clip = animation->current_animation_clip();
//    if (!animation_clip) {
//        LOG_ERROR("SkinnedMeshRenderer::Update() failed, can't get current AnimationClip");
//        return;
//    }
//    //��ȡ��ǰ֡���µĹ�������
//    std::vector<Matrix4x4>& bone_matrices = animation_clip->GetCurrentFrameBoneMatrix();
//    //��ȡ SkinnedMesh
//    MeshFilter::Mesh* skinned_mesh = mesh_filter->skinned_mesh();
//    if (skinned_mesh == nullptr) {
//        //����Mesh����
//        skinned_mesh = static_cast<MeshFilter::Mesh*>(malloc(mesh->size()));
//        memcpy(skinned_mesh, mesh, mesh->size());
//        mesh_filter->set_skinned_mesh(skinned_mesh);
//
//        //������������ vertex_data_
//        skinned_mesh->vertex_data = static_cast<MeshFilter::Vertex*>(malloc(mesh->vertex_num * sizeof(MeshFilter::Vertex)));
//        memcpy(skinned_mesh->vertex_data, mesh->vertex_data, mesh->vertex_num * sizeof(MeshFilter::Vertex));
//    }
//    //���㵱ǰ֡����λ��
//    for (int i = 0; i < skinned_mesh->vertex_num; i++) {
//        auto& vertex = mesh->vertex_data[i];
//        auto& bone_index = vertex_relate_bone_index_vec[i];
//
//        //��ȡ��ǰ��������Ĺ���T-Pos����
//        Matrix4x4& bone_t_pose_matrix = animation_clip->GetBoneTPose(bone_index);
//        //��ȡT-Pos����������
//        Matrix4x4 bone_t_pose_matrix_inverse = bone_t_pose_matrix.Inverse();
//        //����������ת���������ռ�
//        Vector4 vertex_position = bone_t_pose_matrix_inverse * Vector4(vertex.position, 1.0f);
//
//        //��ǰ֡��������Ĺ�������
//        auto& bone_matrix = bone_matrices[bone_index];
//        //���㵱ǰ֡����λ��(ģ������ϵ��bone_matrix����������ģ������ϵ��λ�ã����õ���������ϵ��λ���ϣ���ת������ģ������ϵ)
//        Vector4 pos_in_world = bone_matrix * vertex_position;
//
//        skinned_mesh->vertex_data[i].position = Vector3{ pos_in_world.x,pos_in_world.y,pos_in_world.z };
//    }
//}
//
//SkinnedMeshRenderer::~SkinnedMeshRenderer() {
//
//}