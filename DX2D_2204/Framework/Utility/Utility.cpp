#include "Framework.h"

vector<string> Utility::SplitString(string origin, string tok)
{
    vector<string> result;

    size_t cutAt = 0;

    while ((cutAt = origin.find_first_of(tok)) != origin.npos)
    {
        if (cutAt > 0)
            result.push_back(origin.substr(0, cutAt));

        origin = origin.substr(cutAt + tok.length());
    }

    result.push_back(origin);

    return result;
}

void Utility::Replace(string* origin, string comp, string rep)
{
    string temp = *origin;

    size_t at = 0;
    while ((at = temp.find(comp, at)) != string::npos)
    {
        temp.replace(at, comp.length(), rep);
        at += rep.length();
    }

    *origin = temp;
}

string Utility::ToString(wstring str)
{
    string temp;
    temp.assign(str.begin(), str.end());

    return temp;
}

wstring Utility::ToWString(string str)
{
    wstring temp;
    temp.assign(str.begin(), str.end());

    return temp;
}
