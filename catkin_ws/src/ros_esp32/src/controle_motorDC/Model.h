using namespace BLA;

template <int X, int U, int Y = X>
struct Model
{
    const static int states = X;
    const static int inputs = U;
    const static int outputs = Y;

    Matrix<X, X> A;
    Matrix<X, U> B;
    Matrix<Y, X> C;
    Matrix<Y, U> D;
};

struct MotorSpeedModel : public Model<2, 1, 1>
{
    MotorSpeedModel(float a1, float a2, float b1, float b2)
    {
        // Define the system matrix
        A = {a1, 1, a2, 0};

        // Define the input matrix
        B = {b1, b2};

        // Define the output matrix
        C = {1, 0};

        // Define the direct transmission matrix
        D = Zeros<1, 1>();
    }
};
