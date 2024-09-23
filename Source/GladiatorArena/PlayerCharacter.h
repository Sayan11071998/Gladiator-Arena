#pragma once

#include "CoreMinimal.h"
#include "ArenaCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GLADIATORARENA_API APlayerCharacter : public AArenaCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void Mouse_X(float Value);
	void Mouse_Y(float Value);

public:
	UFUNCTION()
		virtual void OnBeginOverlap(
			UPrimitiveComponent* OverlapComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bSweep,
			const FHitResult& SweepResult
		);

	void TriggerAttack();
	UFUNCTION()
		virtual void OnWeaponBeginOverlap(
			UPrimitiveComponent* OverlapComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bSweepFrom,
			const FHitResult& SweepResult
		);

	bool AddedOverlapToWeapon;
	bool CanDetectCollision;

	UPROPERTY(BlueprintReadOnly)
		float Health = 100.f;
	bool ApplyDamage();
	void RestartGame();
};