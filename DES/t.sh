g++ des.cpp -o des
g++ dl.cpp -o dl
./dl > dl_out
./des>des_out
echo "left is dl, right is des"
diff dl_out des_out -y -W 200

