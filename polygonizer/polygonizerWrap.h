#ifndef POLYGONIZERWRAP_H_INCLUDED
#define POLYGONIZERWRAP_H_INCLUDED

#include <vector>
#include <string>

using std::string, std::vector;

typedef void* pPolygonizer;

typedef struct
{
    float x,y,z;
} Point;
typedef struct
{
    Point pos, norm, uv, color;
} Vertex;
typedef struct
{
    int i1,i2,i3;
} Triangle;

extern "C" { // nim wrapper
    typedef float(vec3Func)(float x, float y, float z);

    pPolygonizer CreatePolygonizer(float bounds, int idiv, vec3Func func);
    void freePolygonizer(pPolygonizer &polyg);
    void writeCTM(pPolygonizer polyg, const char*name);
    int getNVertex(pPolygonizer polyg);
    int getNTrigs(pPolygonizer polyg);
    void getMesh(pPolygonizer polyg, Vertex*vertexes, Triangle*trigs);


// implicit funcs
    vec3Func Sphere, Blob, NordstarndWeird, DecoCube, Cassini, Orth, Orth3,
             Pretzel, Tooth, Pilz, Bretzel, BarthDecic, Clebsch0, Clebsch,
             Chubs, Chair, Roman, TangleCube, Goursat, Sinxyz;

//    float Sphere(float x, float y, float z);


};


class Polygonizer
{
public:
    Polygonizer() {}
    ~Polygonizer()
    {
        release();
    }

    void Create(float bounds, int resol, int nfunc)
    {
        release();
        _polygon_nim=CreatePolygonizer(bounds, resol, getFunc(nfunc));

        if (_polygon_nim)
        {
            vertexes.resize(getNVertex(_polygon_nim));
            trigs.resize(getNTrigs(_polygon_nim));
            getMesh(_polygon_nim, vertexes.data(), trigs.data());
        }
    }

    void release()
    {
        if (_polygon_nim) freePolygonizer(_polygon_nim);
    }

    void saveCTM(const char*name)
    {
        if (_polygon_nim) writeCTM(_polygon_nim, name);
    }

public:
    vector<Vertex>vertexes;
    vector<Triangle>trigs;

public:

    static vector<string> getNames()
    {
        static vector<string>ImplicitFuncNames=
        {
            "Sphere", "Blob", "NordstarndWeird", "DecoCube", "Cassini", "Orth", "Orth3",
            "Pretzel", "Tooth", "Pilz", "Bretzel", "BarthDecic", "Clebsch0", "Clebsch",
            "Chubs", "Chair", "Roman", "TangleCube", "Goursat", "Sinxyz"
        };
        return ImplicitFuncNames;
    }

    static vec3Func* getFunc(int fn)
    {
        static vector<vec3Func*> ImplicitFunctions=
        {
            Sphere, Blob, NordstarndWeird, DecoCube, Cassini, Orth, Orth3,
            Pretzel, Tooth, Pilz, Bretzel, BarthDecic, Clebsch0, Clebsch,
            Chubs, Chair, Roman, TangleCube, Goursat, Sinxyz
        };
        return ImplicitFunctions[fn % ImplicitFunctions.size()];
    }

private:
    pPolygonizer _polygon_nim=nullptr;
};


#endif // POLYGONIZERWRAP_H_INCLUDED
