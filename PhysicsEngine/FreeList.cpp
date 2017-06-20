#include "FreeList.h"
#include <cstddef>

using namespace raven;

core::FreeList::FreeList()
	: m_nextSlot(nullptr)
{}


core::FreeList::FreeList(void* memory, void* memoryEnd, size_t elementSize)
{
	ptrdiff_t memblock_length = static_cast<char*>(memoryEnd) - static_cast<char*>(memory);
	/// Calculate how many elements of element_size fit into the block
	/// to setup that many
	size_t element_count = memblock_length / elementSize;

	m_nextSlot = static_cast<FreeList*>(memory);
	memory = static_cast<char*>(memory) + elementSize;

	FreeList* current = m_nextSlot;
	for (size_t i = 0; i < element_count - 1; ++i)
	{
		current->m_nextSlot = static_cast<FreeList*>(memory);
		current = current->m_nextSlot;
		memory = static_cast<char*>(memory) + elementSize;
	}
	current->m_nextSlot = nullptr;
}


void* core::FreeList::GetSlot()
{
	if (!m_nextSlot) {
		return nullptr;
	}

	FreeList* slot = m_nextSlot;
	m_nextSlot = slot->m_nextSlot;
	return slot;
}


void core::FreeList::ReturnSlot(void* slot)
{
	FreeList* new_slot = static_cast<FreeList*>(slot);
	new_slot->m_nextSlot = m_nextSlot;
	m_nextSlot = new_slot;
}
