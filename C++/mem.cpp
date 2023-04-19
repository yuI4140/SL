#pragma once
#include <cstring>
#include <cstddef>
#include <memory>
constexpr size_t Gigabytes(size_t gb) { return gb * 1024 * 1024 * 1024; }
constexpr size_t Kilobytes(size_t kb) { return kb * 1024; }
class MemoryAllocator {
public:
    MemoryAllocator() = default;

    void* Allocate(size_t size) {
        void* ptr = heap_ + size;
        heap_size_ += size;
        return ptr;
    }

    void* AllocateBox(size_t size) {
        void* ptr = heap_ + size;
        heap_size_ += size;
        return new Box{ ptr, size };
    }

    void Free(void* ptr, size_t size) {
        std::memset(ptr, 0, size);
        heap_size_ -= size;
    }

    void* Reallocate(void* ptr, size_t old_size, size_t new_size) {
        if (new_size <= old_size) {
            return ptr;
        }

        void* new_ptr = Allocate(new_size);
        std::memcpy(new_ptr, ptr, old_size);
        Free(ptr, old_size);

        return new_ptr;
    }

    void* MoveToChunk(void* ptr) {
        for (size_t i = 0; i < heap_size_; ++i) {
            if (heap_ + i == ptr) {
                size_t size = 0;

                // Find the size of the chunk to move
                for (size_t j = i; j < heap_size_; ++j) {
                    if (heap_[j] == 0) {
                        size = j - i;
                        break;
                    }
                }

                if (size == 0) {
                    // The chunk extends to the end of the heap
                    size = heap_size_ - i;
                }

                // Move the chunk to the chunker
                Chunk* new_chunk = new Chunk{ chunker_ + size, size };
                std::memcpy(new_chunk->ptr, ptr, size);

                // Clear the original chunk in the heap
                std::memset(ptr, 0, size);

                // Update heap_size_
                heap_size_ -= size;

                return new_chunk->ptr;
            }
        }

        return nullptr;
    }

    void PassHeap() {
        std::memcpy(heap_, chunker_, chunker_size_);
        heap_size_ = chunker_size_;
        chunker_size_ = 0;
    }

    void BringDown() {
        std::memset(chunker_, 0, chunker_size_);
    }

private:
    char heap_[Gigabytes(1)]{};
    char chunker_[Kilobytes(7)]{};
    size_t chunker_size_{};
    size_t heap_size_{};

    struct Chunk {
        void* ptr{};
        size_t size{};
    };

    struct Box {
        void* ptr{};
        size_t size{};

        ~Box() {
            std::memset(ptr, 0, size);
            delete ptr;
        }
    };
};
