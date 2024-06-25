#include "customerAtLobby.h"


CustomerAtLobby::CustomerAtLobby() : User()
{
    setTitle("customerAtLobbyWaiting");
    std::ifstream openDb("../dataBase/customerAtLobbyQueue.txt");
    std::ofstream spinLock("../dataBase/customerAtLobbyQueueSL.txt");//spinlock
    spinLock.close();//closes immdeiatly


    if(!openDb.is_open())
    {
        //not suppose to happen, assume queue is empty?

    }



    std::string queue = "";
    while(getline(openDb, queue))
    {
        decryptString(&queue[0], queue.length());

        std::stringstream ss(queue);
    }
}

void CustomerAtLobby::run()
{
    
}


std::string CustomerAtLobby::getTitlePrivilege()
{
    return title;
}
