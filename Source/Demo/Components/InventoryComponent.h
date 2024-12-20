#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class ADemoCharacter;
class AWeapon;

USTRUCT(BlueprintType)
struct FWeaponInventory
{
	GENERATED_BODY()

	FName ID;
	TSoftClassPtr<AWeapon> WeaponClass;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	friend class ADemoCharacter;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ADemoCharacter* PlayerCharacter = nullptr;
	
	UPROPERTY(Replicated)
	TArray<FWeaponInventory> WeaponInventory;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
