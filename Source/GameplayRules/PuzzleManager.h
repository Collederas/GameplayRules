#pragma once

#include "CoreMinimal.h"
#include "Actions/PuzzleAction.h"
#include "PuzzleManager.generated.h"

class UPuzzleCondition;

USTRUCT(BlueprintType)
struct FPuzzleConditionContainer
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<TObjectPtr<UPuzzleCondition>> Conditions;
};


UCLASS()
class GAMEPLAYRULES_API APuzzleManager : public AActor
{
	GENERATED_BODY()

public:
	APuzzleManager();

	// Checks that target is solved (= all conditions associated with it are solved)
	// If UpdateState is true, then it will first update the SolvedTargets
	// automatically by performing an update check.
	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	bool IsTargetSolved(AActor* Target, bool bUpdateState = false);
	
	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	TMap<AActor*, bool> GetSolvedTargets() { return SolvedTargets; }
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Puzzle")
	TMap<TObjectPtr<AActor>, FPuzzleConditionContainer> TargetConditionsMap;
	
	UPROPERTY(EditAnywhere, Category = "Puzzle")
	TArray<TObjectPtr<UPuzzleAction>> Actions;

	// Keeps track of the puzzle state per each target
	TMap<AActor*, bool> SolvedTargets;

private:
	// Register this Puzzle with all Targets, provided they have a PuzzlePieceComponent
	void RegisterWithTargets();
	
	// Checks every condition for every target and updates the SolvedTargets
	// state Map accordingly.
	bool UpdatePuzzleState();
	
	// Solved when -for each target- all conditions are solved
	bool IsPuzzleSolved();

	void ExecuteActions();
};
