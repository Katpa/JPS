#include "Framework.h"

unordered_map<wstring, Shader*> Shader::shaders;

Shader::Shader() : blob(nullptr)
{
}

Shader::~Shader()
{
    blob->Release();
}

VertexShader* Shader::AddVS(wstring file)
{
    if (shaders.count(file) > 0)
        return (VertexShader*)shaders[file];
        
    shaders[file] = new VertexShader(file);    

    return (VertexShader*)shaders[file];
}

PixelShader* Shader::AddPS(wstring file)
{    
    if (shaders.count(file) > 0)
        return (PixelShader*)shaders[file];

    shaders[file] = new PixelShader(file);

    return (PixelShader*)shaders[file];
}

void Shader::Delete()
{
    for (pair<wstring, Shader*> shader : shaders)
        delete shader.second;
}
