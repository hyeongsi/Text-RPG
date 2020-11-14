#include "ThrowStonesSkill.h"
#include "MapManager.h"
#include "Projectile.h"
#include "player.h"

ThrowStonesSkill::ThrowStonesSkill(string skill_name, int use_mp, int power)
{
	this->skill_name = skill_name;
	this->use_mp = use_mp;
	this->power = power;
}

void ThrowStonesSkill::UseSkill(Player* player)
{
	if (!(player->GetMp() >= use_mp))
		return;

	MapManager* mapManager = MapManager::GetInstance();
	mapManager->SetProjectileVector(new Projectile(player->GetPos(), player->GetDir(), power));

	player->SetMp(player->GetMp()-use_mp);
}
