Build:
rm -rf build
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=cc ..
cmake --build .

Run:
LANG=ru_RU.UTF-8 ./I18n
LANG=en_EN.UTF-8 ./I18n
