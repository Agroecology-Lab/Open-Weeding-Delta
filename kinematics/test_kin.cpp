#include <cstdio>
#include <cmath>
#include "delta_kinematics.hpp"
using namespace delta;

// Reference: zaphod-bot kinematics.c delta_angle_plane_calc (metres, degrees).
static const double F = 0.050, E = 0.034, RF = 0.180, RE = 0.340;
static bool zaphod_plane(double x0, double y0, double z0, double* theta) {
  double s13 = std::sqrt(1.0/3.0);
  double y1 = -0.5*s13*F;
  y0 -= 0.5*s13*E;
  double a = (x0*x0 + y0*y0 + z0*z0 + RF*RF - RE*RE - y1*y1) / (2*z0);
  double b = (y1 - y0) / z0;
  double d = -(a + b*y1)*(a + b*y1) + RF*(b*b*RF + RF);
  if (d < 0) return false;
  double yj = (y1 - a*b - std::sqrt(d)) / (b*b + 1);
  double zj = a + b*yj;
  *theta = 180.0*std::atan(-zj/(y1 - yj))/M_PI + ((yj > y1) ? 180.0 : 0.0);
  return true;
}
static bool zaphod_ik(double x, double y, double z, double th[3]) {
  const double c120 = -0.5, s120 = std::sqrt(3.0)/2;
  return zaphod_plane(x, y, z, &th[0])
      && zaphod_plane(x*c120 + y*s120, y*c120 - x*s120, z, &th[1])
      && zaphod_plane(x*c120 - y*s120, y*c120 + x*s120, z, &th[2]);
}

int main() {
  Params p; Vec3 zero = {{0,0,0}};
  Kinematics k(p, zero);               // raw frame, no TCP offset
  Kinematics kd(p);                    // default: origin = pose at q=0
  printf("default offset z = %.6f m\n", kd.offset()(2));

  int n = 0, ikfail = 0, fkfail = 0, outlim = 0, cmp = 0;
  double maxrt = 0, maxrod = 0, maxcmp = 0;
  for (double x = -0.10; x <= 0.1001; x += 0.025)
  for (double y = -0.10; y <= 0.1001; y += 0.025)
  for (double z = -0.40; z <= -0.1799; z += 0.02) {
    Vec3 t = {{x,y,z}}, q, t2;
    if (!k.inverse(t, q)) { ikfail++; continue; }
    if (!k.inLimits(q)) outlim++;
    if (!k.forward(q, t2)) { fkfail++; continue; }
    n++;
    for (int i = 0; i < 3; i++) maxrt = fmax(maxrt, fabs(t(i)-t2(i)));
    // rod length check
    double r = p.r_A - p.r_B;
    for (int i = 0; i < 3; i++) {
      double al = i==0?0:(i==1?2*M_PI/3:-2*M_PI/3);
      double xe = r + p.length_A*cos(q(i)), ze = p.length_A*sin(q(i));
      double dx = x-cos(al)*xe, dy = y-sin(al)*xe, dz = z-ze;
      maxrod = fmax(maxrod, fabs(sqrt(dx*dx+dy*dy+dz*dz) - p.length_B));
    }
    // compare with zaphod IK. Frames: mine = zaphod rotated +90 deg about z,
    // so zaphod point = (y, -x, z). Joint: q = -theta. Arm order is the same.
    double th[3];
    if (zaphod_ik(y, -x, z, th)) {
      cmp++;
      for (int i = 0; i < 3; i++) maxcmp = fmax(maxcmp, fabs(q(i) - (-th[i]*M_PI/180.0)));
    }
  }
  printf("points ok=%d ik_fail=%d fk_fail=%d outside_joint_limits=%d\n", n, ikfail, fkfail, outlim);
  printf("IK->FK max err = %.3e m, rod length max err = %.3e m\n", maxrt, maxrod);
  printf("vs zaphod IK: %d points, max joint diff = %.3e rad\n", cmp, maxcmp);
  return (maxrt < 1e-9 && maxrod < 1e-9 && cmp > 0 && maxcmp < 1e-9) ? 0 : 1;
}
