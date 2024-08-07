// Copyright Liu Xuefan


#include "Character/AuraCharacterBase.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");  // 这里不需要使用文本宏，因为传入的参数是一个FName，会对string进行隐式转换
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));   // 将武器插到一个名为"WeaponHandSocket"的插座上
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);   // 将武器的碰撞关闭
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}











































