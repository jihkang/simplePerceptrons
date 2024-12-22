#ifndef PARALLEL_HPP
#define PARALLEL_HPP

#include <thread>
#include <future>
#include <vector>
#include <functional>

template <typename TF>
void parallel_for0(unsigned int begin, unsigned int end, const TF& func)
{
    auto length = end - begin;
    if (length == 0) {
        return ;
    }

    // f worker 람다식을 통해 분배
    auto f = [&func](unsigned int bs, unsigned int be)
    {
        for (unsigned int i = bs; i < be; ++i)
            func(i);
    };

    unsigned int nthreads = std::thread::hardware_concurrency();
    auto const blockSize = length / nthreads;
    std::vector<std::future<void>> futures;

    unsigned int blockStart = begin;

    if (blockSize) {
        for (unsigned int i = 0; i < (nthreads - 1); i++) {
            unsigned int blockEnd = blockStart + blockSize;
            futures.push_back(std::move(std::async(std::launch::async, 
                [blockStart, blockEnd, &f]() {
                    f(blockStart, blockEnd);
                })));
            blockStart = blockEnd;
        }
    }
    f(blockStart, end);
    for (auto& future: futures)
        future.wait();

}

template <typename TF>
void parallel_for(unsigned int begin, unsigned int end, const TF& func)
{
    auto length = end - begin;
    if (length == 0) {
        return ;
    }

    static auto const blockSize = (length) / std::thread::hardware_concurrency();
    if (blockSize > 0 && length <= blockSize) {
        for (int i = begin; i < end; i++) {
            func(i);
        }
        return ;
    }

    auto mid = begin + (end - begin) / 2;
    std::future<void> future = std::async(std::launch::async, parallel_for<TF>, mid, end, func);
    parallel_for(begin, mid, func);
    future.get();
}

#endif