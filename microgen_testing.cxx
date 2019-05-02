/*
 * Copyright (c) 2014-2019 Roman Putanowicz 
 * 
 * This file is distributed on "BSD 3-Clause License" as approved by 
 * the OSI Board. For licensing terms see LICENSE file distributed 
 * with this file.
 */
#include "microgen_testing.hxx"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/TestResult.h>
#include <cppunit/TextTestRunner.h>
#include <stdlib.h> // for EXIT_SUCCESS
#include <iostream>
#include "femdk_except.hxx"

namespace microgen {

struct MyTestProgressListener : public CppUnit::TextTestProgressListener {
  int failCount;
  void  startTest(CppUnit::Test *test) {}
  void  endTest(CppUnit::Test *test) {}
  void 	startSuite (CppUnit::Test *test) {
     failCount = 0;
     std::cout << "\n" << test->getName() << " ";
  }
  void 	endSuite (CppUnit::Test *test) {
     int n = test->countTestCases();
     std::string testName = test->getName();
     if (testName == "All Tests") {
       std::cout << "\n"; 
     } else {
       int k = testName.length();
       std::string dots(60-k, '.');
       std::cout << " " << dots << " " << n-failCount << "/" << n;
     } 
     if (failCount > 0) {
       std::cout << "[0m";
     }
  }
  void addFailure(const CppUnit::TestFailure &failure) {
     failCount++;
     std::cout << "[01;31m";
  }
};
/** The function where the main work is done after configuration
 * and command line parsing.
 */
int selftesting_main(void) {
  std::cout << "Entering program self testing mode\n";

  CppUnit::TextTestRunner runner;
  CppUnit::TestFactoryRegistry &registry = 
                               CppUnit::TestFactoryRegistry::getRegistry();
  runner.addTest( registry.makeTest() );
  MyTestProgressListener progress;
  runner.eventManager().addListener( &progress );
  bool wasSuccessful = runner.run( "", false, true, false );
  if (wasSuccessful) {
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  } 
}

} /* namespace microgen */
