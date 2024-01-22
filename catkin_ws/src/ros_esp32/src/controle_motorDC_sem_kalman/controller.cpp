#include "controller.h"

Controller::Controller(Matrix<1, systemOrder> gains, Matrix<1> K_i){
   this->K = gains;
   this->K_i = K_i;
};

Controller::~Controller(){};

float Controller::controlLaw(Matrix<systemOrder,1> currentState, const Matrix<1> &y){
    this->v_n = this->v_n + this->r - currentState(0);
//    Serial.println(v_n(0));

    this->u = (this->K * currentState + this->K_i * this->v_n)(0);
//    Serial.println(this->r(0));

  return (this->u);    
}

void saturate(float* input, float lowerLimit, float upperLimit){
  if(*input < lowerLimit) *input = lowerLimit;
  if(*input > upperLimit) *input = upperLimit;
}
