// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeEHP, const float, InEHP);

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
	FOnChangeEHP OnChangeEHP;

public:
	UFUNCTION(BlueprintCallable)
	void OnRep_EHPUpdate(const float InEHP);

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UChildActorComponent* GetWeapon() { return Weapon; };

	//Base State
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	FString Name = "EnemyBase";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	float MaxHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	float CurrentHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	float MaxGrogy = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	float CurrentGrogy = 100.f;

	//Base State
public:
	UFUNCTION(BlueprintCallable)
	virtual FString GetName();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxHP() { return MaxHP; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHP() { return CurrentHP; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetHP(float InHP) { CurrentHP = InHP; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxGrogy() { return MaxGrogy; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCurrentGrogy() { return CurrentGrogy; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCurrentGrogy(float InCurrentGrogy) { CurrentGrogy = InCurrentGrogy; };

	UFUNCTION(BlueprintCallable)
	void Attack(UAnimMontage* InMontage);

	UFUNCTION(BlueprintCallable)
	void Grogy(UAnimMontage* InMontage);

	//Anime State
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", Replicated)
	uint8 bIsGrogy : 1 = false;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetbIsGrogy() { return bIsGrogy; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetbIsGrogy(bool Inbool) { bIsGrogy = Inbool; };

	UFUNCTION(BlueprintCallable)
	bool AnimeCheack(UAnimMontage* InMontage);

public:
	UFUNCTION(BlueprintCallable)
	void ProcessOnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
