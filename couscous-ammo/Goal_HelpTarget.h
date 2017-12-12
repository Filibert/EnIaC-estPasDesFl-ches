#ifndef GOAL_HELPTARGET_H
#define GOAL_HELPTARGET_H
#pragma warning (disable:4786)


#include "Goals/Goal_Composite.h"
#include "Goals/Raven_Goal_Types.h"
#include "./Raven_Bot.h"





class Goal_HelpTarget : public Goal_Composite<Raven_Bot>
{
public:

	Goal_HelpTarget(Raven_Bot* pOwner) :Goal_Composite<Raven_Bot>(pOwner, goal_help_target)
	{}

	void Activate();

	int  Process();

	void Terminate() { m_iStatus = completed; }
};







#endif
