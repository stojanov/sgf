#pragma once

#include <vector>
#include <tuple>
#include <unordered_map>
#include <memory>

#include "System/Log.h"
#include "System/Debug.h"
#include "System/AsyncTask.h"
#include "Namespace.h"

using std::string;
using std::tuple;
using std::vector;
using std::shared_ptr;
using std::unordered_map;

SGF_NAMESPACE(::Core)

using UnloadedAsset = tuple<string, string>;
using UnloadedAssetContainer = vector<UnloadedAsset>;
	
template<typename T>
class AssetManager
{
#define IASSETLOG Log(INFO, "AssetManager")
#define EASSETLOG Log(ERROR, "AssetManager")
#define DASSETLOG Log(DEBUG, "AssetManager")
public:
	AssetManager() = default;
	~AssetManager() = default;

	void Add(const string& name, const string& filepath)
	{
		IASSETLOG << "ASSET: " << name << '/' << filepath;
		m_Unloaded.push_back(std::make_tuple(name, filepath));
	}

	shared_ptr<T> Get(const string& name) const
	{
		const auto i = m_Assets.find(name);

		if (i == m_Assets.end())
		{
			EASSETLOG << "Can't find asset -" << name;
			TRACE("Can't find asset");
			return nullptr;
		}

		return i->second;
	}

	void SyncLoad()
	{
		_load();
	}

	void AsyncLoad()
	{
		m_Loader.StartWork();
	}

	const float LoadProgress() const
	{
		return (float) m_LoadedCount / m_Unloaded.size();
	}

	const bool FinishedLoading() const
	{
		return m_Loader.IsDone();
	}

	// some resources may live even after the purge
	// std::shared_ptr will keep them alive
	void Destroy()
	{
		m_LoadedCount = 0;
		m_Assets.clear();
		m_Unloaded.clear();
	}

private:
	string m_Name;
	UnloadedAssetContainer m_Unloaded;
	unordered_map<string, shared_ptr<T>> m_Assets;
	System::AsyncTask m_Loader{ std::bind(&AssetManager::_load, this) };
	int m_LoadedCount{ 0 };

	void _load()
	{
		IASSETLOG << "STARTED LOAD ASSET JOB: ";
		for (const auto& asset : m_Unloaded)
		{
			const string name = std::get<0>(asset);
			const string filepath = std::get<1>(asset);

			if (_exists(name))
			{
				DASSETLOG << "ALREADY LOADED: " << name << "/" << filepath;
				continue;
			}

			auto pShared = std::make_shared<T>();

			DASSETLOG << "LOADING: "<< name << "/" << filepath;
			ASSERT(pShared->loadFromFile(filepath));
			DASSETLOG << "LOADED: " << name << "/" << filepath;

			m_Assets.emplace(name, pShared);
			m_LoadedCount++;
		}

		IASSETLOG << "FINISHED LOADING: " << m_Name;
		DASSETLOG << "TOTAL ASSETS: " << m_Unloaded.size();
		DASSETLOG << "LOADED ASSETS: " << m_LoadedCount;
	}

	const bool _exists(const std::string& name) const
	{
		return m_Assets.find(name) != m_Assets.end();
	}
};

END_NAMESPACE