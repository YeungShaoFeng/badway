in_file='./include/PI64.h'
de_file='./out/decrypted.badway'
diff_dir='./diff'

mkdir -p $diff_dir

hexdump -C $in_file > $diff_dir/a
hexdump -C $de_file > $diff_dir/b

diff $in_file $de_file > $diff_dir/out.txt

