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

#ifndef SCAL_DATASTRUCTURES_HACKQ_H_
#define SCAL_DATASTRUCTURES_HACKQ_H_

#include "datastructures/queue.h"
#include "datastructures/hackathonq.h"

#ifdef __cplusplus
extern "C" {
#endif
static inline void
hackathonq_init() {
    
}

static inline bool
hackathonq_enqueue(uint64_t item) {
    return true;
}

static inline bool
hackathonq_dequeue(uint64_t *item) {
    return true;
}
#ifdef __cplusplus
}
#endif

namespace scal {

template<typename T>
class HackathonQueue : public Queue<T> {
 public:
  inline HackathonQueue() {
    hackathonq_init();
  }

  inline bool enqueue(T item) {
    return hackathonq_enqueue(item);
  }

  inline bool dequeue(T* item) {
    return hackathonq_dequeue(item);
  }
};

}

#endif
