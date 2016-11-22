g++ aesdl.cpp -o aesdl
g++ aes.cpp -o aes
./aesdl>aesdl_out
./aes > aes_out
echo "left is dl, right is aes"
diff aesdl_out aes_out -y -W 200


