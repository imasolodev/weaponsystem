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
	virtual void PostInitializeComponents() override;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> PickupSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponComponent> WeaponComponent;
	
	UPROPERTY(ReplicatedUsing=OnRep_bOverlapEventsEnabled)
	bool bOverlapEventsEnabled = false;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_bOverlapEventsEnabled();
	
	UFUNCTION(Server, Reliable)
	void Server_SetWeaponPhysics(const bool bNewPhysics);

	UFUNCTION(Server, Reliable)
	void Server_SetWeaponCollision(const ECollisionEnabled::Type NewCollisionType);

	UFUNCTION(Server, Reliable)
	void Server_SetOverlapEvents(const bool bNewEvent);

	UFUNCTION(Client, Reliable)
	void Client_SetOverlapEvents(const bool bNewEvent);

	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
	FORCEINLINE USphereComponent* GetPickupSphere() const { return PickupSphere; }
	FORCEINLINE UWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }
};
