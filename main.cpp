#include <iostream>

void xor_string(std::string& code,std::string& polynomial){
    for(int i=0;i<code.size();i++){
        switch (code[i]+polynomial[i]-48*2) {
            case 2:
            case 0:
                code[i]='0';
                break;
            case 1:
                code[i]='1';
                break;

        }
    }
    int i=0;
    while(i<code.size() && code[i]=='0')i++;
    code=code.substr(i);
}
std::string division_with_xor(std::string code,std::string& polynomial){
    std::string del="";
    while(code.size()+del.size()>=polynomial.size()){
        int size=del.size();
        del+=code.substr(0,polynomial.size()-size);
        code=code.substr(polynomial.size()-size);
        if(del[0]=='1')
            xor_string(del,polynomial);
        else
            del=del.substr(1);
    }
    if(!code.empty())
        del+=code;
    int i=0;
    while(i<del.size() && del[i]=='0')i++;
    del=del.substr(i);
    return del;
}


void cdvig(std::string& code,int count_cdvig){
    count_cdvig=code.size()-count_cdvig;
    char buffer[count_cdvig];
    for(int i=0;i<count_cdvig;i++)
        buffer[i]=code[i];
    for(int i=0;i<code.size()-count_cdvig;i++){
        code[i]=code[i+count_cdvig];
    }
    for(int i=0;i<count_cdvig;i++)
        code[code.size()-count_cdvig+i]=buffer[i];
}
std::string systematic(std::string& code,std::string& polynomial){
    code.insert(code.size(),polynomial.size()-1,'0');
    std::string ost= division_with_xor(code,polynomial);
    for(int i=0;i<ost.size();i++){
        code[code.size()-1-i]=ost[ost.size()-i-1];
    }
    return code;
}
bool is_correct_systematic_code(std::string& code,std::string& polynomial){
    std::string ost= division_with_xor(code,polynomial);
    return ost.empty();
}
std::string decoder_systematic_code(std::string code,std::string& polynomial){
    if(is_correct_systematic_code(code,polynomial)){
       code=code.substr(0,code.size()-polynomial.size()+1);
        return code;
    }
    else{
        std::string ost= division_with_xor(code,polynomial);
        int dvig=0;
        while(ost!="1" && ost!="10" && ost!="100"){
            dvig++;

            char tmp=code[0];
            for(int i=0;i<code.size()-1;i++){
                code[i]=code[i+1];
            }
            code[code.size()-1]=tmp;

            ost= division_with_xor(code,polynomial);
        }
        switch (ost.size()) {
            case 1:
                if(code[code.size()-1]=='0')
                    code[code.size()-1]='1';
                else
                    code[code.size()-1]='0';
                break;
            case 2:
                if(code[code.size()-2]=='0')
                    code[code.size()-2]='1';
                else
                    code[code.size()-2]='0';
                break;
            case 3:
                if(code[code.size()-3]=='0')
                    code[code.size()-3]='1';
                else
                    code[code.size()-3]='0';
                break;
        }
        cdvig(code,dvig);
        return code;
    }
}

int main() {
    std::string code;
    std::string polynomial;
    std::cin>>code>>polynomial;
    std::string encode_systematic=systematic(code,polynomial);
    std::cout<<encode_systematic<<"\n";
    std::string decode= decoder_systematic_code(encode_systematic,polynomial);
    std::cout<<decode;

    return 0;
}
