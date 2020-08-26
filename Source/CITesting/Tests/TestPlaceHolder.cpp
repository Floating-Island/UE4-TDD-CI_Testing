// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlaceHolder.h"


#include "Misc/AutomationTest.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.


//a test
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FOneShouldBeOneTest, "Game.Unit.TestPlaceholder.OneShouldBeOne", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


bool FOneShouldBeOneTest::RunTest(const FString& Parameters)
{
	//One should be one.
	{
		TestEqual(TEXT("one is one"), 1, 1);
	}

	return true;
}


//another test
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSTwoShouldBeTwoTest, "Game.Unit.TestPlaceholder.TwoShouldBeTwo", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


bool FSTwoShouldBeTwoTest::RunTest(const FString& Parameters)
{
	//two should be two.
	{
		TestEqual(TEXT("two is two"), 2, 2);
	}

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS