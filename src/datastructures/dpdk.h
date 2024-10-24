// Copyright (c) 2014, the Scal Project Authors.  All rights reserved.
// Please see the AUTHORS file for details.  Use of this source code is governed
// by a BSD license that can be found in the LICENSE file.

// This is a wrapper around the upstream implementation of LCRQ. The files
// reside in
//   datastructures/upstream/lcrq
//
// The upstream files provide an implementation for:
//
// Fast Concurrent Queues for x86 Processors.  Adam Morrison and Yehuda Afek.
// PPoPP 2013.
//
// Website: http://mcg.cs.tau.ac.il/projects/lcrq/, accesed 01/28/2015

#ifndef SCAL_DATASTRUCTURES_BBQ_H_
#define SCAL_DATASTRUCTURES_BBQ_H_

#include "datastructures/queue.h"
#include <atomic>
namespace scal {

template<typename T>
class DPDK : public Queue<T> {

  static constexpr uint64_t CACHELINE_SIZE = 128;
  static constexpr uint64_t SIZE = 1024 * 1024;

 public:
  DPDK() {

  }

  bool enqueue(T t)
  {
      uint64_t ph = 0;
      uint64_t ct = 0;
      do {
          ph = phead.load(std::memory_order_relaxed);
          ct = ctail.load(std::memory_order_acquire);
          if (ph == ct + SIZE) {
              return false;
          }
      } while (!phead.compare_exchange_strong(ph, ph + 1, std::memory_order_relaxed, std::memory_order_relaxed));
      data[ph % SIZE] = t;
      while (ptail.load(std::memory_order_relaxed) != ph) {}
      ptail.store(ph + 1, std::memory_order_release);
      return true;
  }

  bool dequeue(T* t)
  {
        uint64_t ch = 0;
        uint64_t pt = 0;
        do {
            ch = chead.load(std::memory_order_relaxed);
            pt = ptail.load(std::memory_order_acquire);
            if (pt == ch) {
                return false;
            }
        } while (!chead.compare_exchange_strong(ch, ch + 1, std::memory_order_relaxed, std::memory_order_relaxed));
        *t = data[ch % SIZE];
        while (ctail.load(std::memory_order_relaxed) != ch) {}
        ctail.store(ch + 1, std::memory_order_release);
        return true;
  }

  private:
  
    alignas(CACHELINE_SIZE) std::atomic_uint64_t phead = { 0 };
    alignas(CACHELINE_SIZE) std::atomic_uint64_t ptail = { 0 };
    alignas(CACHELINE_SIZE) std::atomic_uint64_t chead = { 0 };
    alignas(CACHELINE_SIZE) std::atomic_uint64_t ctail = { 0 };
    alignas(CACHELINE_SIZE)

    T data[SIZE];

};

}

#endif
