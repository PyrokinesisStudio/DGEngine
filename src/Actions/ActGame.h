#pragma once

#include "Action.h"
#include "Game.h"

class ActGameClearPlayingSounds : public Action
{
public:
	virtual bool execute(Game& game) noexcept
	{
		game.Resources().clearPlayingSounds();
		return true;
	}
};

class ActGameClose : public Action
{
public:
	virtual bool execute(Game& game)
	{
		game.Window().close();
		return true;
	}
};

class ActGameEnableInput : public Action
{
private:
	bool enable;

public:
	ActGameEnableInput(bool enable_) noexcept : enable(enable_) {}

	virtual bool execute(Game& game) noexcept
	{
		game.EnableInput(enable);
		return true;
	}
};

class ActGamePauseOnFocusLoss : public Action
{
private:
	bool pause;

public:
	ActGamePauseOnFocusLoss(bool pause_) noexcept : pause(pause_) {}

	virtual bool execute(Game& game) noexcept
	{
		game.PauseOnFocusLoss(pause);
		return true;
	}
};

class ActGameSetMusicVolume : public Action
{
private:
	Variable volume;

public:
	ActGameSetMusicVolume(const Variable& volume_) noexcept : volume(volume_) {}

	virtual bool execute(Game& game)
	{
		auto vol = game.getVarOrProp<int64_t, unsigned>(volume, 100u);
		game.MusicVolume(vol);
		return true;
	}
};

class ActGameSetProperty : public Action
{
private:
	std::string prop;
	Variable value;
	sf::Vector2i propRange;
	sf::Vector2i valueRange;
	bool hasPropRange{ false };
	bool hasValueRange{ false };

public:
	ActGameSetProperty(const std::string& prop_, const Variable& value_)
		: prop(prop_), value(value_) {}

	void setPropRange(const sf::Vector2i& propRange_) noexcept
	{
		propRange = propRange_;
		hasPropRange = true;
	}
	void setValueRange(const sf::Vector2i& valueRange_) noexcept
	{
		valueRange = valueRange_;
		hasValueRange = true;
	}

	virtual bool execute(Game& game)
	{
		auto prop2 = game.getVarOrPropString(prop);
		auto value2 = game.getVarOrProp(value);
		if (std::holds_alternative<int64_t>(value2) == true)
		{
			if (hasPropRange == true &&
				hasValueRange == true)
			{
				auto val = std::get<int64_t>(value2);
				val = (int64_t)Utils::normalizeNumber<sf::Vector2i>((long)val, valueRange, propRange);
				value2.emplace<int64_t>(val);
			}
		}
		game.setProperty(prop2, value2);
		return true;
	}
};

class ActGameSetSoundVolume : public Action
{
private:
	Variable volume;

public:
	ActGameSetSoundVolume(const Variable& volume_) noexcept : volume(volume_) {}

	virtual bool execute(Game& game)
	{
		auto vol = game.getVarOrProp<int64_t, unsigned>(volume, 100u);
		game.SoundVolume(vol);
		return true;
	}
};
