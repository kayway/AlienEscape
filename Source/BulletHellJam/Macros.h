#pragma once

#include "Engine/GameEngine.h"

#define ScreenPrint(slotID, duration, colour, message) if(GEngine){GEngine->AddOnScreenDebugMessage(slotID, duration, colour, message);}
#define QuickPrint(message) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, message);}