#include "GameInfo.h"

GameInfo* GameInfo::gameInfoInstance = nullptr;

GameInfo* GameInfo::GetInstance()
{
	if (gameInfoInstance == nullptr)
		gameInfoInstance = new GameInfo();
	
	return gameInfoInstance;
}

void GameInfo::ReleaseInstance()
{
	if (gameInfoInstance)
	{
		delete gameInfoInstance;
		gameInfoInstance = nullptr;
	}
}

const map<string, string>& GameInfo::GetShape(const int& character)
{
	switch (character)
	{
	case MYPLAYER:
		return playerShape;
	case SLIME:
		return slimeShape;
	case OAK:
		return oakShape;
	case TANK:
		return tankShape;
	case ITEMBOX:
		return itemBoxShape;
	case NPC:
		return NPCShape;

	default:
		return playerShape;
	}
}

const string& GameInfo::GetItemShape(string itemName, int option)
{
	try
	{
		switch (option)
		{
		case WEAPON:
			return weaponShape[itemName];
		case ITEM:
			break;
		case WEAPON_SWING_SHAPE:
			return weaponSwingShape[itemName];
		default:
			break;
		}
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
}

const int GameInfo::ReadFileInt(const char* section, const char* key, const char* path)
{
	return GetPrivateProfileIntA(section, key, 0, path);
 }

void GameInfo::ReadFileString(const char* section, const char* key, const char* path)
{
	GetPrivateProfileString(section, key,"", loadData, sizeof(loadData), path);
}
const TCHAR* GameInfo::GetReadFileString(const char* section, const char* key, const char* path)
{
	GetPrivateProfileString(section, key, "", loadData, sizeof(loadData), path);
	return loadData;
}

void GameInfo::LoadWeaponData()
{
	ReadFileString("weapon", "sword", "GameInfo\\weapon.ini");	//칼
	weaponShape["sword"] = loadData;

	ReadFileString("weapon", "axe", "GameInfo\\weapon.ini");	//도끼
	weaponShape["axe"] = loadData;

	//=================================================================

	ReadFileString("weaponSwing", "sword", "GameInfo\\weaponSwing.ini");	//칼 공격 모션
	weaponSwingShape["sword"] = loadData;

	ReadFileString("weaponSwing", "axe", "GameInfo\\weaponSwing.ini");	//도끼 공격 모션
	weaponSwingShape["axe"] = loadData;
}

void GameInfo::LoadItemBoxShape()
{
	if (itemBoxShape.size() > 4)
		return;

	ReadFileString("itembox", "head", "GameInfo\\itemBox.ini");
	itemBoxShape["head"] = loadData;

	ReadFileString("itembox", "body", "GameInfo\\itemBox.ini");
	itemBoxShape["body"] = loadData;

	ReadFileString("itembox", "legs", "GameInfo\\itemBox.ini");
	itemBoxShape["legs"] = loadData;
}

void GameInfo::LoadNewData()
{
	int hp = 0;
	int power = 0;
	int mp = 0;

	hp = ReadFileInt("player", "hp", "GameInfo\\player.ini");//섹션수정
	mp = ReadFileInt("player", "mp", "GameInfo\\player.ini");
	power = ReadFileInt("player", "power", "GameInfo\\player.ini");//섹션수정
	player->SetStats(hp, power,mp);
}

void GameInfo::LoadPlayerStats(const string& path, const string& name)
{
	int hp = 0;
	int power = 0;
	int mp = 0;
	int exp = 0;
	int level = 0;
	string weapon;

	hp = ReadFileInt(name.c_str(), "hp", path.c_str());//섹션수정
	mp = ReadFileInt("player", "mp", "GameInfo\\player.ini");
	power = ReadFileInt(name.c_str(), "power", path.c_str());//섹션수정
	exp = ReadFileInt(name.c_str(), "exp", path.c_str());
	level = ReadFileInt(name.c_str(), "level", path.c_str());
	weapon = GetReadFileString(name.c_str(), "currentWeapon", path.c_str());
	
	player->SetStats(hp, power, mp,exp, level, weapon);
}

void GameInfo::LoadPlayerShape()
{
	ReadFileString("player", "head", "GameInfo\\player.ini");	//머리
	playerShape["head"] = loadData;

	ReadFileString("player", "body", "GameInfo\\player.ini");	//몸
	playerShape["body"] = loadData;

	ReadFileString("player", "legs", "GameInfo\\player.ini");	//다리
	playerShape["legs"] = loadData;

	ReadFileString("player", "walkingRight1", "GameInfo\\player.ini");	//우측이동모션1
	playerShape["walkingRight1"] = loadData;

	ReadFileString("player", "walkingRight2", "GameInfo\\player.ini");	//우측이동모션2
	playerShape["walkingRight2"] = loadData;

	ReadFileString("player", "walkingLeft1", "GameInfo\\player.ini");	//좌측이동모션1
	playerShape["walkingLeft1"] = loadData;

	ReadFileString("player", "walkingLeft2", "GameInfo\\player.ini");	//좌측이동모션2
	playerShape["walkingLeft2"] = loadData;

	ReadFileString("playerState", "pickupHead", "GameInfo\\player.ini");	//줍기모션(머리)
	playerShape["pickupHead"] = loadData;

	ReadFileString("playerState", "pickupBody", "GameInfo\\player.ini");	//줍기모션(몸통)
	playerShape["pickupBody"] = loadData;

	ReadFileString("playerState", "pickupLegs", "GameInfo\\player.ini");	//줍기모션(다리)
	playerShape["pickupLegs"] = loadData;
}

void GameInfo::LoadInventoryItem(const string& path, const string& name)
{
	int inventorySize = 0;
	Inventory &tempInventory = player->GetInventory();

	inventorySize = ReadFileInt(name.c_str(), "size", path.c_str());//섹션수정
	for (int i = 0; i < inventorySize; i++)
		tempInventory.PushItem(ReadFileInt(name.c_str(), to_string(i).c_str(), path.c_str()), true);
}

void GameInfo::LoadNPCShape()
{
	ReadFileString("npc", "info", "GameInfo\\npc.ini");	//이름
	NPCShape["info"] = loadData;

	ReadFileString("npc", "head", "GameInfo\\npc.ini");	//머리
	NPCShape["head"] = loadData;

	ReadFileString("npc", "body", "GameInfo\\npc.ini");	//몸통
	NPCShape["body"] = loadData;

	ReadFileString("npc", "legs", "GameInfo\\npc.ini");	//다리
	NPCShape["legs"] = loadData;
}

void GameInfo::LoadMonsterShape(vector<Monster*>* monster)
{
	for (auto monsterIterator : *monster)
	{
		if (typeid(*monsterIterator) == typeid(Slime))
		{
			ReadFileString("slime", "head", "GameInfo\\slime.ini");	//머리
			slimeShape["head"] = loadData;

			ReadFileString("slime", "body", "GameInfo\\slime.ini");	//몸
			slimeShape["body"] = loadData;

			ReadFileString("slime", "legs", "GameInfo\\slime.ini");	//다리
			slimeShape["legs"] = loadData;
		}
		else if (typeid(*monsterIterator) == typeid(Oak))
		{
			ReadFileString("oak", "head", "GameInfo\\oak.ini");	//머리
			oakShape["head"] = loadData;

			ReadFileString("oak", "body", "GameInfo\\oak.ini");	//몸
			oakShape["body"] = loadData;

			ReadFileString("oak", "legs", "GameInfo\\oak.ini");	//다리
			oakShape["legs"] = loadData;
		}
		else if (typeid(*monsterIterator) == typeid(Tank))
		{
			ReadFileString("tank", "head", "GameInfo\\tank.ini");	//머리
			tankShape["head"] = loadData;

			ReadFileString("tank", "bodyR", "GameInfo\\tank.ini");	//몸오른쪽
			tankShape["body"] = loadData;

			ReadFileString("tank", "bodyL", "GameInfo\\tank.ini");	//몸왼쪽
			tankShape["bodyL"] = loadData;

			ReadFileString("tank", "legs", "GameInfo\\tank.ini");	//다리
			tankShape["legs"] = loadData;
		}
	}
}

void GameInfo::LoadMonsterStats(vector<Monster*>* monster)
{
	int monsterHp = 0;
	int monsterPower = 0;
	int monsterSpeed = 0;
	int monsterExp = 0;
	int itemDropPercentage = 0;

	for (auto monsterIterator : *monster)
	{
		if (typeid(*monsterIterator) == typeid(Slime))
		{
			monsterHp = ReadFileInt("slime", "hp", "gameinfo\\slime.ini");
			monsterPower = ReadFileInt("slime", "power", "gameinfo\\slime.ini");
			monsterSpeed = ReadFileInt("slime", "speed", "gameinfo\\slime.ini");
			monsterExp = ReadFileInt("slime", "exp", "gameinfo\\slime.ini");
			itemDropPercentage = ReadFileInt("slime", "itemDropPercentage", "gameinfo\\slime.ini");
			monsterIterator->SetStats(monsterHp, monsterPower, monsterSpeed);

			monsterInfomation["slimeExp"] = monsterExp;
			monsterInfomation["slimeItemDropPercentage"] = itemDropPercentage;
		}
		else if (typeid(*monsterIterator) == typeid(Oak))
		{
			monsterHp = ReadFileInt("oak", "hp", "gameinfo\\oak.ini");
			monsterPower = ReadFileInt("oak", "power", "gameinfo\\oak.ini");
			monsterSpeed = ReadFileInt("oak", "speed", "gameinfo\\oak.ini");
			monsterExp = ReadFileInt("oak", "exp", "gameinfo\\oak.ini");
			itemDropPercentage = ReadFileInt("oak", "itemDropPercentage", "gameinfo\\oak.ini");
			monsterIterator->SetStats(monsterHp, monsterPower, monsterSpeed);

			monsterInfomation["oakExp"] = monsterExp;
			monsterInfomation["oakItemDropPercentage"] = itemDropPercentage;
		}
		else if (typeid(*monsterIterator) == typeid(Tank))
		{
			monsterHp = ReadFileInt("tank", "hp", "gameinfo\\tank.ini");
			monsterPower = ReadFileInt("tank", "power", "gameinfo\\tank.ini");
			monsterSpeed = ReadFileInt("tank", "speed", "gameinfo\\tank.ini");
			monsterExp = ReadFileInt("tank", "exp", "gameinfo\\tank.ini");
			itemDropPercentage = ReadFileInt("tank", "itemDropPercentage", "gameinfo\\tank.ini");
			monsterIterator->SetStats(monsterHp, monsterPower, monsterSpeed);

			monsterInfomation["tankExp"] = monsterExp;
			monsterInfomation["tankItemDropPercentage"] = itemDropPercentage;
		}
	}
}

void GameInfo::LoadMonsterDefaultSettingValue(vector<Monster*>* monster)
{
	int monsterInvincibilityTime = 0;
	int bounceSize = 0;

	for (auto monsterIterator : *monster)
	{
		if (typeid(*monsterIterator) == typeid(Slime))
		{
			monsterInvincibilityTime = ReadFileInt("slime", "invincibilityTime", "gameinfo\\slime.ini");
			bounceSize = ReadFileInt("slime", "bounceSize", "gameinfo\\slime.ini");
			monsterIterator->Setting(monsterInvincibilityTime, bounceSize);
		}
		else if (typeid(*monsterIterator) == typeid(Oak))
		{
			monsterInvincibilityTime = ReadFileInt("oak", "invincibilityTime", "gameinfo\\oak.ini");
			bounceSize = ReadFileInt("oak", "bounceSize", "gameinfo\\oak.ini");
			monsterIterator->Setting(monsterInvincibilityTime, bounceSize);
		}
		else if (typeid(*monsterIterator) == typeid(Tank))
		{
			monsterInvincibilityTime = ReadFileInt("tank", "invincibilityTime", "gameinfo\\tank.ini");
			bounceSize = ReadFileInt("tank", "bounceSize", "gameinfo\\tank.ini");
			monsterIterator->Setting(monsterInvincibilityTime, bounceSize);
		}
	}
}

void GameInfo::WriteData(string tempSection, string tempKey, string tempValue, string tempPath)
{
	auto section = tempSection.c_str();
	auto key = tempKey.c_str();
	auto value = tempValue.c_str();
	auto path = tempPath.c_str();
	WritePrivateProfileString(section, key, value, path);
}