#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UWeaponComponent;
class USphereComponent;

UCLASS()
class DEMO_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void PostLoad() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> PickupSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponComponent> WeaponComponent;

	UFUNCTION(Server, Reliable)
	void Server_SetWeaponPhysics(const bool bNewPhysics);

	UFUNCTION(Server, Reliable)
	void Server_SetWeaponCollision(const ECollisionEnabled::Type NewCollisionType);

	UFUNCTION(Server, Reliable)
	void Server_SetOverlapEvents(const bool bNewEvent);

public:
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
	FORCEINLINE USphereComponent* GetPickupSphere() const { return PickupSphere; }
	FORCEINLINE UWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }
};
