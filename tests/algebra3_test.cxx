#include <cppunit/extensions/HelperMacros.h>
#include "microgen_exceptions.hxx"
#include "microgen_types.hxx"
#include "microgen_parsing.hxx"
#include "microgen_algebra3.hxx"

namespace microgen {

class TestAlgebra3: public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestAlgebra3 );
  CPPUNIT_TEST( testVecMatVec3 );
  CPPUNIT_TEST_SUITE_END();
  public:

    /* The setUp method will called before pach test. If you do not know what
     * put in this method you can safely delete it.
     */
    void setUp() {}

    /* The tearDown method will be called after each test. If you do not know
     * what to put in this method you can safely delete it. */
    void tearDown() {}

    void testVecMatVec3();
};
CPPUNIT_TEST_SUITE_REGISTRATION( TestAlgebra3 );

void TestAlgebra3::testVecMatVec3() {
  double m[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  microgen::Vector3 v1(1.0, 2.0, 3.0);
  microgen::Vector3 v2(3.0, 2.0, 1.0);
  microgen::Matrix3 mat(3,3,m);
  double result = VecMatVec3(v1, mat, v2);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(204, result, 1e-5);
}

} /* namespace microgen */
