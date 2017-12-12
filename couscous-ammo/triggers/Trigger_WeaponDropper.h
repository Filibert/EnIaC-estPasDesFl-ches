#ifndef WEAPON_DROPPER_H
#define WEAPON_DROPPER_H

#include "triggers/Trigger.h"
#include "../Raven_Bot.h"
#include "../Raven_Game.h"

class Trigger_WeaponDropper : public Trigger<Raven_Bot>
{
private:
	//vertex buffers for rocket shape
	std::vector<Vector2D>         m_rocketBufferVertex;
	std::vector<Vector2D>         m_rocketBufferVertexTrans;

	unsigned int m_WeaponType;
	int m_Ammo;
	int m_Team;
	Raven_Game* m_pWorld;

public:

	Trigger_WeaponDropper(Vector2D pos, unsigned int weapon, int ammo, int team, Raven_Game* world, int node_id);

	void Update();

	//if triggered, this trigger will call the PickupWeapon method of the
	//bot. PickupWeapon will instantiate a weapon of the appropriate type.
	void Try(Raven_Bot* bot);

	//draws a symbol representing the weapon type at the trigger's location
	void Render();

};

#endif