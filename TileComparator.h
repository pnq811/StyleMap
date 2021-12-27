#pragma once
#ifndef _TILE_COMPARATOR_H_
#define _TILE_COMPARATOR_H_
class TileComparator
{
public:
	struct Key
	{
	public:
		bool operator ==(const Key key)
		{
			return level == key.level && tileX == key.tileX && tileY == key.tileY;
		}
	public:
		int level;
		int tileX;
		int tileY;
	};
public: 
	bool operator() (const Key& key1, const Key& key2) const
	{
		if (key1.level < key2.level)
			return true;
		else
		{
			if (key1.level == key2.level)
			{
				if (key1.tileX < key2.tileX)
					return true;
				else
				{
					if (key1.tileX == key2.tileX)
					{
						if (key1.tileY < key2.tileY)
							return true;
					}
				}
			}
		}
		return false;
	}
};
#endif
