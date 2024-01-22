
static const int systemOrder = 2;

struct ss{
  Matrix<systemOrder,systemOrder> A;
  Matrix<systemOrder,1> B;
  Matrix<1,systemOrder> C;
  Matrix<1,1> D;
};


ss sysX = {
  {
    0.9558,   1,
    -0.2512,   0
  },

  {
   0.4016,
   -0.207
  },
  
  {1, 0},  

  {0}
};
