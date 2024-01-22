#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <BasicLinearAlgebra.h>
using namespace BLA;

void saturate(float* input, float lowerLimit, float upperLimit);

class Controller{

  private:
  
  static const int systemOrder = 2;
  Matrix<1, systemOrder> K;
  Matrix<1> K_i;

  public:
  
  Controller(Matrix<1, systemOrder> gains, Matrix<1> K_i);
  ~Controller();
  float controlLaw(Matrix<systemOrder, 1> currentState, const Matrix<1> &y);
  
  Matrix<1> v_n = {0};
  Matrix<1> r = {0};
  float u = 0; 
};
#endif
