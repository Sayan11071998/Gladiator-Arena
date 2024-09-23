#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArenaCharacter.generated.h"

class APickableItemBase;
class APickableWeapon;
class UBoxComponent;

UCLASS()
class GLADIATORARENA_API AArenaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AArenaCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool bIsAttacking = false;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool bIsAlive = true;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool PickShield(APickableItemBase* PickedShield);
	bool PickWeapon(APickableWeapon* PickedWeapon);

	APickableItemBase* MyShieldActor;
	APickableWeapon* MyWeaponActor;

	UBoxComponent* WeaponCollider;

	void Attack();
};
