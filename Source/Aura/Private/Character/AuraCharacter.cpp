// Copyright Liu Xuefan


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Controller接管 Character时 调用 设置AbilityActorInfo
	InitAbilityActorInfo();
	
}


void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// 为客户端的Character设置AbilityActorInfo
	InitAbilityActorInfo();
}



void AAuraCharacter::InitAbilityActorInfo()
{
	// 一般在GameMode配置的时候会将 PlayerState设置给 Controller
	// 在 Controller接管 Character时，会将 Controller拥有的 PlayerState设置该 Character
	// 该 PossessedBy()函数也是发生在 Controller接管 Character时，但是顺序上在设置 PlayerState之后
	// 所以这个地方已经能够获取到关联到该 Character的 PlayerState
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();

	// Player ASC的 OwnerActor是 PlayerState，AvatorActor是 PlayerCharacter
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	
	// 把 PlayerState 中的ASC和AS拷贝一份给PlayerCharacter
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	
}


