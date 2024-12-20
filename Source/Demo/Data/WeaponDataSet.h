#pragma once

#include "CoreMinimal.h"
#include "WeaponDataSet.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	AssaultRifle,
	SMG,
	Pistol,
	Melee
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere)
	FName ID;

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FName Socket;

	UPROPERTY(EditAnywhere)
	uint16 MaxAmmo;

	UPROPERTY(EditAnywhere)
	uint8 ClipSize;

	UPROPERTY(EditAnywhere)
	uint16 Range;

	FWeaponData() :
	WeaponType(EWeaponType::None),
	ID(""),
	Name(FText::GetEmpty()),
	Socket(""),
	MaxAmmo(0),
	ClipSize(0),
	Range(0)
	{}
};
