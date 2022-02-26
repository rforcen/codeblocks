lib:
	@# @g++ -c -O3 -std=c++2a -I. VSL_compiler.cpp  MusicFreq.cpp FastSin.cpp ColorScale.cpp
	@g++ -c -O3 -std=c++2a -I. MusicFreq.cpp FastSin.cpp ColorScale.cpp
	@ar -r libvsl.a *.o > /dev/null
	@rm -fr *.o
	@cp libvsl.a ~/Documents/pas/audio/
test:
	@g++ -D_TEST -O3 -std=c++2a -I. VSL_compiler.cpp  MusicFreq.cpp FastSin.cpp ColorScale.cpp -o vsl
