#ifndef RAVEN_TEAM_H
#define RAVEN_TEAM_H
#pragma warning (disable:4786)

#include <list>

#include "Raven_Bot.h"
#include "Raven_Game.h"
#include "Messaging/Telegram.h"
#include "Raven_Messages.h"
#include "Messaging/MessageDispatcher.h"

class Raven_Team
{
public:

	enum BEHAVIOUR { NEUTRAL, AGGRESSIVE, DEFENSIVE, EXPLORER, LOOTER };
	static const int NB_BEHAVIOURS = 5;

	enum { BLUE, GREEN, GREY, ORANGE, RED, WHITE, YELLOW, PURPLE, BLACK };

	Raven_Team(int id, Raven_Game* world, int behaviour);

	double GetHealthBias() { return HealthBias; }
	double GetShotgunBias() { return ShotgunBias; }
	double GetRocketLauncherBias() { return RocketLauncherBias; }
	double GetRailgunBias() { return RailgunBias; }
	//double GetGrenadeBias() { return grenadeBias; }
	double GetExploreBias() { return ExploreBias; }
	double GetAttackBias() { return AttackBias; }
	double GetHelpBias() { return HelpBias; }

	int GetTeamSize() const { return m_bots.size(); }
	int GetId() const { return m_id; }
	Raven_Game* GetWorld() const { return m_pWorld; }

	inline std::string Behaviour()const {

		switch (m_behaviour)
		{
		case NEUTRAL:

			return "NEUTRAL";

			break;

		case AGGRESSIVE:

			return "AGGRESSIVE";

			break;

		case DEFENSIVE:

			return "DEFENSIVE";

			break;

		case EXPLORER:

			return "EXPLORER";

			break;

		case LOOTER:

			return "LOOTER";

			break;

		default:

			return "NONE";

			break;
		}
	}

	std::list<int> Raven_Team::GetTeammatesIds() {
		std::list<int> ids;
		std::list<Raven_Bot*>::iterator curBot = this->m_bots.begin();
		for (curBot; curBot != m_bots.end(); ++curBot) {
			ids.push_back((*curBot)->ID());
		}
		return ids;
	}

	bool HandleMessage(const Telegram& msg);
	int GetEndangeredBotId() { return this->endangeredAllyId; }
	void SetEndangeredBotId(int endangeredBotId) { endangeredAllyId = endangeredBotId; }

	bool isHelpNeeded() { return  /*(this->GetWorld()->IsTeamModeOn()) && (*/this->m_bHelpRequested/*)*/; }
	void SetHelpNeeded(bool v_bHelpRequested) { m_bHelpRequested = v_bHelpRequested; }

	static void TeamColorBrush(int id);

	void Raven_Team::AddTeammate(Raven_Bot* bot) { m_bots.push_back(bot); }
	void Raven_Team::RemoveTeammate(Raven_Bot* bot) { m_bots.remove(bot); }
	void Raven_Team::AddDroppedWeapon(Vector2D pos) { m_DroppedWeapons.push_back(pos); }
	void Raven_Team::RemoveDroppedWeapon(Vector2D pos) { m_DroppedWeapons.remove(pos); }

	void Update();

private:
	std::list<Raven_Bot*> m_bots;
	std::list<Vector2D> m_DroppedWeapons;

	bool				m_bHelpRequested = false;
	int					endangeredAllyId = -1;

	int m_id;
	Raven_Game* m_pWorld;
	int m_behaviour;


	double HealthBias;
	double ShotgunBias;
	double RocketLauncherBias;
	double RailgunBias;
	//double GrenadeBias;
	double ExploreBias;
	double AttackBias;
	double HelpBias;
};

#endif
