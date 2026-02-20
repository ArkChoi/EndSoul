// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeHP, const float, InEHP);

UCLASS()
class ENDSOUL_API APlayerCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FOnChangeHP OnChangeHP;

public:
	UFUNCTION()
	void OnRep_CurrentHP(const float InHP);

	//Base
protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <class USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <class UCameraComponent> Camera;

	UPROPERTY(Category = Character, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UChildActorComponent> Weapon;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UChildActorComponent* GetWeapon() { return Weapon; };

	//Movement
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> ComboAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> ChargeAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	TObjectPtr<UAnimMontage> DashMontage;

public:
	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void ComboAttack();

	UFUNCTION(BlueprintCallable)
	void ChargeAttack();

	UFUNCTION(BlueprintCallable)
	void CancelChargeAttack();

	UFUNCTION(BlueprintCallable)
	void ChargingChargeAttack();

	UFUNCTION(BlueprintCallable)
	void SetMovemoentSpeed(float InSpeed);

	UFUNCTION(BlueprintCallable)
	void Dash(UAnimMontage* InMontage, float InForce);

	UFUNCTION(BlueprintCallable)
	void StartGuard(float MovementSpeed);

	UFUNCTION(BlueprintCallable)
	void EndGuard(float MovementSpeed);

	UFUNCTION(BlueprintCallable)
	void PerfectGuard(UAnimMontage* InMontage);

	//Animation
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", Replicated)
	uint8 bIsGuard : 1 = false;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetbIsGuard() { return bIsGuard; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetbIsGuard(bool Inbool) { bIsGuard = Inbool; };

	//State
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Replicated)
	float MaxHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated)
	float CurrentHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Replicated)
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", Replicated)
	float CurrentStamina = 100.f;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxHP() { return MaxHP; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCurrentHP() { return CurrentHP; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCurrentHP(float InCurrentHP) { CurrentHP = InCurrentHP; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxStamina() { return MaxStamina; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCurrentStamina() { return CurrentStamina; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCurrentStamina(float InCurrentStamina) { CurrentStamina = InCurrentStamina; };

	//ETC
public:
	UFUNCTION()
	void ProcessOnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
