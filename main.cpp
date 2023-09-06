#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include "lib/colormod.h"


using namespace std::chrono_literals;
//static const int max_count = 7;
//static int count = 0;

namespace my
{
    std::mutex m;
    const int max_count = 7;
    std::atomic<int> count{0};
    //std::atomic<bool> isClient{false};
    //int count = 0;

    void client()
    {
        for (int i = 0; i < max_count; ++i)
        {
            m.lock();

            Color::Modifier red(Color::FG_RED);
            count.store(count.load() + 1, std::memory_order_seq_cst);
            //count.store(count.load() + 1, std::memory_order_relaxed);
            //count.store(count.load() + 1, std::memory_order_acq_rel);
            //count.store(count.load() + 1, std::memory_order_acquire);
            //count.store(count.load() + 1, std::memory_order_consume);
            //count.store(count.load() + 1, std::memory_order_release);
            //std::cout << red << "Client took a queue with a number: " << ++count << '\n';
            //isClient.store(true); 
            std::cout << red << "Client took a queue with a number: " << count << '\n'; 
            //std::this_thread::sleep_for(1s);

            m.unlock();
        }
    }

    void manager()
    {
        while (count.load() != 0)
        {
            m.lock();
            Color::Modifier green(Color::FG_GREEN);
           // std::cout << green << "Manager solved the issue with number: " << count-- << '\n'; 
         //   isClient.store(false); 
            std::cout << green << "Manager solved the issue with number: " << count << '\n'; 
            count.store(count.load() - 1, std::memory_order_seq_cst);
            //count.store(count.load() - 1, std::memory_order_relaxed);
            m.unlock();
        }
        // for (int i = 0; i < max_count; ++i)
        // {

        //     if (count.load() > 0)
        //     {
        //         Color::Modifier green(Color::FG_GREEN);
        //         std::cout << green << "Manager solved the issue with number: " << count << '\n'; 
        //         count.store(count.load() - 1, std::memory_order_relaxed);
        //     }
        //     //std::cout << green << "Manager solved the issue with number: " << count-- << '\n'; 
        //     //count.store(count.load() - 1, std::memory_order_acq_rel);
        //     //count.store(count.load() - 1, std::memory_order_acquire);
        //     //count.store(count.load() - 1, std::memory_order_consume);
        //     //count.store(count.load() - 1, std::memory_order_release);
        //     //std::this_thread::sleep_for(2s);

        // }
    }
   
} // namespace my

int main()
{

    //std::cout << "CPU cores: " << std::thread::hardware_concurrency() << '\n';
    //std::cout << "CPU supports atomic objects: ";
    //std::cout << std::boolalpha << my::count.is_lock_free() << "\n\n";

    auto start = std::chrono::steady_clock::now();

    std::thread client_thr(my::client);
    std::thread manager_thr(my::manager);

    if (client_thr.joinable())
        client_thr.join();
    if (manager_thr.joinable())
        manager_thr.join();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    
    Color::Modifier def(Color::FG_DEFAULT);
    std::cout << def << "\nElapsed seconds: " << elapsed_seconds.count() << '\n';

    return 0;
}