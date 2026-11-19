#include <cstdio>
#include <cmath>
#include "delta_kinematics.hpp"
using namespace delta;

int main() {
  Params p; Kinematics k(p);
  printf("offset = %.6f %.6f %.6f\n", k.offset()(0), k.offset()(1), k.offset()(2));
  int n = 0, fail_fk = 0, fail_ik = 0; double maxq = 0, maxp = 0, maxrod = 0;
  for (double x = -0.02; x <= 0.0201; x += 0.005)
  for (double y = -0.02; y <= 0.0201; y += 0.005)
  for (double z = -0.14; z <= -0.0499; z += 0.01) {
    Vec3 t = {{x,y,z}}, q, t2;
    if (!k.inverse(t, q)) { fail_ik++; continue; }
    if (!k.forward(q, t2)) { fail_fk++; continue; }
    n++;
    for (int i = 0; i < 3; i++) maxp = fmax(maxp, fabs(t(i)-t2(i)));
    // independent check: rod length between elbow and TCP
    for (int i = 0; i < 3; i++) {
      double al = i==0?0:(i==1?2*M_PI/3:-2*M_PI/3);
      double r = p.r_A - p.r_B, xe = r + p.length_A*cos(q(i)), ze = p.length_A*sin(q(i));
      double ex = cos(al)*xe, ey = sin(al)*xe;
      double dx = t(0)+k.offset()(0)-ex, dy = t(1)+k.offset()(1)-ey, dz = t(2)+k.offset()(2)-ze;
      maxrod = fmax(maxrod, fabs(sqrt(dx*dx+dy*dy+dz*dz) - p.length_B));
    }
  }
  printf("points ok=%d ik_fail=%d fk_fail=%d\n", n, fail_ik, fail_fk);
  printf("max |IK->FK pos err| = %.3e m, max |rod length err| = %.3e m\n", maxp, maxrod);
  return (maxp < 1e-9 && maxrod < 1e-9 && n > 0) ? 0 : 1;
}
