// Fill out your copyright notice in the Description page of Project Settings.


#include "Thing1.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"


// Sets default values
AThing1::AThing1()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Representation"));
	RootComponent = StaticMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (SphereVisualAsset.Succeeded())
	{
		StaticMesh->SetStaticMesh(SphereVisualAsset.Object);
		StaticMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		StaticMesh->SetWorldScale3D(FVector(0.8f));
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.f;
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = false;

	ActualCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Actual Camera"));
	ActualCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	ActualCamera->bUsePawnControlRotation = false;

	float Val = 100.f;
}

// Called when the game starts or when spawned
void AThing1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThing1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AThing1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThing1::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThing1::MoveRight);
}

void AThing1::MoveForward(float Val)
{
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
	if (Val != 0) 
	{
		AddMovementInput(Direction, Val);
		UE_LOG(LogTemp, Warning, TEXT("W pressed"));


	}

	
}

void AThing1::MoveRight(float Val)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (Val != 0)
	{
		AddMovementInput(Direction, Val);
		UE_LOG(LogTemp, Warning, TEXT("A pressed"));


	}
}

