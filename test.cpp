#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace CryptoPP;

inline const string toHex(const string str){               // 先轉ascii再Hex
    string strHex;
    HexEncoder encoder;
    encoder.Attach(new StringSink(strHex));
    encoder.Put((const CryptoPP::byte*)str.c_str(), str.size());
    encoder.MessageEnd();
    return strHex;
}

int main(){
    string i;
    i = "cd";
    std::cout << toHex(i) << endl;
}