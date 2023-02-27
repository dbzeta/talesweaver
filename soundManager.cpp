#include "StdAfx.h"
#include "soundManager.h"

soundManager::soundManager(void)
	:_system(NULL),
	_channel(NULL),
	_sound(NULL)
{
}

soundManager::~soundManager(void)
{
}

HRESULT soundManager::init(void)
{
	//���� �ý��� ����
	System_Create(&_system);

	//ä�μ� ���� �� �ʱ�ȭ
	_system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, 0);

	//ä�ΰ� ���带 �����Ҵ�...
	//�޸� ���� �� ���� ����...
	_sound = new Sound*[TOTAL_SOUND_CHANNEL];
	_channel = new Channel*[TOTAL_SOUND_CHANNEL];

	//�ʱ�ȭ
	memset(_sound, 0, sizeof(Sound*)* (TOTAL_SOUND_CHANNEL));
	memset(_channel, 0, sizeof(Channel*)* (TOTAL_SOUND_CHANNEL));

	return S_OK;
}

void soundManager::release(void)
{
	//���� ����
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTAL_SOUND_CHANNEL; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != NULL)
			{
				if (_sound != NULL) _sound[i]->release();
			}
		}
	}

	//�޸� �����
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	//�ý��� �ݱ� 
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

//���� �߰�
void soundManager::addSound(string keyName, string soundName, bool background, bool loop)
{
	//�����뷡��?
	if (loop)
	{
		//������̳�?
		if (background)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	//���� �ƴϴ�
	else
	{
		//�ѹ��� �÷���~~
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}

	//�ʿ� ���带 Ű���� �Բ� �־��ش�
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));

}

//���� �÷���
void soundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷���~~~
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			//���� ����
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

//���� ����
void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	Sound* currentSound = NULL;

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter)
	{
		if (keyName == iter->first)
		{
			// ���带 �����Դ�.
			while (true)
			{
				_channel[count]->getCurrentSound(&currentSound);
				if (count > 1000) return;
				if (currentSound != *iter->second) count++;
				else 
				{
					_channel[count]->stop();
					break;
				}
			}
		}
	}
}

//���� �Ͻ�����
void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	Sound* currentSound = NULL;
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// ���带 �����Դ�.
			while (true)
			{
				_channel[count]->getCurrentSound(&currentSound);
				if (currentSound != *iter->second) count++;
				else
				{
					_channel[count]->setPaused(true);
					break;
				}
			}
		}
	}
}

//���� �����
void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	Sound* currentSound = NULL;
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		// ���带 �����Դ�.
		while (true)
		{
			_channel[count]->getCurrentSound(&currentSound);
			if (currentSound != *iter->second) count++;
			else
			{
				_channel[count]->setPaused(false);
				break;
			}
		}
	}
}

//�Ͻ����� �Ǿ���?
bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();

	Sound* currentSound = NULL;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{	
			// ���带 �����Դ�.
			while (true)
			{
				_channel[count]->getCurrentSound(&currentSound);
				if (currentSound != *iter->second) count++;
				else
				{
					_channel[count]->getPaused(&isPause);
					break;
				}
			}
		}
	}
	return isPause;
}

//�÷��� ���̳�?
bool soundManager::isPlaySound(string keyName)
{
	bool isPlay = 0;
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();

	Sound* currentSound = NULL;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// ���带 �����Դ�.
			while (true)
			{
				_channel[count]->getCurrentSound(&currentSound);
				if (count > 1000) return false;
				if (currentSound != *iter->second) count++;
				else
				{
					_channel[count]->isPlaying(&isPlay);
					break;
				}
			}
		}
	}
	return isPlay;
}

//Fmod �ý����� ����
void soundManager::update(void)
{
	//���� System ��������� ������Ʈ
	_system->update();

	//������ �ٲ�ų� 
	//����� ���� ���带 ä�ο��� �����µ��� �پ���
	//�۾��� �ڵ����� ���ش�

}

void soundManager::changeBgm(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (isPlaySound(iter->first))
		{
			this->stop(iter->first);
		}
	}

	count = 0;
	for (iter = _mTotalSounds.begin(); iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷���~~~
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			//���� ����
			_channel[count]->setVolume(volume);
			break;
		}
	}
}
