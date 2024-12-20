#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Demo/Components/WeaponComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	SetRootComponent(WeaponMesh);

	PickupSphere = CreateDefaultSubobject<USphereComponent>("Pickup Sphere");
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	PickupSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupSphere->SetGenerateOverlapEvents(false);
	PickupSphere->SetSphereRadius(70.0f);
	PickupSphere->SetLineThickness(1.0f);
	PickupSphere->ShapeColor = FColor::Orange;
	PickupSphere->SetupAttachment(RootComponent);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("Weapon Component");
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::PostLoad()
{
	Super::PostLoad();

	if (HasAuthority())
	{
		Server_SetWeaponCollision(ECollisionEnabled::Type::QueryAndPhysics);
		Server_SetWeaponPhysics(true);
		Server_SetOverlapEvents(true);
	}
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::Server_SetWeaponPhysics_Implementation(const bool bNewPhysics)
{
	if (WeaponMesh && PickupSphere)
	{
		WeaponMesh->SetSimulatePhysics(bNewPhysics);
	}
}

void AWeapon::Server_SetWeaponCollision_Implementation(const ECollisionEnabled::Type NewCollisionType)
{
	if (WeaponMesh)
	{
		WeaponMesh->SetCollisionEnabled(NewCollisionType);
	}
}

void AWeapon::Server_SetOverlapEvents_Implementation(const bool bNewEvent)
{
	if (PickupSphere)
	{
		PickupSphere->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		PickupSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		PickupSphere->SetGenerateOverlapEvents(bNewEvent);
	}
}