#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

const size_t ARRAY_SIZE = 100000000;
const int NUM_THREADS = 4;

long long parallel_sum_cpp11(const std::vector<int>& array, int num_threads) {
    std::vector<std::thread> threads;
    std::vector<long long> partial_sums(num_threads, 0);
    
    size_t chunk_size = array.size() / num_threads;
    
    auto worker = [&](int thread_id) {
        size_t start = thread_id * chunk_size;
        size_t end = (thread_id == num_threads - 1) ? array.size() : (thread_id + 1) * chunk_size;
        
        for (size_t i = start; i < end; i++) {
            partial_sums[thread_id] += array[i];
        }
    };
    
    // Запускаем потоки
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(worker, i);
    }
    
    // Ждем завершения
    for (auto& t : threads) {
        t.join();
    }
    
    long long total_sum = 0;
    for (long long partial : partial_sums) {
        total_sum += partial;
    }
    
    return total_sum;
}

int main() {
    std::vector<int> array(ARRAY_SIZE, 1);
    
    auto start_time = std::chrono::high_resolution_clock::now();
    long long sum = parallel_sum_cpp11(array, NUM_THREADS);
    auto end_time = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = end_time - start_time;
    
    std::cout << "C++11 threads version (" << NUM_THREADS << " threads):" << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Time: " << duration.count() << " seconds" << std::endl;
    
    return 0;
}