// Fill out your copyright notice in the Description page of Project Settings.


#include "AcceleratingPawnTest.h"

#include "AcceleratingPawn.h"//the class we are testing.
#include "Mocks/AcceleratingPawnMOCK.h"//class mock to implement methods that aren't related with the class but with the tests.



#include "Misc/AutomationTest.h"
//to be able to simulate:
#include "Tests/AutomationEditorCommon.h"
#include "Editor.h"
#include "Kismet/GameplayStatics.h"
//to be able to process inputs:
#include "MyCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/GameModeBase.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.Unit.ClassToTest.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnShouldntBeNullWhenInstantiatedTest,
                                 "Game.Unit.AcceleratingPawnTests.ShouldntBeNullWhenInstantiated",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnShouldntBeNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	{
		AAcceleratingPawn* testPawn = NewObject<AAcceleratingPawn>();

		TestNotNull(TEXT("The pawn shouldn't be null after instantiating it."), testPawn);
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnShouldHaveAStaticMeshTest,
                                 "Game.Unit.AcceleratingPawnTests.ShouldHaveAStaticMesh",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnShouldHaveAStaticMeshTest::RunTest(const FString& Parameters)
{
	{
		AAcceleratingPawn* testPawn = NewObject<AAcceleratingPawn>();

		TestTrue(TEXT("The pawn static mesh shouldn't be null if it has one."), testPawn->hasAStaticMesh());
	}

	return true;
}


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnMeshShouldBeTheRootComponentTest,
                                 "Game.Unit.AcceleratingPawnTests.MeshShouldBeTheRootComponent",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnMeshShouldBeTheRootComponentTest::RunTest(const FString& Parameters)
{
	{
		AAcceleratingPawnMOCK* testPawnMock = NewObject<AAcceleratingPawnMOCK>();

		TestTrue(TEXT("The pawn static mesh should be the root component."), testPawnMock->isMeshTheRootComponent());
	}

	return true;
}


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnShouldHaveGravityEnabledTest,
                                 "Game.Unit.AcceleratingPawnTests.ShouldHaveGravityEnabled",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnShouldHaveGravityEnabledTest::RunTest(const FString& Parameters)
{
	{
		AAcceleratingPawnMOCK* testPawn = NewObject<AAcceleratingPawnMOCK>();

		TestTrue(TEXT("The pawn should have gravity enabled."), testPawn->hasGravityEnabled());
	}

	return true;
}


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnShouldntAffectNavigationVolumeTest,
                                 "Game.Unit.AcceleratingPawnTests.ShouldntAffectNavigationVolume",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnShouldntAffectNavigationVolumeTest::RunTest(const FString& Parameters)
{
	{
		AAcceleratingPawnMOCK* testPawn = NewObject<AAcceleratingPawnMOCK>();

		TestFalse(TEXT("The pawn shouldn't affect the navigation volume."), testPawn->isAffectingNavigation());
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnShouldBeMovableTest,
                                 "Game.Unit.AcceleratingPawnTests.ShouldBeMovable",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnShouldBeMovableTest::RunTest(const FString& Parameters)
{
	{
		AAcceleratingPawn* testPawn = NewObject<AAcceleratingPawn>();

		TestTrue(TEXT("The pawn's root component should be movable."), testPawn->IsRootComponentMovable());
	}

	return true;
}


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnShouldHaveAStaticMeshAssignedTest,
                                 "Game.Unit.AcceleratingPawnTests.ShouldHaveAStaticMeshAssigned",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnShouldHaveAStaticMeshAssignedTest::RunTest(const FString& Parameters)
{
	{
		AAcceleratingPawnMOCK* testPawn = NewObject<AAcceleratingPawnMOCK>();

		TestTrue(TEXT("The pawn should have default static mesh assigned."), testPawn->hasAStaticMeshAssigned());
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnDefaultAccelerationIsGreaterThanZeroTest,
                                 "Game.Unit.AcceleratingPawnTests.DefaultAccelerationIsGreaterThanZero",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnDefaultAccelerationIsGreaterThanZeroTest::RunTest(const FString& Parameters)
{
	AAcceleratingPawn* testPawn = NewObject<AAcceleratingPawn>(AAcceleratingPawn::StaticClass());

	TestTrue(TEXT("A pawn's default acceleration should be bigger than zero."), testPawn->acceleration() > 0);

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAnAcceleratingPawnMakeItAccelerateCommand);

bool FSpawningAnAcceleratingPawnMakeItAccelerateCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();

	AAcceleratingPawn* testPawn = testWorld->SpawnActor<AAcceleratingPawn>(AAcceleratingPawn::StaticClass());

	testPawn->accelerate();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAnAcceleratingPawnXLocationCommand, int, tickCount, int,
                                                 tickLimit, FAutomationTestBase*, test);

bool FCheckAnAcceleratingPawnXLocationCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
		AAcceleratingPawn* testPawn = Cast<AAcceleratingPawn, AActor>(
			UGameplayStatics::GetActorOfClass(testWorld, AAcceleratingPawn::StaticClass()));
		if (testPawn)
		{
			float currentXLocation = testPawn->GetActorLocation().X;


			if (currentXLocation > 0)
			{
				test->TestTrue(
					TEXT("The pawn X location should increase after an acceleration is added (after ticking)."),
					currentXLocation > 0);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			++tickCount;

			if (tickCount > tickLimit)
			{
				test->TestFalse(
					TEXT("Tick limit reached for this test. The pawn X Location never changed from zero."),
					tickCount > tickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnShouldMoveForwardWhenAcceleratedTest,
                                 "Game.Unit.AcceleratingPawnTests.ShouldMoveForwardWhenAccelerated",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnShouldMoveForwardWhenAcceleratedTest::RunTest(const FString& Parameters)
{
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawningAnAcceleratingPawnMakeItAccelerateCommand);
		int tickCount = 0;
		int tickLimit = 3;
		ADD_LATENT_AUTOMATION_COMMAND(FCheckAnAcceleratingPawnXLocationCommand(tickCount, tickLimit, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAnAcceleratingPawnSpeedIncreaseCommand, int, tickCount, int,
                                                 tickLimit, FAutomationTestBase*, test);

bool FCheckAnAcceleratingPawnSpeedIncreaseCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
		AAcceleratingPawn* testPawn = Cast<AAcceleratingPawn, AActor>(
			UGameplayStatics::GetActorOfClass(testWorld, AAcceleratingPawn::StaticClass()));
		if (testPawn)
		{
			float currentSpeed = testPawn->currentSpeed();


			if (currentSpeed > 0)
			//it would be better to align the ship first and then check against it's forward vector. We have to be careful of gravity in this test.
			{
				test->TestTrue(
					TEXT("The pawn speed should increase after accelerating (after ticking)."), currentSpeed > 0);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}

			++tickCount;

			if (tickCount > tickLimit)
			{
				test->TestFalse(
					TEXT("Tick limit reached for this test. The pawn speed never changed from zero."),
					tickCount > tickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnSpeedIncreasesWhenAcceleratesTest,
                                 "Game.Unit.AcceleratingPawnTests.SpeedIncreasesWhenAccelerates",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnSpeedIncreasesWhenAcceleratesTest::RunTest(const FString& Parameters)
{
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawningAnAcceleratingPawnMakeItAccelerateCommand);
		int tickCount = 0;
		int tickLimit = 3;
		ADD_LATENT_AUTOMATION_COMMAND(FCheckAnAcceleratingPawnSpeedIncreaseCommand(tickCount, tickLimit, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAnAcceleratingPawnPressAccelerationKeyCommand);

bool FSpawningAnAcceleratingPawnPressAccelerationKeyCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();

	AAcceleratingPawn* testPawn = testWorld->SpawnActor<AAcceleratingPawn>(AAcceleratingPawn::StaticClass());

	AGameModeBase* testGameMode = testWorld->GetAuthGameMode();

	testGameMode->SpawnPlayerFromSimulate(FVector(), FRotator());


	APlayerController* jetController = Cast<APlayerController, AActor>(
		testGameMode->GetGameInstance()->GetFirstLocalPlayerController(testWorld));

	FName const accelerateActionName = FName(TEXT("AccelerateAction"));
	//in the editor, we are going to add a new action mapping inside Project settings -> Input
	FKey accelerateKey = TArray<FInputActionKeyMapping>(
		jetController->PlayerInput->GetKeysForAction(accelerateActionName))[0].Key;
	//in the pawn class, we are going to add a player input with:
	//	PlayerInputComponent->BindAction("AccelerateAction", IE_Pressed,this,  &AAcceleratingPawn::accelerate);
	// PlayerInputComponent->BindAction("AccelerateAction", IE_Repeat,this,  &AAcceleratingPawn::accelerate);
	//and in the constructor:
	//AutoPossessPlayer = EAutoReceiveInput::Player0;//this should be changed when we start doing multiplayer. It won't work.
	bool binput = jetController->InputKey(accelerateKey, EInputEvent::IE_Repeat, 5.0f, false);

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAnAcceleratingPawnAcceleratesWhenPressingAccelerationKeyTest,
                                 "Game.Unit.AcceleratingPawnTests.AcceleratesWhenPressingAccelerationKey",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAnAcceleratingPawnAcceleratesWhenPressingAccelerationKeyTest::RunTest(const FString& Parameters)
{
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawningAnAcceleratingPawnPressAccelerationKeyCommand);
		int tickCount = 0;
		int tickLimit = 3;
		ADD_LATENT_AUTOMATION_COMMAND(FCheckAnAcceleratingPawnSpeedIncreaseCommand(tickCount, tickLimit, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnCharacterAndMoveIt);

bool FSpawnCharacterAndMoveIt::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	UWorld* World = GEditor->GetPIEWorldContext()->World();
	AMyCharacter* Character = World->SpawnActor<AMyCharacter>();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	PlayerController->Possess(Character);

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FDidCharacterMove, int, tickCount, int, tickLimit,
                                                 FAutomationTestBase*, test);

bool FDidCharacterMove::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	UWorld* World = GEditor->GetPIEWorldContext()->World();
	AActor* Character = UGameplayStatics::GetActorOfClass(World, AMyCharacter::StaticClass());

	if (!Character)
	{
		return false;
	}

	FVector Location = Character->GetActorLocation();

	UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *Location.ToString());

	if (!Location.Equals(FVector()))
	{
		World->bDebugFrameStepExecution = true;
		return true;
	}

	++tickCount;

	if (tickCount > tickLimit)
	{
		test->AddError("Test ticked out");
		World->bDebugFrameStepExecution = true;
		return true;
	}

	return false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCharacterShouldMove, "Game.Unit.Character.ShouldMove",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FCharacterShouldMove::RunTest(const FString& Parameters)
{
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawnCharacterAndMoveIt);
		ADD_LATENT_AUTOMATION_COMMAND(FDidCharacterMove(0, 3, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS
