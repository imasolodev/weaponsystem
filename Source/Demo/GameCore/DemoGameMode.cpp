#include "DemoGameMode.h"
#include "UObject/ConstructorHelpers.h"

ADemoGameMode::ADemoGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AController> DemoControllerBP(TEXT("/Game/ThirdPerson/Blueprints/BP_DemoController"));
	if (DemoControllerBP.Class)
	{
		PlayerControllerClass = DemoControllerBP.Class;
	}
}
