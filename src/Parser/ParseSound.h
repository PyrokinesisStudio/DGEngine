#pragma once

#include "Game.h"
#include "Json/JsonParser.h"

namespace Parser
{
	sf::SoundBuffer* parseSoundObj(Game& game,
		const std::string& id, const std::string& file);
	void parseSound(Game& game, const rapidjson::Value& elem);
}
