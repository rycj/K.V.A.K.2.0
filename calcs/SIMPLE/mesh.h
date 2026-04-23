#include <array>
#include <vector>
struct vertice{
    vertice(double x_,double y_, int id_);
    double x;
    double y;
    int id;
};

struct face{
    std::array<cell&,2> neighbours;
    double size;
};

struct cell{
    double area;
    std::array<face,4> faces;
    std::array<double,2> u;
    double p;
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
