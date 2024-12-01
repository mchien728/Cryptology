blockchain: blockchain.cpp
	g++ -I. -Icryptopp blockchain.cpp cryptopp/libcryptopp.a -std=c++11 -O2 -o blockchain