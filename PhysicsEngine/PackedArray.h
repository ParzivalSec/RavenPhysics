#pragma once

#include "FreeList.h"
#include <cassert>
#include <cstring>
#include <cstdint>
#include <new>

namespace raven
{
	namespace core
	{
		typedef uint32_t ResourceID;

		namespace
		{
			struct HandleData
			{
				uintptr_t resourceIndex;
				uint16_t chunkIndex;
				uint16_t generation;
			};

			union ResourceIDInternal
			{
				ResourceID as_ResourceID;
				struct
				{
					uint16_t sparseArrayIndex;
					uint16_t generation;
				} as_partionedID;
			};

		}

		template <class T, uint32_t maxObjectCount>
		class PackedArray
		{
		public:

			PackedArray();

			ResourceID Add();
			void Remove(ResourceID id);
			T* Lookup(ResourceID id);

			T& operator[](size_t idx);
			T operator[](size_t idx) const;

			uint32_t Size(void) const;

		private:
			FreeList m_freeList;
			HandleData m_sparse[maxObjectCount];
			uint16_t m_idLookup[maxObjectCount];

			// Data that holds the real data stored in the array
			T m_resourceObjects[maxObjectCount];
			uint32_t m_objectCount;
		};

		template <class T, uint32_t maxObjectCount>
		PackedArray<T, maxObjectCount>::PackedArray()
			: m_objectCount(0)
		{
			for (size_t i = 0; i < maxObjectCount; i++)
			{
				m_sparse[i].chunkIndex = static_cast<uint16_t>(i);
			}

			assert(sizeof(void*) <= sizeof(uintptr_t));
			m_freeList.~FreeList();
			new (&m_freeList) FreeList(m_sparse, m_sparse + maxObjectCount, sizeof(HandleData));
		}

		template <class T, uint32_t maxObjectCount>
		ResourceID PackedArray<T, maxObjectCount>::Add()
		{
			assert(m_objectCount < maxObjectCount);

			union
			{
				void* as_void;
				HandleData* as_handleDataPtr;
			};

			as_void = m_freeList.GetSlot();

			ResourceIDInternal newInternalID;
			newInternalID.as_partionedID.sparseArrayIndex = as_handleDataPtr->chunkIndex;
			newInternalID.as_partionedID.generation = as_handleDataPtr->generation;

			as_handleDataPtr->resourceIndex = m_objectCount;
			new (&m_resourceObjects[m_objectCount]) T();
			m_idLookup[m_objectCount++] = newInternalID.as_partionedID.sparseArrayIndex;

			return newInternalID.as_ResourceID;
		}

		template <class T, uint32_t maxObjectCount>
		void PackedArray<T, maxObjectCount>::Remove(ResourceID id)
		{
			ResourceIDInternal internalID { id };

			assert(internalID.as_partionedID.sparseArrayIndex < maxObjectCount);
			HandleData* handleData = &m_sparse[internalID.as_partionedID.sparseArrayIndex];
			if (handleData->generation != internalID.as_partionedID.generation)
			{
				return;
			}

			memcpy(&m_resourceObjects[handleData->resourceIndex], &m_resourceObjects[--m_objectCount], sizeof(T));

			uint32_t toSwapSparseIndex = m_idLookup[m_objectCount];
			m_sparse[toSwapSparseIndex].resourceIndex = handleData->resourceIndex;
			m_idLookup[handleData->resourceIndex] = toSwapSparseIndex;

			m_freeList.ReturnSlot(&m_sparse[internalID.as_partionedID.sparseArrayIndex]);

			++handleData->generation;
		}

		template <class T, uint32_t maxObjectCount>
		T* PackedArray<T, maxObjectCount>::Lookup(ResourceID id)
		{
			ResourceIDInternal internalID { id };
			assert(internalID.as_partionedID.sparseArrayIndex < maxObjectCount);

			HandleData handleData = m_sparse[internalID.as_partionedID.sparseArrayIndex];
			if (handleData.generation != internalID.as_partionedID.generation)
			{
				return nullptr;
			}

			return &m_resourceObjects[handleData.resourceIndex];
		}

		/**
		 * Be causious the data may be invalidate while iterating
		 */
		template <class T, uint32_t maxObjectCount>
		T& PackedArray<T, maxObjectCount>::operator[](size_t idx)
		{
			return m_resourceObjects[idx];
		}

		template <class T, uint32_t maxObjectCount>
		T PackedArray<T, maxObjectCount>::operator[](size_t idx) const
		{
			return m_resourceObjects[idx];
		}

		template <class T, uint32_t maxObjectCount>
		uint32_t PackedArray<T, maxObjectCount>::Size() const
		{
			return m_objectCount;
		}
	}
}
