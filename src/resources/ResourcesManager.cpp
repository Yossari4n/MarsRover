#include "ResourcesManager.h"

ResourcesManager::~ResourcesManager() {
    for (auto& [key, texture] : m_Textures) {
        texture.Free();
    }

    for (auto& [key, model] : m_Models) {
        model.Free();
    }
}

Texture& ResourcesManager::GetTexture(std::string path) {
    if (m_Textures.find(path) == m_Textures.end()) {
        int width, height, components;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &components, 0);

        if (!data) {
            Logger::Instance().ErrorLog(Logger::ESender::Resources, "Failed to load texture %s", path.c_str());
            data = stbi_load(ERROR_TEXTURE_PATH, &width, &height, &components, 0);
        }

        m_Textures.try_emplace(path, data, width, height, components);
        stbi_image_free(data);
    }

    // Using .at instead of operator[] because Texture does not have default ctor
    return m_Textures.at(path);
}


Model3D& ResourcesManager::GetModel3D(std::string path) {
    if (m_Models.find(path) == m_Models.end()) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            Logger::Instance().ErrorLog(Logger::ESender::Resources, "Failed to load model %s:\n%s", path.c_str(), importer.GetErrorString());
            scene = importer.ReadFile(ERROR_MODEL3D_PATH, aiProcess_Triangulate | aiProcess_FlipUVs);
        }

        std::string directory = path.substr(0, path.find_last_of('/'));
        m_Models.try_emplace(path, LoadNode(scene->mRootNode, scene, directory));
    }

    // Using .at instead of operator[] because Model3D does not have default ctor
    return m_Models.at(path);
}

std::vector<Mesh> ResourcesManager::LoadNode(const aiNode* node, const aiScene* scene, std::string directory) {
    std::vector<Mesh> meshes;
    
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        meshes.push_back(LoadMesh(scene->mMeshes[node->mMeshes[i]], scene, directory));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        auto tmp = LoadNode(node->mChildren[i], scene, directory);
        meshes.insert(meshes.end(),
                      std::make_move_iterator(tmp.begin()),
                      std::make_move_iterator(tmp.end()));
    }

    return meshes;
}

Mesh ResourcesManager::LoadMesh(const aiMesh* mesh, const aiScene* scene, std::string directory) {
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
        textures.reserve(static_cast<size_t>(count) + static_cast<size_t>(material->GetTextureCount(aiTextureType_SPECULAR)));
        for (unsigned int i = 0; i < count; i++) {
            aiString path;
            material->GetTexture(aiTextureType_DIFFUSE, i, &path);
            textures.push_back(GetTexture(directory + '/' + path.C_Str()));
            textures.back().Type(Texture::EType::Diffuse);
        }

        // Load specular textures
        count = material->GetTextureCount(aiTextureType_SPECULAR);
        for (unsigned int i = 0; i < count; i++) {
            aiString path;
            material->GetTexture(aiTextureType_SPECULAR, i, &path);
            textures.push_back(GetTexture(directory + '/' + path.C_Str()));
            textures.back().Type(Texture::EType::Specular);
        }
    }

    return Mesh(vertices, indices, textures);
}
