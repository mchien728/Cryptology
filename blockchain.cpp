#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <fstream>

using namespace std;
using namespace CryptoPP;

inline const string toHex(const string str){
    string strHex;
    HexEncoder encoder;
    encoder.Attach(new StringSink(strHex));
    encoder.Put((const CryptoPP::byte*)str.c_str(), str.size());
    encoder.MessageEnd();
    return strHex;
}

int main(){
    ofstream out;
    out.open("out.txt", ios::out);
    string IDmsg = "112550198";
    string nonce(4, 0);                              // 32 bits in Hex
    string curHash(32, 0), prevHash, outputHash;     // SHA-256 length: 32字節
    SHA256 hash;
    hash.Update((const CryptoPP::byte*)IDmsg.data(), IDmsg.size());    // ID in ASCII
    hash.Final((CryptoPP::byte*)&curHash[0]);                          // byte = unsigned char

    unsigned int n = 0;
    int i, j;
    for(i=0; i<64; i++){
        n = 0;                          // n=前綴0數量
        prevHash = curHash;
        while(1){
            for(j=0; j<4; j++){
                nonce[j] = (char)(n >> 8*(3-j));
            }
            IDmsg = prevHash + nonce;
            hash.Update((const CryptoPP::byte*)IDmsg.data(), 36);
            hash.Final((CryptoPP::byte*)&curHash[0]);
            outputHash = toHex(curHash);
            n++;
            if(n == 0){
                break;
            }
            for(j=0; outputHash.c_str()[j] == '0'; j++);
            if(i == j){
                break;
            }
        }
        out << i << endl;
        out << toHex(prevHash) << endl;
        out << toHex(nonce) << endl;
        out << outputHash << endl;
    }
    return 0;
}