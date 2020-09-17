// Fill out your copyright notice in the Description page of Project Settings.


#include "AcceleratingPawnTest.h"

#include "AcceleratingPawn.h"//the class we are testing.

#include "Misc/AutomationTest.h"




#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.Unit.ClassToTest.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnShouldntBeNullWhenInstantiatedTest, "Game.Unit.AcceleratingPawnTests.ShouldntBeNullWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnShouldntBeNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	{
		AAcceleratingPawn* testPawn = NewObject<AAcceleratingPawn>();
		
		TestNotNull(TEXT("The pawn shouldn't be null after instantiating it."), testPawn);
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnShouldHaveAStaticMeshTest, "Game.Unit.AcceleratingPawnTests.ShouldHaveAStaticMesh", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnShouldHaveAStaticMeshTest::RunTest(const FString& Parameters)
{
	{
		AAcceleratingPawn* testPawn = NewObject<AAcceleratingPawn>();
		
		TestTrue(TEXT("The Jet static mesh shouldn't be null if it has one."), testPawn->hasAStaticMesh());
	}

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS
