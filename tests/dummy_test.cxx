#include <cppunit/extensions/HelperMacros.h>
#include "microgen_exceptions.hxx"
#include "microgen_types.hxx"

namespace microgen {

class TestDummy: public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestDummy );
  CPPUNIT_TEST( testDummy );
  CPPUNIT_TEST_SUITE_END();
  public:

    /* The setUp method will called before pach test. If you do not know what
     * put in this method you can safely delete it.
     */
    void setUp() {}

    /* The tearDown method will be called after each test. If you do not know
     * what to put in this method you can safely delete it. */
    void tearDown() {}

    void testDummy();
};
CPPUNIT_TEST_SUITE_REGISTRATION( TestDummy );

void TestDummy::testDummy() {
  CPPUNIT_ASSERT( 1 == 1);
}

} /* namespace microgen */
