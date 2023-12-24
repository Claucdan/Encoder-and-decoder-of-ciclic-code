# Working with cyclic codes
<div id="badges">
<img src=https://img.shields.io/badge/CLion-grey?style=for-the-badge&logo=clion&logoColor=white></img>
 <img src=https://img.shields.io/badge/CMake-orange?style=for-the-badge&logo=cmake&logoColor=white></img>
 <img src=https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white></img>
 <img src=https://img.shields.io/badge/c++-black?style=for-the-badge&logo=c%2B%2B&logoColor=white></img>
 <img src=https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white></img>    
</div>

## Some Information
***
<div>
This program works with classic cyclic codes designed to find and fix errors in the code.<br>
This program is designed to encode and decode messages in different cyclic codes.
During the decoding process, the program finds and corrects one error.
</div>

## Encoding of message
***
The program implements systematic and non-systematic coding. Let's talk in more detail about each of the codes separately:
### Encoding of systematic code
***
```c++
std::string systematic(std::string& code, std::string& polynomial) {
    code.insert(code.size(), polynomial.size() - 1, '0');
    std::string ost = division_with_xor(code, polynomial);
    for (int i = 0; i < ost.size(); i++) {
        code[code.size() - 1 - i] = ost[ost.size() - i - 1];
    }
    return code;
}
```
### Encoding of antisystematic code
***
```c++
std::string anti_systematic(std::string& code, std::string& polynomial) {
    int size = code.size() + polynomial.size() - 1;
    std::string result; result.insert(0, size, '0');
    for (int i = 0; i < code.size(); i++) {
        if (code[i] == '0')
            continue;
        for (int j = 0; j < polynomial.size(); j++) {
            if (polynomial[j] == '1') {
                if (result[i + j] == '0')
                    result[i + j] = '1';
                else
                    result[i + j] = '0';
            }
        }
    }
    return result;
}
```
