#ifndef MICROGEN_ALGEBRA3_HXX
#define MICROGEN_ALGEBRA3_HXX

/** @file This file provides matrix and vector algebra types and functions
 * for R^3 space
 */

#include <vigra/matrix.hxx>
#include <vigra/linear_algebra.hxx>
#include <vigra/tinyvector.hxx>

namespace microgen {

typedef vigra::TinyVector<double, 3> Vector3;
typedef vigra::Matrix<double> Matrix3;

double VecMatVec3(const Vector3& v1, const Matrix3& mat, const Vector3& vec2);


} /* namespace microgen */

#endif /* ifndef MICROGEN_ALGEBRA3_HXX */
