#include "Simple.h"
#include <iostream>

vectorField2 GaussSeidel(scalarField A, vectorField2 b){
    if (A.nx == b.size){
        float diff;
        vec2 sum = vec2(0,0);

        vectorField2 x = vectorField2(b.nx, b.ny);

        // do {
        for (int iter = 0; iter < 30; iter++) {
            diff = 0;

            for (int i = 0; i < A.ny; i++){
                sum = vec2(0,0);

                for (int j = 0; j < A.nx; j++){
                    if (i != j){
                        sum = sum + x(j) * A(i,A.ny-1-j);
                    }
                }

                diff += abs(((b(i) - sum) / A(i,A.ny-1-i) - x(i)).size());

                x(i) = (b(i) - sum) / A(i,A.ny-1-i);
            }

        // } while (diff > 1e-5);
        }
        return x;
    }
    else{
        std::cerr << "fuck you" << std::endl;
    }
}

scalarField GaussSeidel(scalarField A, scalarField b){
    if (A.nx == b.size){
        float diff;
        double sum = 0;

        scalarField x = scalarField(b.nx, b.ny);

        // do {
        for (int iter = 0; iter < 80; iter++) {
            diff = 0;

            for (int i = 0; i < A.ny; i++){
                sum = 0;

                for (int j = 0; j < A.nx; j++){
                    if (i != j){
                        sum = sum + x(j) * A(i,A.ny-1-j);
                    }
                }

                diff += abs((b(i) - sum) / A(i,A.ny-1-i) - x(i));

                x(i) = (b(i) - sum) / A(i,A.ny-1-i);
            }

        // } while (diff > 1e-5);
        }
        return x;
    }
    else{
        std::cerr << "fuck you" << std::endl;
    }
}

scalarField AssembleUCoefficientMatrix(mesh& m, double mu){
    scalarField A = scalarField(m.size, m.size);

    double k = mu / pow(m.h, 2);

    for (int i = 0; i < m.size; i++){
        for (int side = 0; side < m.sides.size(); side++){

            int j = (m.*m.sides[side])(i);

            if (j != -1){
                A(i,A.ny-1-j) = -k;
                A(i,A.ny-1-i) += k;
            }
            else{
                A(i,A.ny-1-i) += 2 * k;
            }
        }
    }
    std::cout<<"A:"<<std::endl;
    // A.printGrid(1);
    return A;
}

scalarField AssemblePCoefficientMatrix(mesh& m, float alpha){
    scalarField B = scalarField(m.size, m.size);

    m.uDiag = m.uDiag / alpha;

    std::cout<<"u diag:"<<std::endl;
    // m.uDiag.printGrid();

    std::cout<<(pow(m.h,2))<<std::endl;

    double k;

    for (int i = 0; i < m.size; i++){
        for (int side = 0; side < m.sides.size(); side++){

            int j = (m.*m.sides[side])(i);

            if (j != -1){
                // if (m.uDiag(i) == 0 || std::isnan(m.uDiag(i))) {
                //     std::cout << "BAD UDIAG " << i << " " << m.uDiag(i) << std::endl;
                // }
                k = (1.0 / m.uDiag(i) + 1.0 / m.uDiag(j)) / (2*pow(m.h,2));

                B(i,B.ny-1-j) = -k;
                B(i,B.ny-1-i) += k;
            }
            else{
                // boundary
            }
        }
    }

    return B;
}

vectorField2 AssembleURightSide(mesh& m, double mu){
    vectorField2 b = vectorField2(m.nx, m.ny);
    std::cout<<"computing u right side"<<m.nx*m.ny<<std::endl;
    double k = mu / pow(m.h,2);

    for (int i = 0; i < m.size; i++){
        for (int side = 0; side < m.sides.size(); side++){

            int j = (m.*m.sides[side])(i);

            if (j == -1){
                b(i) = b(i) - (*m.BCs[side] * 2 * k);
            }
        }
    }
    std::cout<<"u right side magnitude:"<< b(8).print() <<std::endl;
    // b.magnitude().printGrid();
    return b;
}

scalarField ComputeDivU(mesh& m){
    scalarField b = scalarField(m.nx, m.ny);

    std::array<vec2,4> faceUs;

    for (int i = 0; i < m.size; i++){
        // std::cout<<m.u(i).size()<<std::endl;

        for (int side = 0; side < m.sides.size(); side++){

            int j = (m.*m.sides[side])(i);

            if (j != -1){
                faceUs[side] = (m.u(i) + m.u(j)) / 2;
            }
            else{
                faceUs[side] = (m.u(i) + *m.BCs[side]) / 2;
            }
        }

        b(i) = -(
            (faceUs[1](0) - faceUs[3](0)) / m.h +
            (faceUs[0](1) - faceUs[2](1)) / m.h
        );
    }
    std::cout<<"div u:"<<std::endl;
    // b.printGrid();
    return b;
}

vectorField2 ComputePressureGradient(mesh& m, bool corr){
    vectorField2 gradp = vectorField2(m.nx, m.ny);

    std::array<double,4> neighbourPs;

    scalarField* p;

    if (!corr){
        std::cout<<"computing p gradient"<<std::endl;
        p = &m.p;
    }
    else{
        std::cout<<"computing p' gradient"<<std::endl;
        p = &m.pCorr;

        // p->printGrid();
    }



    for (int i = 0; i < m.size; i++){

        for (int side = 0; side < m.sides.size(); side++){

            int j = (m.*m.sides[side])(i);

            if (j != -1){
                neighbourPs[side] = (*p)(j);
            }
            else{
                neighbourPs[side] = (*p)(i);
            }
        }
        std::cout<<neighbourPs[1]<<"   "<<neighbourPs[3]<<std::endl;
        gradp(i) = vec2(
            (neighbourPs[1] - neighbourPs[3]) / (m.h * 2),
            (neighbourPs[0] - neighbourPs[2]) / (m.h * 2)
        );
        gradp(i).print(true);
    }
    std::cout<<"xs:"<<std::endl;
    // gradp.xs().printGrid();
    std::cout<<"ys:"<<std::endl;
    // gradp.ys().printGrid();
    return gradp;
}

void SolveVelocityField(mesh& m, double mu){
    std::cout<<"solving velocity field"<<std::endl;
    scalarField A = AssembleUCoefficientMatrix(m, mu);
    std::cout<<"U coef matrix ready"<<std::endl;

    vectorField2 b =
        vectorField2(m.nx, m.ny)
        - ComputePressureGradient(m, false)
        + AssembleURightSide(m, mu);
    std::cout<<"right side ready"<<std::endl;
    m.u = GaussSeidel(A, b);
    std::cout<<"u* solved"<<std::endl;
    m.uDiag = A.diag(vec2(m.nx,m.ny));
    A.chDiag(0.7);
    std::cout<<"diagonal ok"<<std::endl;
}

void SolvePressureField(mesh& m, float alpha){
    std::cout<<"solving pressure field"<<std::endl;
    scalarField B = AssemblePCoefficientMatrix(m, alpha);
    std::cout<<"P coef matrix ready"<<std::endl;

    
    // B(0,0) = 1;
    B(0,B.ny-1)*=2;
    // B.printGrid();
    std::cout<<"B:"<<std::endl;
    scalarField b = ComputeDivU(m);
    std::cout<<"right side ready"<<std::endl;

    // b(0) = 0;

    m.pCorr = GaussSeidel(B, b);
    std::cout<<"p' solved"<<std::endl;

    m.p = m.p + m.pCorr * 0.1;
    std::cout<<"p applied"<<std::endl;
}

void SIMPLE(mesh* m){

    std::cout<<"start simple"<<std::endl;

    double mu = 0.1;

    for (int i = 0; i < 10; i++){

        std::cout<<"iteration "<<i<<std::endl;

        SolveVelocityField(*m, mu);

        SolvePressureField(*m, 0.7);


        m->u = m->u -
            (m->uDiag.inverseVals()
            * ComputePressureGradient(*m, true));

        std::cout<<"finished iteration "<<m->u.magnitude()(2)<<std::endl;
    }
}

int mesh::east(int i){
    if (i % nx == nx - 1){
        return -1;
    }

    return i + 1;
}

int mesh::west(int i){
    if (i % nx == 0){
        return -1;
    }

    return i - 1;
}

int mesh::north(int i){
    if (i >= nx * (ny - 1)){
        return -1;
    }

    return i + nx;
}

int mesh::south(int i){
    if (i < nx){
        return -1;
    }

    return i - nx;
}
