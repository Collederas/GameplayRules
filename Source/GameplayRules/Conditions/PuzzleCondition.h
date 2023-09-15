#pragma once

#include "PuzzleCondition.generated.h"


UCLASS(DefaultToInstanced, EditInlineNew, Blueprintable, Abstract)
class UPuzzleCondition : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Puzzle|Check")
	bool IsConditionMet(AActor* WorldContextActor);

	virtual bool IsConditionMet_Implementation(AActor* WorldContextActor) { return false; }
};
