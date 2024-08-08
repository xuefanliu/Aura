// Copyright Liu Xuefan


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;  // 当当前实体在服务器上发生变化时，变化将被复制和发送给其他客户端
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();   // 处理指针高亮

	
}




void AAuraPlayerController::CursorTrace()
{

	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	 *  1. LastActor = null && ThisActor = null
	 *		- Do nothing
	 *	2. LastActor = null && ThisActor != null
	 *		- HightLight ThisActor
	 *  3. LastActor != null && ThisActor = null
	 *		- UnHighLight LastActor
	 *	4. LastActor != null && ThisActor != null
	 *		- LastActor == ThisActor:
	 *			- Do nothing
	 *		- LastActor != ThisActor:
	 *			- HightLight ThisActor
	 *			- UnHighLight LasyActor
	 **/

	if(LastActor == nullptr)
	{
		if(ThisActor == nullptr)
		{
			// Do nothing
		}else
		{
			ThisActor->HighlightActor();
		}
	}else
	{
		if(ThisActor == nullptr)
		{
			LastActor->UnHighlightActor();
		}else
		{
			if(ThisActor == LastActor)
			{
				// Do nothing
			}else
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
		}
	}
}




void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}



void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}




void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);  // Yaw就是在水平平面上旋转的方向

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);   // 水平平面上，朝前是 X
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);     // 水平平面上，朝右是 Y
	
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);  // TODO：想不通啊
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


