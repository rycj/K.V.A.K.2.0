#include <array>
#include <vector>
#include <string>
struct vertice{
    vertice(double x_,double y_, int id_);
    double x;
    double y;
    int id;
};

struct face{
    face(CartMesh2d* mesh_, bool B,double size_,int id_,std::string BType=NULL);
    CartMesh2d* mesh;
    std::array<cell&,2> neighbours;
    double size;
    bool boundary;
    std::string boundaryType;
    int id;
};

struct cell{
    cell(CartMesh2d* mesh_, double area_, std::array<int,4> faceIDs,int id_);
    CartMesh2d* mesh;
    double area;
    std::array<face,4> faces;
    std::array<double,2> u;
    double p;
    int id;
};



struct CartMesh2d{
    CartMesh2d(int x_, int y_, int nx_, int ny_);
    // int x;
    // int y;
    // int nx;
    // int ny;
    std::vector<vertice> vertices;
    std::vector<face> faces;
    std::vector<cell> cells;
};
