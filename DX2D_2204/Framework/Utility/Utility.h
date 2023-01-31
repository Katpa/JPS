#pragma once

namespace Utility
{
    vector<string> SplitString(string origin, string tok);
    void Replace(string* origin, string comp, string rep);

    string ToString(wstring str);
    wstring ToWString(string str);
};