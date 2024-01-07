#include "controller.h"

Controller::Controller(Matrix<1, systemOrder> gains){
   this->K = gains;
};

Controller::~Controller(){};

void Controller::controlLaw(Matrix<systemOrder,1> currentState, const Matrix<1> &y){

    v_n = v_n + r - (currentState)(0);

    this->u = (this->K * currentState)(0);

    this->u += this->Ki * v_n;
}

void saturate(float* input, float lowerLimit, float upperLimit){
  if(*input < lowerLimit) *input = lowerLimit;
  if(*input > upperLimit) *input = upperLimit;
}
