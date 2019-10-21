#include "RawModel.h"

#include "../ResourcesManager.h"

RawModel::RawModel(std::string path, ResourcesManager& manager)
    : m_Path(path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        Logger::Instance().ErrorLog(Logger::ESender::Resources, "Failed to load model %s:\n%s", path.c_str(), importer.GetErrorString());
        scene = importer.ReadFile(ERROR_MODEL3D_PATH, aiProcess_Triangulate | aiProcess_FlipUVs);
    }

    std::string directory = path.substr(0, path.find_last_of('/'));
    m_RawMeshes.reserve(scene->mNumMeshes);
    LoadNode(scene->mRootNode, scene, directory, manager);
}

void RawModel::LoadNode(const aiNode* node, const aiScene* scene, const std::string& directory, ResourcesManager& manager) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        LoadMesh(scene->mMeshes[node->mMeshes[i]], scene, directory, manager);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        LoadNode(node->mChildren[i], scene, directory, manager);
    }
}

void RawModel::LoadMesh(const aiMesh* mesh, const aiScene* scene, const std::string& directory, ResourcesManager& manager) {
    std::vector<RawMesh::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<RawTexture*> diffuse;
    std::vector<RawTexture*> specular;
    float shininess = 1.0f;

    // Load vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        RawMesh::Vertex vertex;

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

        // Load diffuse texture
        aiString path;
        unsigned int count = material->GetTextureCount(aiTextureType_DIFFUSE);
        diffuse.reserve(count);
        for (unsigned int i = 0; i < count; i++) {
            material->GetTexture(aiTextureType_DIFFUSE, i, &path);
            diffuse.push_back(&manager.GetTexture(directory + "/" + path.C_Str()));
        }

        // Load specular texture
        count = material->GetTextureCount(aiTextureType_SPECULAR);
        specular.reserve(count);
        for (unsigned int i = 0; i < count; i++) {
            material->GetTexture(aiTextureType_SPECULAR, i, &path);
            specular.push_back(&manager.GetTexture(directory + "/" + path.C_Str()));
        }

        // Load shininess
        float strength = 1.0f;
        material->Get(AI_MATKEY_SHININESS, shininess);
        material->Get(AI_MATKEY_SHININESS_STRENGTH, strength);
        shininess = shininess * strength;
    }

    m_RawMeshes.emplace_back(vertices, indices, diffuse, specular, shininess);
}