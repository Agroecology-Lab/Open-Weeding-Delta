// Delta kinematics, ported from eeduro/delta control/Kinematic.cpp.
// No EEROS, no heap, no exceptions. Units: metres, radians.
// q = 0 -> upper arm horizontal; z negative = below base.
#pragma once
#include <cmath>

namespace delta {

struct Vec3 { double v[3]; double& operator()(int i){return v[i];} double operator()(int i) const {return v[i];} };

// Defaults: Scottapotamas/zaphod-bot firmware/src/drivers/kinematics.c
//   rf = 180 mm (bicep), re = 340 mm (rod), f = 50 mm, e = 34 mm.
//   Zaphod's f, e are triangle side lengths (Chong IK): radial offset = f/(2*sqrt3).
//   Effective r = r_A - r_B = (f - e)*tan30/2 = 4.619 mm, same as zaphod's `t`.
// Joint limits: zaphod theta in [-45, +65] deg, theta positive = arm down.
//   This code uses q = -theta (q negative = arm down) -> q in [-65, +45] deg.
struct Params {
  double length_A = 0.180;                 // bicep
  double length_B = 0.340;                 // rod
  double r_A      = 0.050 / 3.4641016151377544;  // 14.434 mm
  double r_B      = 0.034 / 3.4641016151377544;  //  9.815 mm
  double q_min    = -65.0 * M_PI / 180.0;  // [rad]
  double q_max    =  45.0 * M_PI / 180.0;
};

class Kinematics {
 public:
  explicit Kinematics(const Params& p) : p_(p), r_(p.r_A - p.r_B) {
    offset_ = {{0,0,0}};
    Vec3 q = {{0,0,0}}, t;
    if (forward(q, t)) offset_ = t;   // same as eeduro: TCP origin = pose at q=0
  }
  Kinematics(const Params& p, const Vec3& offset) : p_(p), r_(p.r_A - p.r_B), offset_(offset) {}

  const Vec3& offset() const { return offset_; }
  bool inLimits(const Vec3& q) const {
    for (int i = 0; i < 3; i++) if (q(i) < p_.q_min || q(i) > p_.q_max) return false;
    return true;
  }

  bool forward(const Vec3& q, Vec3& tcp) const {
    Vec3 pc[3];
    for (int i = 0; i < 3; i++) {
      double c = std::cos(alpha(i)), s = std::sin(alpha(i));
      double x = r_ + p_.length_A * std::cos(q(i)), z = p_.length_A * std::sin(q(i));
      pc[i] = {{c * x, s * x, z}};
    }
    double w1 = dot(pc[0], pc[0]), w2 = dot(pc[1], pc[1]), w3 = dot(pc[2], pc[2]);
    double A = pc[1](0)-pc[0](0), B = pc[1](1)-pc[0](1), C = -(pc[1](2)-pc[0](2)), G = (w2-w1)/2;
    double D = pc[2](0)-pc[0](0), E = pc[2](1)-pc[0](1), F = -(pc[2](2)-pc[0](2)), H = (w3-w1)/2;
    double dnm = A*E - B*D;
    if (std::fabs(dnm) < 1e-12) return false;
    double a1 = (C*E - F*B)/dnm, b1 = (G*E - H*B)/dnm;
    double a2 = (A*F - C*D)/dnm, b2 = (A*H - G*D)/dnm;
    double x1 = pc[0](0), y1 = pc[0](1), z1 = pc[0](2);
    double a = a1*a1 + a2*a2 + 1;
    double b = 2*(a1*(b1-x1) + a2*(b2-y1) - z1);
    double c = -p_.length_B*p_.length_B + w1 + b1*(b1-2*x1) + b2*(b2-2*y1);
    double d = b*b - 4*a*c;
    if (d < 0) return false;
    double z = (-b - std::sqrt(d)) / (2*a);   // lower solution
    tcp = {{a1*z + b1 - offset_(0), a2*z + b2 - offset_(1), z - offset_(2)}};
    return true;
  }

  bool inverse(const Vec3& tcp, Vec3& q) const {
    Vec3 t = {{tcp(0)+offset_(0), tcp(1)+offset_(1), tcp(2)+offset_(2)}};
    // eeduro: arm1 uses rotz1, arm2 uses inverse(rotz2)=rotz3, arm3 uses rotz2
    Vec3 q_out;
    for (int i = 0; i < 3; i++) {
      double ang = -alpha(i);                 // rotate TCP into arm i's XZ plane
      double c = std::cos(ang), s = std::sin(ang);
      double x0 = c*t(0) - s*t(1), y0 = s*t(0) + c*t(1), z0 = t(2);
      if (z0 == 0) return false;
      double LA2 = p_.length_A*p_.length_A;
      double a = (x0*x0 + y0*y0 + z0*z0 + LA2 - p_.length_B*p_.length_B - r_*r_) / (2*z0);
      double b = (r_ - x0) / z0;
      double A = b*b + 1, B = 2*(a*b - r_), C = r_*r_ + a*a - LA2;
      double disc = B*B - 4*A*C;
      if (disc < 0) return false;
      double xj = (-B + std::sqrt(disc)) / (2*A);   // outer point
      double zj = a + b*xj;
      q_out(i) = std::atan2(zj, xj - r_);
    }
    q = q_out;
    return true;
  }

 private:
  static double dot(const Vec3& a, const Vec3& b){ return a(0)*b(0)+a(1)*b(1)+a(2)*b(2); }
  static double alpha(int i){ return i == 0 ? 0.0 : (i == 1 ? 2.0*M_PI/3.0 : -2.0*M_PI/3.0); }
  Params p_; double r_; Vec3 offset_;
};

}  // namespace delta
