//
//  Thread.h
//
//  Created by asd on 29/04/2019.
//  Copyright © 2019 voicesync. All rights reserved.
//

#pragma once
#include <vector>
#include <functional>
#include <thread>

using std::thread, std::vector;

class Thread {
  public:
    Thread() : nth(int(thread::hardware_concurrency())) {
        threads.resize(nth);
    }

    Thread(int size)
        : nth(size < int(thread::hardware_concurrency())
              ? size
              : int(thread::hardware_concurrency())),
          segSz(size > nth ? size / nth : 1),
          size(size)  {
        threads.resize(nth);
    }

    static int getnthreads() {
        return int(thread::hardware_concurrency());
    }

    int from(int t) {
        return t * segSz;
    }
    int to(int t) {
        return ((t == nth - 1) ? size : (t + 1) * segSz);
    }

    void run(std::function<void(int, int, int)> const &lambda) {  // t, from, to
        for (int t = 0; t < nth; t++) {
            threads[t] = thread([this, lambda, t]() {
                lambda(t, from(t), to(t));
            });
        }
        for (int t = 0; t < nth; t++) threads[t].join();
    }

    void run(std::function<void(int)> const &lambda) {  // i
        for (int t = 0; t < nth; t++) {
            threads[t] = thread([this, lambda, t]() {
                for (int i = from(t); i < to(t); i++) lambda(i);
            });
        }
        for (auto&t:threads) t.join();
    }

    void run(std::function<void(int, int)> const &lambda) {  // t, i
        for (int t = 0; t < nth; t++) {
            threads[t] = thread([this, lambda, t]() {
                for (int i = from(t); i < to(t); i++) lambda(t, i);
            });
        }
        for (auto&t:threads) t.join();
    }

    void run(std::function<void(void)> const &lambda) {  // ()
        for (int t = 0; t < nth; t++) {
            threads[t] = thread([this, lambda, t]() {
                for (int i = from(t); i < to(t); i++) lambda();
            });
        }
        for (auto&t:threads) t.join();
    }



    void join() {
        for (int t = 0; t < nth; t++)
            if (threads[t].joinable()) threads[t].join();
    }

    static void sleep(int ms = 100) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    int nth = int(thread::hardware_concurrency()), segSz = 0, size = 0;
    vector<thread>threads;
};



