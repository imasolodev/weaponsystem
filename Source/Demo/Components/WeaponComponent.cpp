#include "WeaponComponent.h"
#include "Net/UnrealNetwork.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponComponent::PostLoad()
{
	Super::PostLoad();

	if (!GetOwner()->HasAuthority())
	{
		Server_SetClientAmmoAndClip();
	}

	else
	{
		Ammo = WeaponData.MaxAmmo - WeaponData.ClipSize;
		Clip = WeaponData.ClipSize;
	}
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponComponent, Ammo);
	DOREPLIFETIME(UWeaponComponent, Clip);
	DOREPLIFETIME(UWeaponComponent, WeaponData);
}

void UWeaponComponent::Server_SetClientAmmoAndClip_Implementation()
{
	Ammo = WeaponData.MaxAmmo - WeaponData.ClipSize;
	Clip = WeaponData.ClipSize;
}