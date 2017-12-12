#include "Raven_Team.h"
#include "misc/Cgdi.h"


Raven_Team::Raven_Team(int id, Raven_Game* world, int behaviour) :
	m_id(id),
	m_pWorld(world),
	m_behaviour(behaviour)
{

	switch (behaviour)
	{

	case NEUTRAL:
	{
		HealthBias = 1;
		ShotgunBias = 1;
		RocketLauncherBias = 1;
		RailgunBias = 1;
		//GrenadeBias = 1;
		ExploreBias = 1;
		AttackBias = 1;
		HelpBias = 1;

		break;
	}

	case AGGRESSIVE:
	{
		HealthBias = 0;
		ShotgunBias = 0.5;
		RocketLauncherBias = 0.5;
		RailgunBias = 0.5;
		//GrenadeBias = 0;
		ExploreBias = 1;
		AttackBias = 2;
		HelpBias = 0;

		break;
	}

	case DEFENSIVE:
	{
		HealthBias = 2;
		ShotgunBias = 0.5;
		RocketLauncherBias = 0.5;
		RailgunBias = 0.5;
		//GrenadeBias = 1;
		ExploreBias = 0.5;
		AttackBias = 0.5;
		HelpBias = 2;

		break;
	}

	case EXPLORER:
	{
		HealthBias = 0.5;
		ShotgunBias = 1;
		RocketLauncherBias = 1;
		RailgunBias = 1;
		//GrenadeBias = 1;
		ExploreBias = 2;
		AttackBias = 1;
		HelpBias = 1;

		break;
	}

	case LOOTER:
	{
		HealthBias = 1;
		ShotgunBias = 2;
		RocketLauncherBias = 2;
		RailgunBias = 2;
		//GrenadeBias = 1;
		ExploreBias = 1.5;
		AttackBias = 1;
		HelpBias = 1;

		break;
	}
	}
}


//-------------------------- Handle Messages --------------------------------------
//-----------------------------------------------------------------------------
bool Raven_Team::HandleMessage(const Telegram& msg) {

	switch (msg.Msg)
	{
	case Msg_HelpRequested:
		this->endangeredAllyId = msg.Sender;
		this->m_bHelpRequested = true;
		return true;

	case Msg_NoHelpRequested:
		if (msg.Sender == endangeredAllyId) {
			this->m_bHelpRequested = false;
		}
		return true;

	default:
		return false;
		break;
	}

}

void Raven_Team::TeamColorBrush(int id)
{
	switch (id) {

	case Raven_Team::BLUE:
		gdi->BlueBrush();
		break;

	case Raven_Team::GREEN:
		gdi->GreenBrush();
		break;

	case Raven_Team::GREY:
		gdi->GreyBrush();
		break;

	case Raven_Team::ORANGE:
		gdi->OrangeBrush();
		break;

	case Raven_Team::RED:
		gdi->RedBrush();
		break;

	case Raven_Team::WHITE:
		gdi->WhiteBrush();
		break;

	case Raven_Team::YELLOW:
		gdi->YellowBrush();
		break;

	case Raven_Team::PURPLE:
		gdi->PurplePen();
		break;

	case Raven_Team::BLACK:
		gdi->BlackBrush();
		break;

	default:

		gdi->BrownBrush();
	}
}


void Raven_Team::Update()
{
}