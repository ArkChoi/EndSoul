// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UAnimMontage;
class ACharacter;

UCLASS()
class ENDSOUL_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	TObjectPtr<UAnimMontage> ComboAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	TObjectPtr<UAnimMontage> ChargeAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int ComboCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	uint8 bComboCheak : 1 = 0;

public:
	UFUNCTION(BlueprintCallable)
	bool CheackAnimation(ACharacter* PC);

	UFUNCTION(BlueprintCallable)
	void ComboAttack(ACharacter *PC, bool bIsPlay);

	UFUNCTION(BlueprintCallable)
	void ComboAttackCountUp();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetComboCount() { return ComboCount; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetComboCount(int InComboCount) { ComboCount = InComboCount; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetbComboCheak() { return bComboCheak; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetbComboCheak(bool InbComboCheak) { bComboCheak = InbComboCheak; };
};
