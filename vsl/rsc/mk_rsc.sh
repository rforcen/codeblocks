# make resource file
ld -r -b binary -o resources.o *.png *.ico
nm resources.o
nm -P resources.o | grep _size
