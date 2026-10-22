#include "validator.h"
#include <string>
bool isValidNumber(const std::string&s){ 
    if(s.empty()){
        return false;
    }
    std::size_t i=0;
    if (s[i] =='+' || s[i]=='-'){
       i++;
    }
    if(i>=s.length() || s[i]<'0'|| s[i] >'9'){
        return false;
    }
    while (i<s.length() && s[i]>= '0' && s[i] <= '9'){
        i++;
    }
    if (i<s.length()&& s[i] == '.'){
        i++;
        if (i>=s.length() || s[i]< '0'|| s[i]>'9'){
            return false;
        }
        while (i<s.length()&& s[i] >= '0' && s[i]<='9'){
            i++;
        }
    }
    return i == s.length();
}

