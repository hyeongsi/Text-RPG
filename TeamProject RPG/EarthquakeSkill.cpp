#include "EarthquakeSkill.h"
#include "Player.h"
#include "Monster.h"

EarthquakeSkill::EarthquakeSkill(string skill_name, int use_mp, int power)
{
	this->skill_name = skill_name;
	this->use_mp = use_mp;
	this->power = power;
}

void EarthquakeSkill::UseSkill(Player* player)
{
	if (!(player->GetMp() >= use_mp))
		return;

	vector<Monster*>* monster = Monster::GetInstance();

	player->SetMp(player->GetMp()-use_mp);

	int monsterNumber = monster->size();
	//이거 모든몬스터가 안맞는 이유가 몬스터삭제중간에 몬스터죽어가지고 몬스터개체수랑 인덱스랑 안맞아가지고그런거라서
	//꼼수라면 꼼수일수도있는데 암튼 몬스터죽으면 인덱스도 그에맞게 변화되게만듦
	for (int i = 0; i < monster->size(); i++)
	{
		(*monster)[i]->EarthquakeSkillHit(player->GetPos(), power);
		if (monsterNumber > monster->size())	//몬스터죽으면
			i--;								//인덱스값도 하나감소
	}

	monster = nullptr;
}