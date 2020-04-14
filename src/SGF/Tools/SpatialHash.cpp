#include "SpatialHash.h"
#include "System/Debug.h"
#include "System/Log.h"
#include "Components/Collidable.h"

SGF_NAMESPACE(::Tools::SpatialHash)

Map::Map(uint8_t size = 6)
	: m_BlockSize(size)
{}

Map::~Map() = default;

void Map::RegisterObject(Collidable& obj)
{
	const auto box = obj.getBoundingBox();

	const unsigned int kx = _getBlock(box.left);
	const unsigned int ky = _getBlock(box.top);

	unsigned int kw;
	unsigned int kh;

	if (box.width == 0 || box.height == 0)
	{
		kw = kx;
		kh = ky;
	}
	else
	{
		kw = _getBlock(box.left + box.width);
		kh = _getBlock(box.top + box.height);
	}

	for (unsigned int x = kx; x <= kw; x++)
	{
		for (unsigned int y = ky; y <= kh; y++)
		{
			auto blockKey = _getKey(x, y);

			auto ptr = _insertIntoBlock(blockKey, &obj);

			_registerObject(obj.getID(), blockKey, ptr);
		}
	}
}

void Map::UpdateObject(Collidable& obj)
{
	if (RemoveObject(obj))
	{
		RegisterObject(obj);
	}
}

bool Map::RemoveObject(Collidable& obj)
{
#ifdef SHOULD_SYNC_SPATIAL
	std::lock_guard<std::mutex> lck(m_Lock);
#endif
	const auto id = obj.getID();
	auto i = m_Objects.find(id);

	if (i == m_Objects.end()) return false;

	for (const auto& v : i->second)
	{
		m_Blocks.at(std::get<StrIdx>(v)).Remove(std::get<NodeIdx>(v));
	}

	m_Objects.erase(id);

	return true;
}

CollidableList Map::GetRect(sf::FloatRect& box)
{
	/*
	 * TODO: Refactor
	 * Trying to avoid dynamic allocation at runtime
	 * haven't really checked if this is better
	 */
	CollidableList list;

	const unsigned int dx = _getBlock(box.left);
	const unsigned int dy = _getBlock(box.top);

	const unsigned int dw = _getBlock(box.left + box.width);
	const unsigned int dh = _getBlock(box.top + box.height);
#ifdef SHOULD_SYNC_SPATIAL
	std::lock_guard<std::mutex> lck(m_Lock);
#endif
	for (unsigned int x = dx; x <= dw; x++) {
		for (unsigned int y = dy; y <= dh; y++) {
			auto i = m_Blocks.find(_getKey(x, y));

			if (i == m_Blocks.end())
			{
				ELOG << "Map: cannot find block at (" << x << ", " << y << ")";
				continue;
			}

			i->second.ForEach([&list](auto p)
			{
				list.push_back(p);
			});
		}
	}

	return list;
}

CollidableList Map::GetRect(sf::Vector2i& pos)
{
	CollidableList list;

	const unsigned int x = _getBlock(pos.x);
	const unsigned int y = _getBlock(pos.y);

#ifdef SHOULD_SYNC_SPATIAL
	std::lock_guard<std::mutex> lck(m_Lock);
#endif
	auto i = m_Blocks.find(_getKey(x, y));

	if (i == m_Blocks.end())
	{
		ELOG << "Map: cannot find block at (" << x << ", " << y << ")";
		TRACE("Error cannot find block");
	}

	i->second.ForEach([&list](auto p)
	{
		list.push_back(p);
	});

	return list;
}

CollidableList Map::GetRect(Collidable& obj)
{
	return GetRect(obj.getBoundingBox());
}

void Map::ClearBlocks()
{
	for (auto& i : m_Blocks)
	{
		i.second.Destroy();
	}
	m_Blocks.clear();
}

void Map::Clear()
{
	m_Objects.clear();
	ClearBlocks();
}

END_NAMESPACE
