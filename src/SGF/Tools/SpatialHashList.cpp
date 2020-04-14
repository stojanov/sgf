#include "SpatialHashList.h"

SGF_NAMESPACE(::Tools::SpatialHash)

List::List()
{
	m_Head = new ListNode{ nullptr, nullptr, nullptr };
}

List::~List()
{
	Destroy();
}

void List::Push(Collidable* data)
{
	auto newNode = new ListNode{ m_Head, nullptr, data };
#ifdef SHOULD_SYNC_SPATIAL
	lock_guard<mutex> lock(m_LOCK);
#endif
	m_Head->next = newNode;
	m_Head = newNode;
	m_Size++;
}

void List::Remove(ListNode* node)
{
#ifdef SHOULD_SYNC_SPATIAL
	lock_guard<mutex> lock(m_LOCK);
#endif

	if (m_Size == 0) { return; }
	
	if (node->next == nullptr)
	{
		m_Head = node->prev;
		m_Head->next = nullptr;
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	delete node;
	m_Size--;
}
	
void List::ForEach(std::function<void(Collidable*)> f) const
{
#ifdef SHOULD_SYNC_SPATIAL
	lock_guard<mutex> lock(m_LOCK);
#endif
	
	auto ptr = m_Head;
	while (ptr->prev != nullptr)
	{
		f(ptr->data);
		ptr = ptr->prev;
	}
}

void List::Destroy()
{
#ifdef SHOULD_SYNC_SPATIAL
	lock_guard<mutex> lock(m_LOCK);
#endif
	
	auto ptr = m_Head;
	while (ptr->prev != nullptr)
	{
		auto prev = ptr->prev;
		delete ptr;
		ptr = prev;
	}
}
	
END_NAMESPACE