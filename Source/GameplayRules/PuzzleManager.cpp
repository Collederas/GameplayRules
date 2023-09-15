#include "PuzzleManager.h"

#include "PuzzlePieceComponent.h"
#include "Conditions/PuzzleCondition.h"
#include "Actions/PuzzleAction.h"


APuzzleManager::APuzzleManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APuzzleManager::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterWithTargets();
}


void APuzzleManager::RegisterWithTargets()
{
	for(auto& TargetConditions : TargetConditionsMap)
	{
		if (auto* PuzzlePieceComponent = TargetConditions.Key->FindComponentByClass<UPuzzlePieceComponent>())
		{
			PuzzlePieceComponent->RegisterManager(this);

			// Init SolvedTargets to false for each Target
			SolvedTargets.Emplace(TargetConditions.Key, false);
		}
	}
}


bool APuzzleManager::UpdatePuzzleState()
{
	bool bAllTargetsSolved = true;

	for (const TPair<TObjectPtr<AActor>, FPuzzleConditionContainer>& Kvp : TargetConditionsMap)
	{
		const TArray<UPuzzleCondition*>& ConditionsForThisTarget = Kvp.Value.Conditions;
		bool bAllConditionsMetForThisTarget = true;

		for (UPuzzleCondition* Condition : ConditionsForThisTarget)
		{
			if (!Condition->IsConditionMet(Kvp.Key))
			{
				bAllConditionsMetForThisTarget = false;
				break;
			}
		}

		if (bAllConditionsMetForThisTarget)
		{
			// All conditions are met, mark this target as solved
			SolvedTargets.Emplace(Kvp.Key, true);
		}
		else
		{
			// This target didn't meet all conditions. Set the overall state to false.
			bAllTargetsSolved = false;
			// Optionally, clear the solved state for this target if it was previously set.
			SolvedTargets.Emplace(Kvp.Key, false);
		}
	}

	if (bAllTargetsSolved)
	{
		// All targets have all their conditions met, the puzzle is solved: execute
		// reward actions
		ExecuteActions();
		return true;
	}

	// At least one target didn't meet all conditions
	return false;
}


bool APuzzleManager::IsPuzzleSolved()
{
	int32 NumSolvedTargets = 0;

	for (const auto& Kvp : SolvedTargets)
	{
		if (Kvp.Value)
		{
			NumSolvedTargets++;
		}
	}

	return NumSolvedTargets == TargetConditionsMap.Num();
}


bool APuzzleManager::IsTargetSolved(AActor* Target, bool bUpdateState)
{
	if (bUpdateState)
		UpdatePuzzleState();

	const bool* bIsSolved = SolvedTargets.Find(Target);
	return bIsSolved != nullptr && *bIsSolved;
}



void APuzzleManager::ExecuteActions()
{
	for (auto Action : Actions)
	{
		Action->Execute(this);
	}
}