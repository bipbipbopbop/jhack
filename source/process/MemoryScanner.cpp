//windows.h sucks
#define NOMINMAX

#include <limits>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <iterator>
#include "MemoryScanner.hpp"

namespace jhack
{
	namespace
	{
		// credit to Aixxe from https://aixxe.net/2016/10/osu-game-hacking and atom0s from http://atom0s.com/forums/viewtopic.php?f=5&t=4
		// works for 32bit processes
		LPVOID		findPattern(HANDLE processHandle, const BYTE *_pattern, const char *mask, const size_t begin) {
			constexpr size_t						readSize = 4096;
			size_t									maskSize{};
			std::vector<std::pair<BYTE, bool>>	pattern;

			for (maskSize = 0; mask[maskSize]; ++maskSize)
				pattern.push_back(std::make_pair(_pattern[maskSize], mask[maskSize] != '?'));

			for (size_t i = begin; i < std::numeric_limits<uint32_t>::max(); i += readSize - maskSize)
			{
				BYTE			chunk[readSize]{};

				if (!ReadProcessMemory(processHandle, (LPCVOID)i, &chunk, readSize, NULL))
					return NULL;
				auto			result = std::search(
					std::begin(chunk), std::end(chunk),
					std::begin(pattern), std::end(pattern),
					[](BYTE a, std::pair<BYTE, bool> b){
						return b.second ? a == b.first : true;
					});

				if (result != std::end(chunk))
					return result;
			}

			return NULL;
		}
	}

	MemoryScanner::MemoryScanner(HANDLE _processHandle, const BYTE *_pattern, const char *_mask)
		: processHandle(_processHandle), pattern(_pattern), mask(_mask)
	{}

	MemoryScanner::iterator	MemoryScanner::scan()
	{
		if (this->_hasScanned)
			return this->begin();

		LPVOID	result = (LPVOID)~NULL;
		while (result != NULL)
		{
			result = findPattern(this->processHandle, this->pattern, this->mask, this->_internalOffset);
			this->_result.push_back(result);
			this->_internalOffset = (size_t)result + 1;
		}
		this->_hasScanned = true;
		return this->begin();
	}

	LPVOID							MemoryScanner::scanNext()
	{
		if (this->_hasScanned)
			return NULL;

		auto	result = findPattern(this->processHandle, this->pattern, this->mask, this->_internalOffset);
		if (result == NULL)
			this->_hasScanned = true;
		else
		{
			this->_result.push_back(result);
			this->_internalOffset = (size_t)result + 1;
		}
		return result;
	}

	bool							MemoryScanner::hasScanned() const
	{
		return this->_hasScanned;
	}

	void							MemoryScanner::clear()
	{
		this->_internalOffset = 0;
		this->_hasScanned = false;
		this->_result.clear();
	}

	void							MemoryScanner::setBeginOffset(size_t offset)
	{
		this->clear();
		this->_internalOffset = offset;
	}

	MemoryScanner::iterator			MemoryScanner::begin()
	{
		return MemoryScanner::iterator(this->_result.begin(), *this);
	}

	MemoryScanner::const_iterator	MemoryScanner::begin() const
	{
		return this->_result.begin();
	}

	MemoryScanner::iterator			MemoryScanner::end()
	{
		return MemoryScanner::iterator(this->_result.end(), *this);
	}

	MemoryScanner::const_iterator	MemoryScanner::end() const
	{
		return this->_result.end();
	}

}
