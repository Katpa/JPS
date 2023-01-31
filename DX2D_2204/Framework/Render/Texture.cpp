#include "Framework.h"

unordered_map<wstring, Texture*> Texture::textures;

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
    : srv(srv), image(move(image))
{
}

Texture::~Texture()
{
    srv->Release();
}

Texture* Texture::Add(wstring file)
{
    if (textures.count(file) > 0)
        return textures[file];

    ScratchImage image;
    LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    ID3D11ShaderResourceView* srv;

    CreateShaderResourceView(DEVICE, image.GetImages(),
        image.GetImageCount(), image.GetMetadata(), &srv);

    Texture* texture = new Texture(srv, image);

    textures[file] = texture;

    return texture;
}

Texture* Texture::Add(wstring key, ID3D11ShaderResourceView* srv)
{
    if (textures.count(key) > 0)
        return textures[key];

    ScratchImage image;
    Texture* texture = new Texture(srv, image);

    textures[key] = texture;

    return texture;
}

void Texture::Delete()
{
    for (pair<wstring, Texture*> texture : textures)
        delete texture.second;
}

void Texture::PSSet(UINT slot)
{
    DC->PSSetShaderResources(slot, 1, &srv);
}

Vector2 Texture::GetSize()
{
    return Vector2(image.GetMetadata().width, image.GetMetadata().height);
}
