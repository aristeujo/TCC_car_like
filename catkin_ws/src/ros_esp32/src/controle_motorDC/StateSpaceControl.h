//// #ifndef STATE_SPACE_CONTROL_H
//// #define STATE_SPACE_CONTROL_H
//
//#include "Arduino.h"
//#include "BasicLinearAlgebra.h"
//#include "Model.h"
//
//using namespace BLA;
//
//template<bool>
//struct enable_if {
//};
//
//template<>
//struct enable_if<true> {
//  typedef int type;
//};
//
//template <class X, class M, class N, class O, class Q>
//X map_Generic(X x, M in_min, N in_max, O out_min, Q out_max){
//  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//}
//
//template<int X, int U, int Y = X, bool FullStateFeedback = X == Y>
//class StateSpaceController {
//  Matrix<X, X> ALC;
//  Matrix<U, Y> N_bar;
//
//public:
//  // System model
//  const Model<X, U, Y> &model;
//
//  // Control variables
//  Matrix<X> x_hat;  // state estimate
//  Matrix<X> x_n;
//  Matrix<1> v_n;
//  Matrix<U> u;      // control input
//  Matrix<Y> r;      // reference input (assumed to be of the same dimension as the observation y)
//  Matrix<U> w_hat;  // estimate of a disturbance / error in the system model (used by the integral controller)
//
//  // Control Gains
//  Matrix<U, X> K;  // regulator gain
//  Matrix<U> Ki;  // regulator gain
//  Matrix<X, Y> L;  // estimator gain
//  Matrix<U, Y> I;  // integral control gain
//
//  StateSpaceController(const Model<X, U, Y> &_model)
//    : model(_model),
//      x_hat(Zeros<X>()),
//      x_n(Zeros<X>()),
//      v_n(Zeros<1>()),
//      u(Zeros<U>()),
//      r(Zeros<Y>()),
//      w_hat(Zeros<U>()),
//      L(Zeros<X, Y>()),
//      I(Zeros<U, Y>()) {
//    static_assert(X == Y || !FullStateFeedback,
//                  "The number of inputs must match the number of outputs if using full state feedback");
//  }
//
//  void initialise() {
//    // For reference tracking we'll need to precalculate Nbar which maps the reference input to a control input
//    // offset
//    Matrix<X + Y, X + U> sys = (model.A || model.B) && (model.C || model.D);
//
//    // Find an inverse for the aggregated matrix
//    Matrix<X + U, X + Y> sysInv;
//
//    // Case 1: more outputs than inputs - find the left inverse
//    if (model.inputs < model.outputs) {
//      sysInv = Inverse(~sys * sys) * ~sys;
//    }
//    // Case 2: more than, or the same number of outputs as inputs - find the right inverse
//    else {
//      sysInv = ~sys * Inverse(sys * ~sys);
//    }
//
//    // Split it up and multiply it with K to find NBar
//    N_bar = K * sysInv.template Submatrix<X, Y>(0, X) + sysInv.template Submatrix<U, Y>(X, X);
//
//    
//  }
//
////
////  template<bool FSF>
////  Matrix<X> state_xn(float dt, typename enable_if<!FSF>::type * = nullptr) {
////    return x_n + (model.A * x_n + model.B * u);
////  }
////
////  template<bool FSF>
////  Matrix<X> state_vn(float dt, typename enable_if<!FSF>::type * = nullptr) {
////    return (v_n + r - model.C * x_n);
////  }
////
////  template<bool FSF>
////  Matrix<X> estimate_state(const Matrix<Y> &y, float dt, typename enable_if<FSF>::type * = nullptr) {
////    return y;
////  }
//
//  void update(const Matrix<Y> &y, float dt) {
//    // First, update the state estimate
//    x_n = (model.A * x_n + model.B * u);
//    v_n = (v_n + r - y);
//    // v_n = (v_n + r - model.C * x_n);
//
//    // Calculate the control input 
//    u = K * x_n;
//
//    u += Ki * v_n;
//  }
//};
