#pragma once

#include <memory>
#include <vector>


template<class T>
class MemBlock{
public:

    MemBlock(size_t N): size(N),next(0){
        auto p_ = std::malloc(size * sizeof(T));
        if(!p_){
            throw std::bad_alloc();
        }
        p = reinterpret_cast<T *> (p_);
    };

    T * allocate(std::size_t n){
      	if(next < size) return p + next++;
	    else return nullptr;
    };

    void deallocate(T * p, std::size_t n_){
        --next;
        if(!next) {
            std::free(p);
        }
    };

    bool isFull(){
        return next == size;
    };

private:

    size_t size;// размер блока
    T * p; //указатель на выделеную область памяти
    int next;
};


template <class T>
class MemManager{
public:
    MemManager(size_t n) : blockSize(n){
	MemBlock<T> temp(blockSize);
        blocks.push_back(temp);
        allocBlock = &blocks.back();
    };

    T * allocate(size_t n){
        T* res = allocBlock->allocate(n);
        if(res != nullptr) return res;
        else {
            for(auto i : blocks){
                if(!i.isFull()){
                    allocBlock = &i;
                    return allocBlock->allocate(n);
                }
            }
            blocks.push_back(MemBlock<T>(blockSize));
            allocBlock = &blocks.back();
            return allocBlock->allocate(n);
        }
    };

    void deallocate(T * p, std::size_t n){
	    allocBlock->deallocate(p, n);
    }

private:
    std::vector<MemBlock<T>> blocks;
    MemBlock<T> * allocBlock;
    size_t blockSize;
};
