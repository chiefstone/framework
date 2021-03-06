/*
 * Copyright 2017 - 2018 The WizTK Authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WIZTK_ASYNC_SCHEDULER_HPP_
#define WIZTK_ASYNC_SCHEDULER_HPP_

#include "wiztk/base/macros.hpp"

namespace wiztk {
namespace async {

class Message;
class EventLoop;

/**
 * @ingroup async
 * @brief An EventScheduler is used to send and process Event associated with
 * EventQueue.
 */
class WIZTK_EXPORT Scheduler {

 public:

  /**
   * @brief Default constructor associates this EventScheduler with the
   * EventLoop for the current thread.
   */
  Scheduler();

  explicit Scheduler(EventLoop *event_loop);

  Scheduler(const Scheduler &) = default;

  Scheduler(Scheduler &&) = default;

  ~Scheduler();

  Scheduler &operator=(const Scheduler &) = default;

  Scheduler &operator=(Scheduler &&) = default;

  void PostMessage(Message *message);

  void PostMessageAfter(Message *a, Message *b);

 private:

  EventLoop *event_loop_ = nullptr;

};

} // namespace async
} // namespace wiztk

#endif // WIZTK_ASYNC_SCHEDULER_HPP_
