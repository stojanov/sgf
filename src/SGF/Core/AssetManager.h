#pragma once

#include <vector>
#include <tuple>
#include <unordered_map>
#include <memory>
#include <future>

#include "System/Log.h"
#include "System/Debug.h"
#include "Namespace.h"

using std::string;
using std::pair;
using std::vector;
using std::shared_ptr;
using std::unordered_map;
using std::function;
using std::future;

SGF_NAMESPACE(::Core)

template<typename T>
using LoadedAsset = pair<shared_ptr<T>, bool>;
template<typename T>
using LoadFunction = function<LoadedAsset<T>(const std::string & filepath)>;

template<typename T>
class AssetManager
{
#define IASSETLOG Log(INFO, "AssetManager")
#define EASSETLOG Log(ERROR, "AssetManager")
#define DASSETLOG Log(DEBUG, "AssetManager")

using UnloadedAsset = pair<string, string>;
public:
	AssetManager(const std::string& name, LoadFunction<T> f)
		:
		m_Name(name),
		m_LoadFunction(f)
	{}
	
	~AssetManager() = default;

	void Queue(const string& name, const string& filepath)
	{
		IASSETLOG << "ASSET: " << name << '/' << filepath;
		m_Unloaded.push_back(std::make_pair(name, filepath));
	}

	shared_ptr<T> Get(const string& name) const
	{		
		if (auto entry = m_Assets.find(name); entry != m_Assets.end())
			return entry->second;
			
		EASSETLOG << "Can't find asset: " << name;
		TRACE("Can't find asset");
		return nullptr;
	}
	
	unsigned UnloadedAssetsCount() const
	{
		return m_Unloaded.size();
	}

	unsigned LoadedAssetCount() const
	{
		return m_Assets.size();
	}

	const float LoadProgress() const
	{
		return m_Assets.size() * 1.f / m_Unloaded.size();
	}
	// Loading will automatically clear the unloaded assets container	
	future<bool> Load()
	{
		return std::async(std::launch::async, std::bind(&AssetManager::_load, this));
	}
	// some resources may live even after the purge
	// std::shared_ptr will keep them alive
	void ClearLoaded() { m_Assets.clear(); }
	void ClearUnloaded() { m_Unloaded.clear(); }
	void Clear()
	{
		m_Assets.clear();
		m_Unloaded.clear();
	}
private:
	string m_Name;
	LoadFunction<T> m_LoadFunction;
	vector<UnloadedAsset> m_Unloaded;
	unordered_map<string, shared_ptr<T>> m_Assets;
	
	bool _load()
	{
		IASSETLOG << "--------STARTED LOAD ASSET JOB--------";
		for (const auto& [name, filepath] : m_Unloaded)
		{
			if (auto entry = m_Assets.find(name); entry == m_Assets.end())
			{				
				if (auto [assetPtr, isLoaded] = m_LoadFunction(filepath); isLoaded)
				{
					m_Assets.emplace(name, assetPtr);
				}
				else
				{
					EASSETLOG << "ERROR LOADING: " << name << "/" << filepath;
					return false;
				}
			}
			else
			{
				DASSETLOG << "ALREADY LOADED: " << name << "/" << filepath;
			}
		}

		IASSETLOG << "FINISHED LOADED ASSETS: " << m_Name;
		DASSETLOG << "TOTAL ASSETS: " << m_Unloaded.size();
		DASSETLOG << "LOADED ASSETS: " << m_Assets.size();

		m_Unloaded.clear();
		return true;
	}
};

END_NAMESPACE