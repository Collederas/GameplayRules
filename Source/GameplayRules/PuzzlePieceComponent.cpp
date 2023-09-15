#include "PuzzlePieceComponent.h"

#include "PuzzleManager.h"


bool UPuzzlePieceComponent::TriggerPuzzleCheck()
{
	if (bCanTriggerCheck && MyPuzzleManager)
	{
		const bool Solved =  MyPuzzleManager->IsTargetSolved(GetOwner(), true);
		OnCheckTriggered.Broadcast(GetOwner(), Solved);
		return Solved;
	}
#if WITH_EDITOR
		UE_LOG(LogTemp, Verbose, TEXT("Puzzle check triggered on %s, but it is disabled or no manager is registered."
								"Make sure there is at least one condition targeting this actor in your PuzzleManager."), *GetOwner()->GetName());
#endif
	
	return false;
}

bool UPuzzlePieceComponent::IsSolved()
{
	if (MyPuzzleManager)
	{
		return MyPuzzleManager->IsTargetSolved(GetOwner());
	}
	return false;
}

void UPuzzlePieceComponent::RegisterManager(APuzzleManager* Manager)
{
	MyPuzzleManager = Manager;
}
