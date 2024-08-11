// Copyright Liu Xuefan

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 这是玩家类
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	void InitAbilityActorInfo();
	
};
