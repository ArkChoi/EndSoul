// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class ENDSOUL_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UChildActorComponent> Weapon;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UChildActorComponent* GetWeapon() { return Weapon; };

	//Base State
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	float MaxHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	float CurrentHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	float Grogy = 100.f;

	//Base State
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxHP() { return MaxHP; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHP() { return CurrentHP; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetHP(float InHP) { CurrentHP = InHP; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetGrogy() { return Grogy; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetGrogy(float InGrogy) { Grogy = InGrogy; };

	UFUNCTION(BlueprintCallable)
	void Attack(UAnimMontage* InMontage);


public:
	UFUNCTION()
	void ProcessOnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

};
