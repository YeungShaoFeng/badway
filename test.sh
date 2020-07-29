#in_file="./test/test.mp3"
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
echo "=== diffs btw $in_file and $de_file ==="
# sha sum
shasum -a 256 $en_file $in_file $de_file

# show the differences between $in_file and $de_file.
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
#rm -rf $diff_dir $in_file.h
#rm -rf CMakeCache.txt Makefile cmake-build-debug out CMakeFiles cmake_install.cmake badway


# Linux localhost 4.14.117-perf-g509c074 #1 SMP PREEMPT Wed Apr 8 03:32:01 CST 2020 arrch64 Android
OS=`uname -a`
if [ `echo $OS | grep -c "cen" ` -gt 0 ]
then echo "Success"
elif [ `echo $OS | grep -c "Darwin" ` -gt 0 ]
then echo "Darwin"
elif [ `echo $OS | grep -c "cen" ` -gt 0 ]
then echo "Success"
fi