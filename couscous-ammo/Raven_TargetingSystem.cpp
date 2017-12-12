#include "Raven_TargetingSystem.h"
#include "Raven_Bot.h"
#include "Raven_SensoryMemory.h"
#include "Raven_Game.h"
#include "../Common/Game/EntityManager.h"


//-------------------------------- ctor ---------------------------------------
//-----------------------------------------------------------------------------
Raven_TargetingSystem::Raven_TargetingSystem(Raven_Bot* owner) :m_pOwner(owner),
m_pCurrentTarget(0)
{}



//----------------------------- Update ----------------------------------------

//-----------------------------------------------------------------------------
void Raven_TargetingSystem::Update()
{
	// double ClosestDistSoFar = MaxDouble;
	double MaxBound = MaxDouble;
	m_pCurrentTarget = 0;

	//grab a list of all the opponents the owner can sense
	std::list<Raven_Bot*> SensedBots;
	SensedBots = m_pOwner->GetSensoryMem()->GetListOfRecentlySensedOpponents();


	std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
	for (curBot; curBot != SensedBots.end(); ++curBot)
	{
		//make sure the bot is alive and that it is not the owner
		if ((*curBot)->isAlive() && (*curBot != m_pOwner))
		{
			//make sure the bot is not a team member
			if (!(*curBot)->GetWorld()->IsTeamModeOn() || (*curBot)->GetTeam() != m_pOwner->GetTeam())
			{

				double dist = Vec2DDistanceSq((*curBot)->Pos(), m_pOwner->Pos());

				// compute a bonus if the enemy is aldready being attacked 
				double bonus = 0;

				if ((*curBot)->GetWorld()->IsTeamModeOn())
				{
					std::list<int> alliesIds = this->m_pOwner->GetTeam()->GetTeammatesIds();
					std::list<int>::iterator nextAlly = alliesIds.begin();
					for (nextAlly; nextAlly != alliesIds.end(); ++nextAlly) {
						if (*nextAlly != this->m_pOwner->ID()) {
							Raven_Bot* curAlly = (Raven_Bot*)EntityManager::Instance()->GetEntityFromID(*nextAlly);
							if (curAlly->ID() == (*curBot)->ID()) {
								bonus -= 1 / dist * 1 / (*curBot)->Health() * 100;
							}

						}
					}
				}


				if ((dist + bonus) < MaxBound)
				{
					MaxBound = dist + bonus;
					m_pCurrentTarget = *curBot;
				}
			}
		}
	}
}








bool Raven_TargetingSystem::isTargetWithinFOV()const
{
	return m_pOwner->GetSensoryMem()->isOpponentWithinFOV(m_pCurrentTarget);
}

bool Raven_TargetingSystem::isTargetShootable()const
{
	return m_pOwner->GetSensoryMem()->isOpponentShootable(m_pCurrentTarget);
}

Vector2D Raven_TargetingSystem::GetLastRecordedPosition()const
{
	return m_pOwner->GetSensoryMem()->GetLastRecordedPositionOfOpponent(m_pCurrentTarget);
}

double Raven_TargetingSystem::GetTimeTargetHasBeenVisible()const
{
	return m_pOwner->GetSensoryMem()->GetTimeOpponentHasBeenVisible(m_pCurrentTarget);
}

double Raven_TargetingSystem::GetTimeTargetHasBeenOutOfView()const
{
	return m_pOwner->GetSensoryMem()->GetTimeOpponentHasBeenOutOfView(m_pCurrentTarget);
}
