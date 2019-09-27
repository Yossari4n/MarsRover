#include "Model3D.h"

#include "../ResourcesManager.h"

Model3D::Model3D(std::string path, ResourcesManager& manager)
    : m_Path(path) {
    Load(manager);
}

void Model3D::Load(ResourcesManager& manager) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(m_Path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        // TODO DebugLog
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';

        // TODO Load ErrorMesh
        return;
    }

    std::string directory = m_Path.substr(0, m_Path.find_last_of('/'));
    m_Meshes.reserve(scene->mNumMeshes);
    LoadNode(scene->mRootNode, scene, directory, manager);
}

void Model3D::LoadNode(const aiNode* node, const aiScene* scene, std::string directory, ResourcesManager& manager) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        LoadMesh(scene->mMeshes[node->mMeshes[i]], scene, directory, manager);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        LoadNode(node->mChildren[i], scene, directory, manager);
    }
}

void Model3D::LoadMesh(const aiMesh* mesh, const aiScene* scene, std::string directory, ResourcesManager& manager) {
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Load vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Mesh::Vertex vertex;

        vertex.Position.x = mesh->mVertices[i].x;
        vertex.Position.y = mesh->mVertices[i].y;
        vertex.Position.z = mesh->mVertices[i].z;

        vertex.Normal.x = mesh->mNormals[i].x;
        vertex.Normal.y = mesh->mNormals[i].y;
        vertex.Normal.z = mesh->mNormals[i].z;

        // Check if mesh contains texture coordinates
        if (mesh->mTextureCoords[0]) {
            vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
            vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
        } // else TextCoords are initialized to vec2(0.0f)

        vertices.push_back(vertex);
    }

    // Load indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // Load material
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // Load diffuse textures
        auto count = material->GetTextureCount(aiTextureType_DIFFUSE);
        textures.reserve(count + material->GetTextureCount(aiTextureType_SPECULAR));
        for (unsigned int i = 0; i < count; i++) {
            aiString path;
            material->GetTexture(aiTextureType_DIFFUSE, i, &path);
            textures.push_back(manager.GetTexture(directory + "/n" + path.C_Str()));
        }

        // Load specular textures
        count = material->GetTextureCount(aiTextureType_SPECULAR);
        for (unsigned int i = 0; i < count; i++) {
            aiString path;
            material->GetTexture(aiTextureType_SPECULAR, i, &path);
            textures.push_back(manager.GetTexture(directory + "/n" + path.C_Str()));
        }
    }

    m_Meshes.emplace_back(vertices, indices, textures);
}
