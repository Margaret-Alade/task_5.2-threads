//
//  main.cpp
//  Task-2.1-Threads
//
//  Created by Маргарет  on 04.06.2024.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
using namespace std::chrono_literals;

std::atomic<int> client_count = 0;
std::mutex m;
void client(int max_num) {
    
    for (int i = 0; i < max_num; i++) {
        std::unique_lock lk(m, std::defer_lock);
        client_count += 1;
        lk.lock();
        std::cout << "Клиент зашел в очередь: client_count = " << client_count << "\n";
    }
}

void operat(int max_num) {
    for (int i = 0; i < max_num; i++) {
        std::unique_lock lk(m, std::defer_lock_t());
        client_count -= 1;
        lk.lock();
        std::cout << "Запрос клинта обработан: client_count = " << client_count << "\n";

    }
}


int main(int argc, const char * argv[]) {
    std::thread th1(client, 10);
    std::thread th2(operat, 10);
    th1.join();
    th2.join();
    std::cout << "Итоговое состояние счетчика клиентов: " << client_count << "\n";
    
    
    return 0;
}
