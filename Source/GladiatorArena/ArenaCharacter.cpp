#include "ArenaCharacter.h"
#include "PickableItemBase.h"
#include "PickableWeapon.h"
#include "Components/BoxComponent.h"

AArenaCharacter::AArenaCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AArenaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AArenaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AArenaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AArenaCharacter::PickShield(APickableItemBase* PickedShield)
{
	if(!PickedShield)
		return false;

	if(!MyShieldActor)
	{
		if(PickedShield->AttachItemTo(GetMesh(), TEXT("DualWeaponPoint")) == true)
		{
			MyShieldActor = PickedShield;
			return true;
		}
	}

	return false;
}

bool AArenaCharacter::PickWeapon(APickableWeapon* PickedWeapon)
{
	if(!PickedWeapon)
		return false;
	
	if(!MyWeaponActor)
	{
		if(PickedWeapon->AttachItemTo(GetMesh(), TEXT("WeaponPoint")) == true)
		{
			MyWeaponActor = PickedWeapon;
			WeaponCollider = MyWeaponActor->GetDamageBox();

			WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			return true;
		}
	}

	return false;
}

void AArenaCharacter::Attack()
{
	bIsAttacking = true;
}