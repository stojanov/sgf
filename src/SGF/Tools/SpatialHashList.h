#pragma once

#include <functional>

#include "Components/Collidable.h"

#include <mutex>

using std::mutex;
using std::lock_guard;

SGF_NAMESPACE(::Tools::SpatialHash)
// #define SHOULD_SYNC_SPATIAL
	
// Built to be used in SpatialHash
struct ListNode
{
	ListNode* prev;
	ListNode* next;
	Collidable* data;
};

// Custom LinkedList with limited functionality
class List
{
public:
	List();
	~List();

	void Push(Collidable* data);

	void Remove(ListNode* node);

	ListNode* getLast() const { return m_Head; }
	int Size() const { return m_Size; }
	
	void ForEach(std::function<void(Collidable*)> f) const;
	void Destroy();
private:
	ListNode* m_Head;
#ifdef SHOULD_SYNC_SPATIAL
	static mutex m_LOCK;
#endif
	int m_Size{ 0 }; 
};

END_NAMESPACE
