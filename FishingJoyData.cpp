#include "FishingJoyData.h"

USING_NS_CC;

#define IS_BEGINER "_isBeginer"
#define MUSIC "_music"
#define SOUND "_sound"
#define GOLD "_gold"

static FishingJoyData* _getInstance = NULL;

FishingJoyData::FishingJoyData(void)
{
}


FishingJoyData::~FishingJoyData(void)
{
	this->flush();
}

FishingJoyData* FishingJoyData::getInstance()
{
	if(NULL == _getInstance)
	{
		_getInstance = new FishingJoyData();
		_getInstance -> init();
	}
	return _getInstance;
}

bool FishingJoyData::init()
{
	_isBeginer = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_BEGINER, true);
	if (_isBeginer)
	{
		this -> reset();
	}
	else
	{
		CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
		this -> setGold(userDefault -> getIntegerForKey(GOLD));
		this -> setMusic(userDefault -> getBoolForKey(MUSIC, true));
		this -> setSound(userDefault -> getBoolForKey(SOUND, true));
	}
	return true;
}

void FishingJoyData::reset()
{
	this -> setMusic(true);
	this -> setSound(true);
	this -> setGold(200);
	this -> setIsBeginer(false);
	this -> flush();
}

void FishingJoyData::flush()
{
	CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
	
	userDefault -> setBoolForKey(IS_BEGINER, _isBeginer);
	userDefault -> setIntegerForKey(GOLD, _gold);
	userDefault -> getBoolForKey(MUSIC, _music);
	userDefault -> getBoolForKey(SOUND, _sound);

	userDefault -> flush();
}

void FishingJoyData::alterGold(int golds)
{
	int num = getGold();
	num += golds;
	this->setGold(num);
	flush();
}

void FishingJoyData::purge()
{
	CC_SAFE_RELEASE_NULL(_getInstance);
}
