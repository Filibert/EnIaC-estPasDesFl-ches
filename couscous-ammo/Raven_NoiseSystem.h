#pragma once

#include <vector>

#include "2d/Vector2D.h"
#include "time/CrudeTimer.h"
#include "misc/utils.h"
#include "../../lua/Raven_Scriptor.h"
#include "../../Raven_Bot.h"
#include "Fuzzy/FuzzyModule.h"

class Raven_NoiseSystem
{
private:
	//a weapon is always (in this game) carried by a bot
	Raven_Bot*    m_pOwner;

	//fuzzy logic is used to determine the desirability of a weapon. Each weapon
	//owns its own instance of a fuzzy module because each has a different rule 
	//set for inferring desirability.
	FuzzyModule   m_FuzzyModule;

	//this is used to keep a local copy of the previous noise score
	//so that we can give some feedback for debugging
	double         m_dXNoiseScore;
	double         m_dYNoiseScore;

	void     InitializeFuzzyModule();
public:
	Vector2D GetNoise();
	Raven_NoiseSystem(Raven_Bot* owner);
	
};

