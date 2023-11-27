#include <cstdio>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

#include "src/SpellcasterSrv.h"

void initMainTask() {
    SpellcasterSrv game;
    game.setup();

    while (game.update()) {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
    }

}



int main()
{
    
    // Constructs the new thread and runs it. Does not block execution.
    boost::thread t1(initMainTask);

    
    t1.join();
    
    return 0;
}