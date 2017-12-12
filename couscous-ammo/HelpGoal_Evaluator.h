#ifndef RAVEN_HELP_EVALUATOR
#define RAVEN_HELP_GOAL_EVALUATOR
#pragma warning (disable:4786)

#include "./goals/Goal_Evaluator.h"
#include "./Raven_Bot.h"


class HelpGoal_Evaluator :
	public Goal_Evaluator
{
public:
	HelpGoal_Evaluator(double bias) :Goal_Evaluator(bias) {}

	double CalculateDesirability(Raven_Bot* pBot);

	void  SetGoal(Raven_Bot* pEnt);

	void RenderInfo(Vector2D Position, Raven_Bot* pBot);
};

#endif