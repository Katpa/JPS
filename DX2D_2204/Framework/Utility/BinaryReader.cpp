#include "Framework.h"

BinaryReader::BinaryReader(string filePath)
    : size(0)
{
    file = CreateFileA(filePath.c_str(), GENERIC_READ,
        FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
}

BinaryReader::BinaryReader(wstring filePath)
    : size(0)
{
    file = CreateFile(filePath.c_str(), GENERIC_READ,
        FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
}

BinaryReader::~BinaryReader()
{
    CloseHandle(file);
}

int BinaryReader::Int()
{
    int temp;
    ReadFile(file, &temp, sizeof(int), &size, nullptr);

    return temp;
}

UINT BinaryReader::UInt()
{
    UINT temp;
    ReadFile(file, &temp, sizeof(UINT), &size, nullptr);

    return temp;
}

float BinaryReader::Float()
{
    float temp;
    ReadFile(file, &temp, sizeof(float), &size, nullptr);

    return temp;
}

string BinaryReader::String()
{
    UINT strSize = UInt();

    char* temp = new char[strSize + 1];
    ReadFile(file, temp, sizeof(char) * strSize, &size, nullptr);
    temp[strSize] = '\0';

    return temp;
}

wstring BinaryReader::WString()
{
    UINT strSize = UInt();

    WCHAR* temp = new WCHAR[strSize + 1];
    ReadFile(file, temp, sizeof(WCHAR) * strSize, &size, nullptr);
    temp[strSize] = '\0';

    return temp;
}

Vector2 BinaryReader::Vector()
{
    Vector2 temp;
    ReadFile(file, &temp, sizeof(Vector2), &size, nullptr);

    return temp;
}

void BinaryReader::Byte(void** data, UINT dataSize)
{
    ReadFile(file, *data, dataSize, &size, nullptr);
}
