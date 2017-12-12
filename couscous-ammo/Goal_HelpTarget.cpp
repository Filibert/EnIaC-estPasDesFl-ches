#include "Goal_HelpTarget.h"
#include "./goals/Goal_SeekToPosition.h"
#include "./goals/Goal_HuntTarget.h"
#include "./goals/Goal_DodgeSideToSide.h"
#include "./Raven_Bot.h"
#include "../Common/Game/EntityManager.h"
#include "./Raven_Team.h"
#include "./goals/Goal_MoveToPosition.h"
#include "Messaging/Telegram.h"

#include "debug/DebugConsole.h"




//------------------------------- Activate ------------------------------------
//-----------------------------------------------------------------------------
void Goal_HelpTarget::Activate()
{
	m_iStatus = active;

	//if this goal is reactivated then there may be some existing subgoals that
	//must be removed
	RemoveAllSubgoals();

	//debug_con << "rgetijerttigjero" << "";

	Raven_Team* team = m_pOwner->GetTeam();
	Raven_Bot* endangeredBot = (Raven_Bot*)EntityManager::Instance()->GetEntityFromID(team->GetEndangeredBotId());
	if (endangeredBot->GetTargetSys()->isTargetPresent() && !endangeredBot->isDead()) {
		Vector2D targetPos = (endangeredBot->Pos() + endangeredBot->GetTargetBot()->Pos()) / 2;
		debug_con << "BOT " << endangeredBot->ID() << " ASKED FOR HELP!!" << "";
		AddSubgoal(new Goal_MoveToPosition(m_pOwner, targetPos));
	}

	/*else
	{
		AddSubgoal(new Goal_HuntTarget(m_pOwner));
	}*/
}

//-------------------------- Process ------------------------------------------
//-----------------------------------------------------------------------------
int Goal_HelpTarget::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();

	//process the subgoals
	m_iStatus = ProcessSubgoals();

	ReactivateIfFailed();

	return m_iStatus;
}




