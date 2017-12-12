#include "Raven_NoiseSystem.h"

Raven_NoiseSystem::Raven_NoiseSystem(Raven_Bot* owner)
{
	m_pOwner = owner;
	InitializeFuzzyModule();
}

//---------------------------- Noise -----------------------------------
//
//-----------------------------------------------------------------------------
Vector2D Raven_NoiseSystem::GetNoise()
{
	//fuzzify distance and amount of ammo
	m_FuzzyModule.Fuzzify("DistToTarget", (double)((m_pOwner->Pos() - m_pOwner->GetTargetBot()->Pos()).Length()));
	m_FuzzyModule.Fuzzify("Velocity", (double)m_pOwner->GetTargetBot()->Velocity().Length());
	m_FuzzyModule.Fuzzify("TimeVisible", (double)m_pOwner->GetTargetSys()->GetTimeTargetHasBeenVisible());

	m_dXNoiseScore = m_FuzzyModule.DeFuzzify("XNoise", FuzzyModule::centroid);
	m_dYNoiseScore = m_FuzzyModule.DeFuzzify("YNoise", FuzzyModule::centroid);	

	//TODO: change sign sometimes

	if(std::abs(m_pOwner->Pos().x) - std::abs(m_pOwner->GetTargetBot()->Pos().x) < std::abs(m_pOwner->Pos().y) - std::abs(m_pOwner->GetTargetBot()->Pos().y))
		return Vector2D(m_dXNoiseScore, m_dYNoiseScore);
	else
		return Vector2D(m_dYNoiseScore, m_dXNoiseScore);
	
}

//-------------------------  InitializeFuzzyModule ----------------------------
//
//  set up some fuzzy variables and rules
//-----------------------------------------------------------------------------
void Raven_NoiseSystem::InitializeFuzzyModule()
{
	FuzzyVariable& DistToTarget = m_FuzzyModule.CreateFLV("DistToTarget");

	FzSet& Target_Close = DistToTarget.AddLeftShoulderSet("Target_Close", 0, 25, 150);
	FzSet& Target_Medium = DistToTarget.AddTriangularSet("Target_Medium", 25, 150, 300);
	FzSet& Target_Far = DistToTarget.AddRightShoulderSet("Target_Far", 150, 300, 1000);

	FuzzyVariable& Velocity = m_FuzzyModule.CreateFLV("Velocity");

	FzSet& Target_Velocity_Slow = Velocity.AddLeftShoulderSet("Velocity_Slow", 0, 25, 50);
	FzSet& Target_Velocity_Medium = Velocity.AddTriangularSet("Velocity_Average", 25, 50, 75);
	FzSet& Target_Velocity_Fast = Velocity.AddRightShoulderSet("Velocity_Fast", 50, 75, 100);

	FuzzyVariable& TimeVisible = m_FuzzyModule.CreateFLV("TimeVisible");

	FzSet& Target_Visibility_Time_Short = TimeVisible.AddLeftShoulderSet("Time_Short", 0, 0, 200);
	FzSet& Target_Visibility_Time_Medium = TimeVisible.AddTriangularSet("Time_Medium", 150, 500, 700);
	FzSet& Target_Visibility_Time_Long = TimeVisible.AddRightShoulderSet("Time_Long", 500, 800, 50000);

	FuzzyVariable& XNoise = m_FuzzyModule.CreateFLV("XNoise");

	FzSet& xNoise_VeryStrong = XNoise.AddTriangularSet("XNoise", 75, 100, 100);
	FzSet& xNoise_Strong = XNoise.AddTriangularSet("XNoise", 50, 75, 100);
	FzSet& xNoise_Substantial = XNoise.AddTriangularSet("XNoise", 25, 50, 75);
	FzSet& xNoise_Weak = XNoise.AddTriangularSet("XNoise", 0, 25, 50);
	FzSet& xNoise_VeryWeak = XNoise.AddTriangularSet("XNoise", 0, 0, 25);

	FuzzyVariable& YNoise = m_FuzzyModule.CreateFLV("YNoise");

	FzSet& yNoise_VeryStrong = XNoise.AddTriangularSet("YNoise", 75, 100, 100);
	FzSet& yNoise_Strong = XNoise.AddTriangularSet("YNoise", 50, 75, 100);
	FzSet& yNoise_Substantial = XNoise.AddTriangularSet("YNoise", 25, 50, 75);
	FzSet& yNoise_Weak = XNoise.AddTriangularSet("YNoise", 0, 25, 50);
	FzSet& yNoise_VeryWeak = XNoise.AddTriangularSet("YNoise", 0, 0, 25);


	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Slow, Target_Visibility_Time_Short), xNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Slow, Target_Visibility_Time_Medium), xNoise_Substantial);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Slow, Target_Visibility_Time_Long), xNoise_VeryWeak);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Medium, Target_Visibility_Time_Short), xNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Medium, Target_Visibility_Time_Medium), xNoise_Substantial);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Medium, Target_Visibility_Time_Long), xNoise_Weak);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Fast, Target_Visibility_Time_Short), xNoise_VeryStrong);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Fast, Target_Visibility_Time_Medium), xNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Fast, Target_Visibility_Time_Long), xNoise_Strong);

	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Slow, Target_Visibility_Time_Short), xNoise_Substantial);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Slow, Target_Visibility_Time_Medium), xNoise_Weak);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Slow, Target_Visibility_Time_Long), xNoise_VeryWeak);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Medium, Target_Visibility_Time_Short), xNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Medium, Target_Visibility_Time_Medium), xNoise_Substantial);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Medium, Target_Visibility_Time_Long), xNoise_Weak);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Fast, Target_Visibility_Time_Short), xNoise_VeryStrong);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Fast, Target_Visibility_Time_Medium), xNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Fast, Target_Visibility_Time_Long), xNoise_Strong);

	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Slow, Target_Visibility_Time_Short), xNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Slow, Target_Visibility_Time_Medium), xNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Slow, Target_Visibility_Time_Long), xNoise_Substantial);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Medium, Target_Visibility_Time_Short), xNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Medium, Target_Visibility_Time_Medium), xNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Medium, Target_Visibility_Time_Long), xNoise_Substantial);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Fast, Target_Visibility_Time_Short), xNoise_VeryStrong);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Fast, Target_Visibility_Time_Medium), xNoise_VeryStrong);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Fast, Target_Visibility_Time_Long), xNoise_VeryStrong);


	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Slow, Target_Visibility_Time_Short), yNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Slow, Target_Visibility_Time_Medium), yNoise_Substantial);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Slow, Target_Visibility_Time_Long), yNoise_VeryWeak);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Medium, Target_Visibility_Time_Short), yNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Medium, Target_Visibility_Time_Medium), yNoise_Substantial);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Medium, Target_Visibility_Time_Long), yNoise_Weak);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Fast, Target_Visibility_Time_Short), yNoise_VeryStrong);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Fast, Target_Visibility_Time_Medium), yNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Close, Target_Velocity_Fast, Target_Visibility_Time_Long), yNoise_Strong);

	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Slow, Target_Visibility_Time_Short), yNoise_Substantial);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Slow, Target_Visibility_Time_Medium), yNoise_Weak);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Slow, Target_Visibility_Time_Long), yNoise_VeryWeak);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Medium, Target_Visibility_Time_Short), yNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Medium, Target_Visibility_Time_Medium), yNoise_Substantial);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Medium, Target_Visibility_Time_Long), yNoise_Weak);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Fast, Target_Visibility_Time_Short), yNoise_VeryStrong);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Fast, Target_Visibility_Time_Medium), yNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Medium, Target_Velocity_Fast, Target_Visibility_Time_Long), yNoise_Strong);

	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Slow, Target_Visibility_Time_Short), yNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Slow, Target_Visibility_Time_Medium), yNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Slow, Target_Visibility_Time_Long), yNoise_Substantial);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Medium, Target_Visibility_Time_Short), yNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Medium, Target_Visibility_Time_Medium), yNoise_Strong);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Medium, Target_Visibility_Time_Long), yNoise_Substantial);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Fast, Target_Visibility_Time_Short), yNoise_VeryStrong);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Fast, Target_Visibility_Time_Medium), yNoise_VeryStrong);
	m_FuzzyModule.AddRule(FzAND(Target_Far, Target_Velocity_Fast, Target_Visibility_Time_Long), yNoise_VeryStrong);
}