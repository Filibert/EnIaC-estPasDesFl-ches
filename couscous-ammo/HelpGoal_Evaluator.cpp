#include "HelpGoal_Evaluator.h"
#include "./goals/Goal_Think.h"
#include "./goals/Raven_Goal_Types.h"
#include "./Raven_WeaponSystem.h"
#include "./Raven_ObjectEnumerations.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "./goals/Raven_Feature.h"
#include "./Raven_Game.h"
#include "../Common/Game/EntityManager.h"
#include "./goals/Goal_Composite.h"


#include "debug/DebugConsole.h"

//------------------ CalculateDesirability ------------------------------------
//
//  returns a value between 0 and 1 that indicates the Rating of a bot (the
//  higher the score, the stronger the bot).
//-----------------------------------------------------------------------------
double HelpGoal_Evaluator::CalculateDesirability(Raven_Bot* pBot)
{
	double Desirability = 0.0;
	Raven_Team* team = pBot->GetTeam();

	//debug_con << " Is Help Nedded???" << team->GetWorld()->IsTeamModeOn() << "";

	if (team->isHelpNeeded() &&  team->GetWorld()->IsTeamModeOn()) {
		const double Tweaker = 1.0;

		Raven_Bot* endangeredBot = (Raven_Bot*)EntityManager::Instance()->GetEntityFromID(team->GetEndangeredBotId());
		bool isOwner = (team->GetEndangeredBotId() == pBot->ID());
		if (!isOwner && (endangeredBot->GetTargetSys()->isTargetPresent()) && !(endangeredBot->isDead()))
		{
			debug_con << "BOT " << endangeredBot->ID() << " called for help!!" << "";

			Desirability = Tweaker *
				Raven_Feature::Health(pBot) *
				Raven_Feature::TotalWeaponStrength(pBot);
		}

		Desirability *= m_dCharacterBias;
	}

	return Desirability;
}

//----------------------------- SetGoal ---------------------------------------
//-----------------------------------------------------------------------------
void HelpGoal_Evaluator::SetGoal(Raven_Bot* pBot)
{
	pBot->GetBrain()->AddGoal_HelpTarget();
}

//-------------------------- RenderInfo ---------------------------------------
//-----------------------------------------------------------------------------
void HelpGoal_Evaluator::RenderInfo(Vector2D Position, Raven_Bot* pBot)
{
	gdi->TextAtPos(Position, "AT: " + ttos(CalculateDesirability(pBot), 2));
	return;

	std::string s = ttos(Raven_Feature::Health(pBot)) + ", " + ttos(Raven_Feature::TotalWeaponStrength(pBot));
	gdi->TextAtPos(Position + Vector2D(0, 12), s);
}