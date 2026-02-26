
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PD_NPC_Combat_Interface.generated.h"


UINTERFACE(MinimalAPI)
class UPD_NPC_Combat_Interface : public UInterface
{
	GENERATED_BODY()
};


class PROJECT4_API IPD_NPC_Combat_Interface
{
	GENERATED_BODY()

public:
	virtual void Attack() {};
	virtual void SpecialAttack() {};
};
