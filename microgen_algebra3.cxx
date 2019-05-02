#include "microgen_algebra3.hxx"

namespace microgen {

double VecMatVec3(const Vector3& v1, const Matrix3& mat, const Vector3& vec2) {
  Vector3 t = mat*vec2;
  return vigra::dot(v1, t);
}

} /* namespace microgen */
