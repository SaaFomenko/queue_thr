#include <iostream>
#include <thread>
#include <chrono>
#include "lib/colormod.h"


using namespace std::chrono_literals;
//static const int max_count = 7;
//static int count = 0;

namespace my
{
    const int max_count = 7;
    int count = 0;

    void client()
    {
        for (int i = 0; i < max_count; ++i)
        {
            Color::Modifier red(Color::FG_RED);
            std::this_thread::sleep_for(1s);
            std::cout << red << "Client took a queue with a number: " << ++count << '\n'; 
        }
    }

    void manager()
    {
        for (int i = 0; i < max_count; ++i)
        {
            Color::Modifier green(Color::FG_GREEN);
            std::this_thread::sleep_for(2s);
            std::cout << green << "Manager solved the issue with number: " << count-- << '\n'; 
        }
    }
   
} // namespace my

int main()
{

    //std::cout << "CPU cores: " << std::thread::hardware_concurrency() << '\n';

    std::thread client_thr(my::client);
    std::thread manager_thr(my::manager);

    if (client_thr.joinable())
        client_thr.join();
    if (manager_thr.joinable())
        manager_thr.join();

    return 0;
}