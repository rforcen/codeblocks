# make resources files
ld -r -b binary -o depthMaps.o depthMaps/*.jpg depthMaps/*.png
nm depthMaps.o

ld -r -b binary -o texturePatterns.o texturePatterns/*.jpg texturePatterns/*.png
nm texturePatterns.o

