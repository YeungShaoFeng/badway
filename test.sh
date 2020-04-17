cmake .
make

rm -rf ./tmp

./badway -e -i ./include/PI64 -o ./tmp/encrypted -p Linxi
./badway -d -i ./tmp/encrypted -o ./tmp/decrypted -p Linxi

shasum -a 256 ./tmp/encrypted ./include/PI64 ./tmp/decrypted
