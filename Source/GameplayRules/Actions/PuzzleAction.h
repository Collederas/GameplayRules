#pragma once

#include "PuzzleAction.generated.h"

class APuzzleManager;


UCLASS(DefaultToInstanced, EditInlineNew, Blueprintable, Abstract)
class UPuzzleAction : public UObject
{
	GENERATED_BODY()

public:
	/** Logic that defines the resulting action for a solved puzzle
 * Consider using Interaction Gameplay Ability for this. */
	UFUNCTION(BlueprintNativeEvent, Category=Puzzle)
	void Execute(AActor* WorldContextActor);
	virtual void Execute_Implementation(AActor* WorldContextActor) { }
};