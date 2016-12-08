#include "stdafx.h"
#include "cPlayerSkillEffect.h"


cPlayerSkillEffect::cPlayerSkillEffect()
{

}


cPlayerSkillEffect::~cPlayerSkillEffect()
{
	MAP_EFFECT::iterator itMap;
	for (itMap = m_mapEffects.begin(); itMap != m_mapEffects.end();)
	{
		for each(auto v in itMap->second){
			SAFE_DELETE(v);
		}
		itMap = m_mapEffects.erase(itMap);
	}
}

void cPlayerSkillEffect::StartEffect(string _Name)
{
	if (m_mapEffects.find(_Name) != m_mapEffects.end()) {
		for each (auto v in m_mapEffects[_Name])
			v->Start();
	}
}

void cPlayerSkillEffect::StopEffect(string _Name)
{
	if (m_mapEffects.find(_Name) != m_mapEffects.end()) {
		for each (auto v in m_mapEffects[_Name])
			v->Stop();
	}
}

void cPlayerSkillEffect::InitPlayerSkill()
{
	//Default Init
	//필요한 effect는 이곳에서 로드한다.


}