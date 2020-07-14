rm -rf ./tmp include/PI64.h
python3 src/makePI64_h.py

cmake . && make

./badway -e -i ./include/PI64.h -o ./tmp/encrypted -p 91CBD30f3d1496 -l 4
./badway -d -i ./tmp/encrypted -o ./tmp/decrypted -p 91CBD30f3d1496 -l 4

shasum -a 256 ./tmp/encrypted ./include/PI64.h ./tmp/decrypted
