#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

#include "SpatialHashList.h"

using std::string;
using std::unordered_map;
using std::tuple;

SGF_NAMESPACE(::Tools::SpatialHash)
/*
 * TODO: Create a custom hash function instead of relying on std::string
 */
using CollidableList = std::list<Collidable*>;

struct SpatialHashObject
{
	ListNode* nodePtr;
	std::string block;
};
	
class Map
{
	
enum MapObjectIndex
{
	NodeIdx,
	StrIdx
};
	
using MapObject = tuple<ListNode*, string>;
using BlockMap = unordered_map<std::string, List>;
using ObjectMap = unordered_map<int, std::vector<MapObject>>;
	
public:
	Map(uint8_t size);
	~Map();

	void RegisterObject(Collidable& obj);
	void UpdateObject(Collidable& obj);
	bool RemoveObject(Collidable& obj);

	CollidableList GetRect(sf::Vector2i& pos);
	CollidableList GetRect(Collidable& obj);
	CollidableList GetRect(sf::FloatRect& box);

	void ClearBlocks();
	void Clear();

	unsigned int size() const { return m_Blocks.size(); }

private:
	uint8_t m_BlockSize{ 6 }; // Size of the blocks, power of two
	BlockMap m_Blocks;
	ObjectMap m_Objects;
#ifdef SHOULD_SYNC_SPATIAL
	std::mutex m_Lock;
#endif

	auto _insertIntoBlock(std::string& key, Collidable* obj)
	{
		List* list;

		#ifdef SHOULD_SYNC_SPATIAL
		std::lock_guard<std::mutex> lck(m_Lock);
		#endif
		if (m_Blocks.count(key) == 0)
		{
			auto [iterator, err] = m_Blocks.emplace(key, List());
			list = &iterator->second;
		}
		else
		{
			list = &m_Blocks.at(key);
		}
		list->Push(obj);
		return list->getLast();
	}

	void _registerObject(const int& ID, std::string& blockKey, ListNode* ptr)
	{
		std::vector<MapObject>* vec;
#ifdef SHOULD_SYNC_SPATIAL
		std::lock_guard<std::mutex> lck(m_Lock);
#endif
		if (m_Objects.count(ID) == 0)
		{
			auto [ iterator, err ] = m_Objects.emplace(ID, std::vector<MapObject>());
			vec = &iterator->second;
		}
		else
		{
			vec = &m_Objects.at(ID);
		}

		vec->push_back(std::make_tuple(ptr, std::move(blockKey)));
	}

	const unsigned int _getBlock(const unsigned int x) const
	{
		return x >> m_BlockSize;
	}

	static std::string _getKey(const int x, const int y)
	{
		return std::to_string(x) + ":" + std::to_string(y);
	}
};

END_NAMESPACE
