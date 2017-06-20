#pragma once

namespace raven
{
	namespace core
	{
		class FreeList
		{
		public:
			FreeList();
			FreeList(void* memory, void* memoryEnd, size_t elementSize);

			void* GetSlot(void);
			void ReturnSlot(void* slot);

			bool IsEmpty(void) const { return !m_nextSlot; }

		private:
			FreeList* m_nextSlot;
		};
	}
}