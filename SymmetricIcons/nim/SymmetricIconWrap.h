// Symmetric Icon.nim wrap
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <cstddef>
#include <vector>

using std::vector;

typedef float float32;
typedef uint32_t uint32;
typedef size_t nint;
typedef void *SymmetricIconsNim;

extern "C" {
    SymmetricIconsNim newSymmIcon(int len, int preset, uint32 color_set);
    void generateSymmIcon(SymmetricIconsNim  si, int iters);
    nint getImageSize(SymmetricIconsNim  si);
    void getImage(SymmetricIconsNim  si, void*image);
    void writeImage(SymmetricIconsNim  si, void*image, const char*name);
};

#ifdef ___TEST
int main() {
    auto si = newSymmIcon(1024*2, 8, 0);
    generateSymmIcon(si, 20000000);
    printf("image size:%ld\n", getImageSize(si));

    vector<uint32>image(getImageSize(si));
    getImage(si, image.data());
    writeImage(si, image.data(), "testSI.png");

    return 1;
}
#endif
