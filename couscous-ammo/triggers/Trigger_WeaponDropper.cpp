#include "Trigger_WeaponDropper.h"
#include "../lua/Raven_Scriptor.h"
#include "../Raven_ObjectEnumerations.h"
#include "../Raven_Team.h"
#include "../Raven_Bot.h"
#include "../Raven_WeaponSystem.h"

#include "../armory/Weapon_RocketLauncher.h"
#include "../armory/Weapon_RailGun.h"
#include "../armory/Weapon_ShotGun.h"
#include "../armory/Weapon_Blaster.h"
//#include "../armory/Weapon_Grenade.h"

#include "../navigation/Raven_PathPlanner.h"

#include "Debug/DebugConsole.h"


///////////////////////////////////////////////////////////////////////////////
Trigger_WeaponDropper::Trigger_WeaponDropper(Vector2D pos, unsigned int weaponType, int ammo, int team, Raven_Game* world, int node_id) :
	Trigger<Raven_Bot>(BaseGameEntity::GetNextValidID()),
	m_WeaponType(weaponType),
	m_Ammo(ammo),
	m_Team(team),
	m_pWorld(world)
{
	SetPos(pos);
	SetGraphNodeIndex(node_id);
	SetEntityType(weaponType);
	AddCircularTriggerRegion(pos, 5);

	//create the vertex buffer for the rocket shape
	const int NumRocketVerteces = 8;
	const Vector2D rip[NumRocketVerteces] = {	Vector2D(0, 3),
												Vector2D(1, 2),
												Vector2D(1, 0),
												Vector2D(2, -2),
												Vector2D(-2, -2),
												Vector2D(-1, 0),
												Vector2D(-1, 2),
												Vector2D(0, 3) };

	for (int i = 0; i < NumRocketVerteces; ++i)
	{
		m_rocketBufferVertex.push_back(rip[i]);
	}
}

void Trigger_WeaponDropper::Update()
{
	if (!m_pWorld->IsTeamModeOn())
	{
		SetToBeRemovedFromGame();
	}
}

void Trigger_WeaponDropper::Try(Raven_Bot* bot) {
	if (m_pWorld->IsTeamModeOn()) {
		if (this->isActive() && bot->GetTeam()->GetId() == m_Team && this->isTouchingTrigger(bot->Pos(), bot->BRadius()))
		{
			bot->GetWeaponSys()->AddWeapon(EntityType());
			debug_con << "Bot " << bot->ID() << " picked a weapon " << EntityType() << "";

			Raven_Weapon* w = 0;

			switch (EntityType())
			{
			case type_rail_gun:

				w = new RailGun(bot); break;

			//case type_grenade:

				//w = new Grenade(bot); break;

			case type_shotgun:

				w = new ShotGun(bot); break;

			case type_rocket_launcher:

				w = new RocketLauncher(bot); break;

			}//end switch


			 //if the bot holds a weapon of this type, add its ammo
			Raven_Weapon* present = bot->GetWeaponSys()->GetWeaponFromInventory(EntityType());

			if (present)
			{
				present->IncrementRounds(m_Ammo);
			}
			delete w;

			bot->GetTeam()->RemoveDroppedWeapon(m_vPosition);
			SetToBeRemovedFromGame();
			SetInactive();
		}
	}
}



void Trigger_WeaponDropper::Render()
{
	if (isActive())
	{
		gdi->BlackPen();
		Raven_Team::TeamColorBrush(m_Team);
		int sz = 5;
		gdi->Rect(Pos().x - sz, Pos().y - sz, Pos().x + sz + 1, Pos().y + sz + 1);
		//gdi->Circle(m_vPosition, 5);
	}
}