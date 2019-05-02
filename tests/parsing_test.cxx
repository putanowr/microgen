#include <cppunit/extensions/HelperMacros.h>
#include "microgen_exceptions.hxx"
#include "microgen_types.hxx"
#include "microgen_parsing.hxx"

namespace microgen {

class TestParsing: public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( TestParsing );
  CPPUNIT_TEST( testParseCubeSize );
  CPPUNIT_TEST_SUITE_END();
  public:

    /* The setUp method will called before pach test. If you do not know what
     * put in this method you can safely delete it.
     */
    void setUp() {}

    /* The tearDown method will be called after each test. If you do not know
     * what to put in this method you can safely delete it. */
    void tearDown() {}

    void testParseCubeSize();
};
CPPUNIT_TEST_SUITE_REGISTRATION( TestParsing );

void TestParsing::testParseCubeSize() {
  std::string sizeString1("10x20x30");
  std::string sizeString2("1,2,3");
  std::string sizeString3("100 200 300");
  vigra::Shape3 shape;
  microgen::parseCubeSize(sizeString1, shape); 
  CPPUNIT_ASSERT( shape[0] == 10);
  CPPUNIT_ASSERT( shape[1] == 20);
  CPPUNIT_ASSERT( shape[2] == 30);

  microgen::parseCubeSize(sizeString2, shape); 
  CPPUNIT_ASSERT( shape[0] == 1);
  CPPUNIT_ASSERT( shape[1] == 2);
  CPPUNIT_ASSERT( shape[2] == 3);

  microgen::parseCubeSize(sizeString3, shape); 
  CPPUNIT_ASSERT( shape[0] == 100);
  CPPUNIT_ASSERT( shape[1] == 200);
  CPPUNIT_ASSERT( shape[2] == 300);
}

} /* namespace microgen */
