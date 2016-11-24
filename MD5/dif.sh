g++ md5.cpp.back2.13.cpp -o md5my
g++ dl21.cpp -o md5dl -w
./md5my>md5my_out
./md5dl > md5dl_out
echo "left is my, right is dl"
diff md5my_out md5dl_out -y -W 200



