//Copyright (c) 2011 Oscar (.teri) Triano <teritriano@gmail.com>

//This software is provided 'as-is', without any express or implied
//warranty. In no event will the authors be held liable for any damages
//arising from the use of this software.

//Permission is granted to anyone to use this software for any purpose,
//including commercial applications, and to alter it and redistribute it
//freely, subject to the following restrictions:

//1. The origin of this software must not be misrepresented; you must not
//claim that you wrote the original software. If you use this software
//in a product, an acknowledgment in the product documentation would be
//appreciated but is not required.

//2. Altered source versions must be plainly marked as such, and must not be
//misrepresented as being the original software.

//3. This notice may not be removed or altered from any source
//distribution.

#pragma once

#include <physfs.h>
#include <SFML/System.hpp>
#include <string>

namespace sf
{
	class PhysFSStream : public sf::InputStream, public sf::NonCopyable
	{
	private:
		PHYSFS_File* file;

	public:
		PhysFSStream(const std::string& fileName) : PhysFSStream(fileName.c_str()) {}
		PhysFSStream(const char* fileName);
		virtual ~PhysFSStream();

		virtual sf::Int64 read(void* data, sf::Int64 size) noexcept;
		virtual sf::Int64 seek(sf::Int64 position) noexcept;
		virtual sf::Int64 tell() noexcept;
		virtual sf::Int64 getSize() noexcept;

		bool hasError() const noexcept { return file == NULL; }

		const char* getLastError() const noexcept
		{
#if (PHYSFS_VER_MAJOR > 2 || (PHYSFS_VER_MAJOR == 2 && PHYSFS_VER_MINOR >= 1))
			return PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode());
#else
			return PHYSFS_getLastError();
#endif
		}
	};
}
