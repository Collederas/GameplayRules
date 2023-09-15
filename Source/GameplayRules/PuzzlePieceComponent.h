#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzlePieceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCheckTriggered, AActor*, ActorPiece, bool, Solved);

class APuzzleManager;

/**
 * Through the Manager, this allows access of the status of this piece in the context
 * of the Puzzle it belongs to.
 */
UCLASS(BlueprintType, Blueprintable)
class UPuzzlePieceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Can be used to prevent this component to ever triggering a check,
	 * even if it receives a TriggerPuzzleCheck call. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Puzzle Piece")
	bool bCanTriggerCheck = true;

	UPROPERTY(BlueprintAssignable, Category = "Puzzle Piece")
	FOnCheckTriggered OnCheckTriggered;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Puzzle Piece")
	bool TriggerPuzzleCheck();
	
	UFUNCTION(BlueprintPure, Category = "Puzzle Piece")
	bool IsSolved();

	UFUNCTION(BlueprintPure, Category = "Puzzle Piece")
	APuzzleManager* GetPuzzleManager() const { return MyPuzzleManager; }

private:
	friend APuzzleManager;

	UPROPERTY()
	TObjectPtr<APuzzleManager> MyPuzzleManager;

private:
	void RegisterManager(APuzzleManager* Manager);
	void UnregisterManager() { MyPuzzleManager = nullptr; }
};
