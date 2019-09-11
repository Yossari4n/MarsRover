#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(const std::string& path, ShaderProgram::Type type)
    : Drawable(type) {
    LoadModel(path);
}

void MeshRenderer::Initialize() {
    Object().Scene().RegisterDrawCall(this);
}

void MeshRenderer::Destroy() {
    Object().Scene().UnregisterDrawCall(this);
}

void MeshRenderer::Draw(const ShaderProgram &shader) const {
    shader.Uniform("model", Model);
    
    for (const Mesh &mesh: m_Meshes) {
        mesh.Draw(shader);
    }
}

void MeshRenderer::LoadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
        return;
    }
    
    m_Directory = path.substr(0, path.find_last_of('/'));
    m_Meshes.reserve(scene->mRootNode->mNumMeshes);
    ProcessNode(scene->mRootNode, scene);
}

void MeshRenderer::ProcessNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene);
    }
    
    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        ProcessNode(node->mChildren[i], scene);
    }
}

void MeshRenderer::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;

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

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // Does mesh contains material
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    m_Meshes.emplace_back(vertices, indices, textures);
}

std::vector<Texture> MeshRenderer::LoadMaterialTextures(aiMaterial *material, aiTextureType type, const std::string& type_name) const {
    std::vector<Texture> textures;
    
    for (unsigned int i = 0; i < material->GetTextureCount(type); ++i) {
        aiString string;
        material->GetTexture(type, i, &string);
        
        Texture texture;
        texture.ID = TextureFromFile(string.C_Str(), m_Directory);
        texture.Type = type_name;
        texture.Path = string.C_Str();
        textures.push_back(texture);
    }
    
    return textures;
}

unsigned int MeshRenderer::TextureFromFile(const char *path, const std::string &directory) const {
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    GLuint id;
    glGenTextures(1, &id);

    int width, height, components;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &components, 0);
    if (data) {
        GLenum format = 0;
        if (components == 1) {
            format = GL_RED;
        } else if (components == 3) {
            format = GL_RGB;
        } else if (components == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        if (components > 3) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
    }

    stbi_image_free(data);

    return id;
}
