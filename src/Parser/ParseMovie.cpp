#include "ParseMovie.h"
#include "GameUtils.h"
#include <iostream>
#include "Movie2.h"
#include "ParseAction.h"
#include "Utils/ParseUtils.h"

namespace Parser
{
	using namespace rapidjson;

	void parseMovie(Game& game, const Value& elem)
	{
		if (isValidString(elem, "file") == false)
		{
			return;
		}

		std::string file(elem["file"].GetString());
		std::string id;

		if (isValidString(elem, "id") == true)
		{
			id = elem["id"].GetString();
		}
		else if (getIdFromFile(file, id) == false)
		{
			return;
		}
		if (isValidId(id) == false)
		{
			return;
		}

		std::shared_ptr<Action> action;
		if (elem.HasMember("onComplete"))
		{
			action = parseAction(game, elem["onComplete"]);
		}
		auto movie = std::make_shared<Movie2>(file);
		if (movie->load() == false)
		{
			if (action != nullptr)
			{
				game.Events().addBack(action);
			}
			return;
		}
		else
		{
			if (action != nullptr)
			{
				movie->setAction(str2int16("complete"), action);
			}
		}

		auto anchor = getAnchorKey(elem, "anchor");
		movie->setAnchor(anchor);
		auto size = getVector2fKey<sf::Vector2f>(elem, "size", movie->Size());
		auto pos = getPositionKey(elem, "position", size, game.RefSize());
		if (getBoolKey(elem, "relativeCoords", true) == true)
		{
			GameUtils::setAnchorPosSize(anchor, pos, size, game.RefSize(), game.MinSize());
			if (game.StretchToFit() == false)
			{
				GameUtils::setAnchorPosSize(anchor, pos, size, game.MinSize(), game.WindowSize());
			}
		}
		movie->Position(pos);
		movie->Size(size);

		auto volume = getVariableKey(elem, "volume");
		auto vol = game.getVarOrProp<int64_t, unsigned>(volume, game.MusicVolume());
		if (vol > 100)
		{
			vol = 100;
		}
		movie->setVolume((float)vol);

		movie->Visible(getBoolKey(elem, "visible", true));

		if (isValidString(elem, "resource") == true)
		{
			game.Resources().addDrawable(elem["resource"].GetString(), id, movie);
		}
		else
		{
			game.Resources().addDrawable(id, movie);
		}

		try
		{
			movie->play();
		}
		catch (std::exception ex)
		{
			std::cerr << ex.what();
		}
	}
}
