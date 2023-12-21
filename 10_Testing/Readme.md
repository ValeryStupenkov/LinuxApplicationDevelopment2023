Build:

autoreconf -fisv && ./configure --enable-gcov && make

gcov report:
make gcov
