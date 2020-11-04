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

map<string, string> GameInfo::GetShape(const int character)
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


	default:
		return playerShape;
	}
}

string GameInfo::GetItemShape(string itemName, int option)
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
	ReadFileString("itembox", "head", "GameInfo\\itemBox.ini");
	itemBoxShape["head"] = loadData;

	ReadFileString("itembox", "body", "GameInfo\\itemBox.ini");
	itemBoxShape["body"] = loadData;

	ReadFileString("itembox", "legs", "GameInfo\\itemBox.ini");
	itemBoxShape["legs"] = loadData;
}

void GameInfo::LoadSaveData(int dataNumber)
{
	switch (dataNumber)
	{
	case 1:
		LoadPlayerStats(dataNumber);
		break;
	case 2:
		LoadPlayerStats(dataNumber);
		break;
	default:
		LoadPlayerStats(dataNumber);
		break;	//새게임
	}
}

void GameInfo::LoadPlayerStats(int dataNumber)
{
	int hp = 0;
	int power = 0;

	switch (dataNumber)
	{
	case 1:
		hp = ReadFileInt("player", "hp", "GameInfo\\player.ini");//섹션수정
		power = ReadFileInt("player", "power", "GameInfo\\player.ini");//섹션수정
		break;
	case 2:
		hp = ReadFileInt("player", "hp", "GameInfo\\player.ini");	//섹션수정
		power = ReadFileInt("player", "power", "GameInfo\\player.ini");//섹션수정
		break;
	default:
		hp = ReadFileInt("player", "hp", "GameInfo\\player.ini");
		power = ReadFileInt("player", "power", "GameInfo\\player.ini");
		break;
	}
	player->SetStats(hp, power);
}

void GameInfo::LoadPlayerShape(int dataNumber)
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

void GameInfo::LoadSlimeShape()
{
	ReadFileString("slime", "head", "GameInfo\\slime.ini");	//머리
	slimeShape["head"] = loadData;

	ReadFileString("slime", "body", "GameInfo\\slime.ini");	//몸
	slimeShape["body"] = loadData;

	ReadFileString("slime", "legs", "GameInfo\\slime.ini");	//다리
	slimeShape["legs"] = loadData;
}

void GameInfo::LoadSlimeStats()
{
	slime = Slime::GetInstance();

	if (slime != nullptr)
	{
		for (int i = 0; i < slime->size(); i++)		//슬라임객체에 체력과 공격력과 속도넣기
			(*slime)[i]->SetStats(ReadFileInt("slime", "hp", "gameinfo\\slime.ini"), ReadFileInt("slime", "power", "gameinfo\\slime.ini"), ReadFileInt("slime", "speed", "gameinfo\\slime.ini") - i * 200);
	}
}

void GameInfo::LoadSlimeDefaultSettingValue()
{
	slime = Slime::GetInstance();

	if (slime != nullptr)
	{
		for (int i = 0; i < slime->size(); i++)		//슬라임객체에 무적시간, 넉백거리넣기
			(*slime)[i]->Setting(ReadFileInt("slime", "invincibilityTime", "gameinfo\\slime.ini"), ReadFileInt("slime", "bounceSize", "gameinfo\\slime.ini"));
	}
}

void GameInfo::LoadOakStats()
{
	oak = Oak::GetInstance();

	if (oak != nullptr)
	{
		for (int i = 0; i < oak->size(); i++)		//오크객체에 체력과 공격력과 속도넣기
			(*oak)[i]->SetStats(ReadFileInt("oak", "hp", "gameinfo\\oak.ini"), ReadFileInt("oak", "power", "gameinfo\\oak.ini"), ReadFileInt("oak", "speed", "gameinfo\\oak.ini") - i * 200);
	}
}

void GameInfo::LoadOakShape()
{
	ReadFileString("oak", "head", "GameInfo\\oak.ini");	//머리
	oakShape["head"] = loadData;

	ReadFileString("oak", "body", "GameInfo\\oak.ini");	//몸
	oakShape["body"] = loadData;

	ReadFileString("oak", "legs", "GameInfo\\oak.ini");	//다리
	oakShape["legs"] = loadData;
}

void GameInfo::LoadTankStats()
{
	tank = Tank::GetInstance();

	if (tank != nullptr)
	{
		for (int i = 0; i < tank->size(); i++)		//탱크객체에 체력과 공격력과 속도넣기
			(*tank)[i]->SetStats(ReadFileInt("tank", "hp", "gameinfo\\tank.ini"), ReadFileInt("tank", "power", "gameinfo\\tank.ini"), ReadFileInt("tank", "speed", "gameinfo\\tank.ini"));
	}
}

void GameInfo::LoadTankShape()
{
	ReadFileString("tank", "head", "GameInfo\\tank.ini");	//머리
	tankShape["head"] = loadData;

	ReadFileString("tank", "bodyR", "GameInfo\\tank.ini");	//몸오른쪽
	tankShape["bodyR"] = loadData;

	ReadFileString("tank", "bodyL", "GameInfo\\tank.ini");	//몸왼쪽
	tankShape["bodyL"] = loadData;

	ReadFileString("tank", "legs", "GameInfo\\tank.ini");	//다리
	tankShape["legs"] = loadData;
}

void GameInfo::WriteData(string tempSection, string tempKey, string tempValue, string tempPath)
{
	auto section = tempSection.c_str();
	auto key = tempKey.c_str();
	auto value = tempValue.c_str();
	auto path = tempPath.c_str();
	WritePrivateProfileString(section, key, value, path);
}