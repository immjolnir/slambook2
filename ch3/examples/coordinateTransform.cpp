// $ g++ -std=c++14 -I/usr/include/eigen3 coordinateTransform.cpp 
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main(int argc, char** argv) {
  Quaterniond q1(0.35, 0.2, 0.3, 0.1), q2(-0.5, 0.4, -0.1, 0.2);
  q1.normalize();
  q2.normalize();
  Vector3d t1(0.3, 0.1, 0.1), t2(-0.1, 0.5, 0.3);
  Vector3d p1(0.5, 0, 0.2);

  Isometry3d T1w(q1), T2w(q2);
  T1w.pretranslate(t1);
  T2w.pretranslate(t2);

  Vector3d p2 = T2w * T1w.inverse() * p1;
  cout << endl << p2.transpose() << endl;

  // ---
  auto w1 = T1w.inverse() * p1;
  cout << "word1 cor=" << w1 << endl;

  auto w2 = T2w.inverse() * p2;
  cout << "word2 cor=" << w2 << endl;
  // https://stackoverflow.com/questions/15051367/how-to-compare-vectors-approximately-in-eigen
  // There is also isApprox function which was not working for me. I am just using ( expect - res).norm() < some small number.
  cout << w1.x() << ","<< w2.x() << " and they are equal?"<< (w1.x() == w2.x()) <<endl;
  auto diff = (w2 - w1).norm();
  cout << std::setprecision(10) << std::fixed<< diff << endl;
  cout << "std::setprecision(10): " << std::setprecision(10) << std::fixed<< diff << '\n'
       << "max precision:        " << std::setprecision(std::numeric_limits<long double>::digits10 + 1) << diff << endl;
  return 0;
}
