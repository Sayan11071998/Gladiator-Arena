#pragma once

#include "CoreMinimal.h"
#include "PickableItemBase.h"
#include "PickableWeapon.generated.h"

class UBoxComponent;
class USphereComponent;
class USkeletalMeshComponent;

UCLASS()
class GLADIATORARENA_API APickableWeapon : public APickableItemBase
{
	GENERATED_BODY()

public:	
	APickableWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UBoxComponent* GetDamageBox() const;

protected:
	UPROPERTY(EditAnywhere)
		USphereComponent* MySphere;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* MySkeletalMesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* DamageBox;
};
