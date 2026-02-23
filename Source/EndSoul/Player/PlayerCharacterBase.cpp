// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ChildActorComponent.h"
#include "../Weapon/WeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APlayerCharacterBase::APlayerCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SocketOffset = FVector(0, 0, 100);
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.f, 0));

	bReplicates = true; //이걸 해줘야 ReplicatedUsing 가 동작되는 듯 하다.
}

// Called when the game starts or when spawned
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	OnTakeAnyDamage.AddDynamic(this, &APlayerCharacterBase::ProcessOnTakeAnyDamage);
	
}

// Called every frame
void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::Look);

		//EnhancedInputComponent->BindAction(ComboAttackAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::ComboAttack);

		EnhancedInputComponent->BindAction(ChargeAttackAction, ETriggerEvent::Started, this, &APlayerCharacterBase::ChargingChargeAttack);
		//EnhancedInputComponent->BindAction(ChargeAttackAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::ChargeAttack);
		EnhancedInputComponent->BindAction(ChargeAttackAction, ETriggerEvent::Canceled, this, &APlayerCharacterBase::CancelChargeAttack);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent_Not_Found"));
	}
}

void APlayerCharacterBase::OnRep_HPUpdate(const float InHP)
{
	OnChangeHP.Broadcast(CurrentHP / MaxHP);
}

void APlayerCharacterBase::OnRep_StaminaUpdate(const float InStamina)
{
	OnChangeStamina.Broadcast(CurrentStamina / MaxStamina);
}

void APlayerCharacterBase::Move(const FInputActionValue& Value)
{
	FVector2D MovementValue = Value.Get<FVector2D>();

	const FRotator CameraRotation = GetController()->GetControlRotation();
	const FRotator YawRotation = FRotator(0, CameraRotation.Yaw, 0);
	const FRotator YawRollRotation = FRotator(0, CameraRotation.Yaw, CameraRotation.Roll);


	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(YawRotation);
	AddMovementInput(ForwardVector, MovementValue.Y);

	const FVector RightVector = UKismetMathLibrary::GetRightVector(YawRollRotation);
	AddMovementInput(RightVector, MovementValue.X);

}

void APlayerCharacterBase::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();

	AddControllerPitchInput(-LookValue.Y);
	AddControllerYawInput(LookValue.X);
}

void APlayerCharacterBase::ComboAttack(const float InUsingStamina)
{
	if (CheackStamina(InUsingStamina))
	{
		return;
	}

	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->ComboAttack(this, false);
		CurrentStamina -= InUsingStamina;
	}
}

void APlayerCharacterBase::ChargeAttack(const float InUsingStamina)
{
	if (CheackStamina(InUsingStamina))
	{
		return;
	}

	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->ChargeAttack(this);
		CurrentStamina -= InUsingStamina;
	}
}

void APlayerCharacterBase::CancelChargeAttack()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->CancelChargeAttack(this);
	}
}

void APlayerCharacterBase::ChargingChargeAttack()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->ChargingChargeAttack(this);
	}
}

void APlayerCharacterBase::SetMovemoentSpeed(float InSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = InSpeed;
}

void APlayerCharacterBase::DoRun(float InStaminaDownSpeed)
{
	if (CheackStamina(InStaminaDownSpeed))
	{
		EndRun();
		return;
	}

	SetMovemoentSpeed(600.f);
	CurrentStamina -= InStaminaDownSpeed;

}

void APlayerCharacterBase::EndRun()
{
	SetMovemoentSpeed(300.f);
}

void APlayerCharacterBase::Dash(UAnimMontage* InMontage, float InForce)
{
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector( this->GetActorRotation() );
	ForwardVector = ForwardVector * InForce;

	GetCharacterMovement()->AddImpulse(ForwardVector, true);
	PlayAnimMontage(InMontage, 3.f);
}

void APlayerCharacterBase::DoGuard(float MovementSpeed)
{
	SetMovemoentSpeed(MovementSpeed);
	bIsGuard = true;

}

void APlayerCharacterBase::EndGuard(float MovementSpeed)
{
	SetMovemoentSpeed(MovementSpeed);
	bIsGuard = false;

}

void APlayerCharacterBase::PerfectGuard(UAnimMontage* InMontage)
{
	PlayAnimMontage(InMontage);
}

void APlayerCharacterBase::ReChargeStamina(float InStaminaCharge)
{
	if (CurrentStamina < MaxStamina)
	{
		CurrentStamina += InStaminaCharge;
	}
}

bool APlayerCharacterBase::CheackStamina(float InUseStamina)
{
	if (CurrentStamina - InUseStamina <= 0)
	{
		return true;
	}

	return false;
}

void APlayerCharacterBase::ProcessOnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	ACharacter* Enemy = Cast<ACharacter>(DamageCauser);
	if (Enemy)
	{
		FVector EnemyLocation = Enemy->GetMesh()->GetComponentLocation();
		FVector MyLocation = GetCapsuleComponent()->GetComponentLocation();
		FVector ImpulseForce;
		ImpulseForce = (MyLocation - EnemyLocation).GetSafeNormal();
		ImpulseForce.Z = 0;
		ImpulseForce *= 1000.f;
		GetCapsuleComponent()->AddImpulse(ImpulseForce);
	}
	SetCurrentHP((GetCurrentHP()-10.f));
	OnRep_HPUpdate(1);

	UE_LOG(LogTemp, Warning, TEXT("HP : %f"), CurrentHP);
}

void APlayerCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacterBase, CurrentHP);
	DOREPLIFETIME(APlayerCharacterBase, CurrentStamina);

	DOREPLIFETIME(APlayerCharacterBase, bIsGuard);
}

