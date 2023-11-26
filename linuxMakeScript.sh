sudo apt-get update
sudo apt-get install cmake g++ -y
cmake . -Bbuild
make -C build
./build/AffineTransform
