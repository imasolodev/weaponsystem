#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Demo/Data/WeaponDataSet.h"
#include "WeaponComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMO_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;
	virtual void PostLoad() override;

private:
	UPROPERTY(Replicated)
	uint16 Ammo;

	UPROPERTY(Replicated)
	uint8 Clip;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = Data, meta = (AllowPrivateAccess = "true"))
	FWeaponData WeaponData;

	UFUNCTION(Server, Reliable)
	void Server_SetClientAmmoAndClip();

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE uint16 GetAmmoCount() const { return Ammo; }
	FORCEINLINE uint8 GetClipCount() const { return Clip; }
	FORCEINLINE FWeaponData GetWeaponData() const { return WeaponData; }
	FORCEINLINE FName GetWeaponID() const { return WeaponData.ID; }
	FORCEINLINE FName GetWeaponSocket() const { return WeaponData.Socket; }
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponData.WeaponType; }
};
