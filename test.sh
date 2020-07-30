in_file="./include/PI64"
en_file="./out/encrypted.badway"
de_file="./out/decrypted.badway"
PASSWORD="e6b35253f56cecf2"
log_level="4"

# make the $in_file.
python3 src/makePI64_h.py

# make the project.
cmake . && make

# test.
./badway -e -i $in_file -o $en_file -p $PASSWORD -l $log_level
./badway -d -i $en_file -o $de_file -p $PASSWORD -l $log_level

echo "============================================================="
echo "--- shasum ---"
# echo "shaxxxsum[0] | shasum -a 256[1]"
# read -p "shasum type: " shasum_type
#shasum type
xxx='256'
shasum_a_xxx='shasum -a '$xxx
shaxxxsum='sha'$xxx'sum'
shasum_func=$shaxxxsum
# OS type
if   [[ "$OSTYPE" == "linux-gnu"* ]]; then
    shasum_func=$shaxxxsum
elif [[ "$OSTYPE" == "darwin"* ]]; then
    shasum_func=$shasum_a_xxx
elif [[ "$OSTYPE" == "cygwin"* ]]; then
    shasum_func=$shasum_a_xxx
elif [[ "$OSTYPE" == "msys"* ]]; then
    shasum_func=$shasum_a_xxx
elif [[ "$OSTYPE" == "freebsd"* ]]; then
    shasum_func=$shasum_a_xxx
elif [[ "$OSTYPE" == *"andriod"* ]]; then
    shasum_func=$shaxxxsum        
else
    echo "unknown OSTYPE"
fi

shasum_in_file=`$shasum_func $in_file`
shasum_en_file=`$shasum_func $en_file`
shasum_de_file=`$shasum_func $de_file`
echo "$shasum_en_file"
echo "$shasum_in_file"
echo "$shasum_de_file"
if [ "${shasum_de_file% *}" = "${shasum_in_file% *}" ]; then
#if [ "${shasum_de_file:0:16}" = "${shasum_in_file:0:16}" ]; then
    echo "shasums are equal. [$in_file $de_file]"
else
    echo "shasums are not equal. [$in_file $de_file]"
fi

# show the differences between $in_file and $de_file.
echo ""
echo "--- diffs btw $in_file and $de_file ---"
diff_dir='./diff'
diff_out_file=$diff_dir/out.txt
mkdir -p $diff_dir

hexdump -C $in_file > $diff_dir/a
hexdump -C $de_file > $diff_dir/b

diff $in_file $de_file > $diff_out_file
echo "### diffs ###"
head $diff_out_file
echo "### diffs ###"
echo "============================================================="

# clean up.
rm -rf $diff_dir out
rm -rf CMakeCache.txt Makefile cmake-build-debug CMakeFiles cmake_install.cmake badway
