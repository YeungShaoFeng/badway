in_file="./include/PI64"
en_file="./out/encrypted.badway"
de_file="./out/decrypted.badway"
PASSWORD="e6b35253f56cecf2"
log_level="4"
diff_dir='./diff'

# clean up
cleanup() {
    rm -rf $diff_dir out include/PI64.h
    rm -rf CMakeCache.txt Makefile cmake-build-debug CMakeFiles cmake_install.cmake badway badway.cbp
}

# make the $in_file.
python3 src/makePI64_h.py

# make the project.
cmake . && make

# test.
./badway -e -i $in_file -o $en_file -p $PASSWORD -l $log_level
./badway -d -i $en_file -o $de_file -p $PASSWORD -l $log_level

#shasum type
xxx='256'
shasum_a_xxx='shasum -a '$xxx
shaxxxsum='sha'$xxx'sum'
shasum_func=$shaxxxsum
# switch shasum according to the OSTYPE
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

# repeat "string" times
repeat () {
    # seq  -f $1 -s '' $2; echo
    python3 -c 'print("'$1'"*'$2')'
}

length_shasum_en_file=${#shasum_en_file}
window_columns=`stty size | cut -d" " -f2`
# decide how many '=' will be printed. 
if (( length_shasum_en_file < window_columns)); then
    repeat_times=$length_shasum_en_file
else
    repeat_times=$window_columns
fi
repeat "=" $repeat_times

echo "--- shasums ---"
echo
echo "$shasum_en_file"
echo "$shasum_in_file"
echo "$shasum_de_file"
if [ "${shasum_de_file% *}" = "${shasum_in_file% *}" ]; then
#if [ "${shasum_de_file:0:16}" = "${shasum_in_file:0:16}" ]; then
    echo
    echo "--- shasums are equal [$in_file $de_file] ---"
else
    echo
    echo "!!! shasums are not equal [$in_file $de_file] !!!"
    # show the differences between $in_file and $de_file.
    # diff.sh
    echo
    echo "--- diffs btw $in_file and $de_file ---"
    diff_out_file=$diff_dir/out.txt
    mkdir -p $diff_dir

    hexdump -C $in_file > $diff_dir/a
    hexdump -C $de_file > $diff_dir/b

    diff $in_file $de_file > $diff_out_file
    echo "### diffs ###"
    head $diff_out_file
    echo "### diffs ###"
fi
repeat "=" $repeat_times

# clean up.
cleanup