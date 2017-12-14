/*
 * Copyright 2016 Freeman Zhang <zhanggyb@gmail.com>
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

#ifndef WIZTK_BASE_COUNTED_DEQUE_HPP_
#define WIZTK_BASE_COUNTED_DEQUE_HPP_

#include "wiztk/base/macros.hpp"

namespace wiztk {
namespace base {

/**
 * @ingroup base
 * @brief A double-ended queue container with an element counter.
 */
class CountedDeque {

 public:

  WIZTK_DECLARE_NONCOPYABLE_AND_NONMOVALE(CountedDeque);

  /**
 * @brief A nested class represents an element in a deque
 */
  class Element {

    friend class CountedDeque;

   public:

    WIZTK_DECLARE_NONCOPYABLE_AND_NONMOVALE(Element);

    Element() = default;

    virtual ~Element();

    Element *previous() const { return previous_; }

    Element *next() const { return next_; }

    CountedDeque *deque() const { return deque_; }

   private:

    Element *previous_ = nullptr;
    Element *next_ = nullptr;
    CountedDeque *deque_ = nullptr;

  };

  /**
   * @brief A nested iterator for deque
   */
  class Iterator {

   public:

    explicit Iterator(Element *element = nullptr)
        : element_(element) {}

    Iterator(const Iterator &orig) = default;

    ~Iterator() = default;

    Iterator &operator=(const Iterator &other) = default;

    Iterator &operator++() {
      element_ = element_->next_;
      return *this;
    }

    Iterator operator++(int) {
      Iterator retval;
      retval.element_ = element_->next_;
      return retval;
    }

    Iterator &operator--() {
      element_ = element_->previous_;
      return *this;
    }

    Iterator operator--(int) {
      Iterator retval;
      retval.element_ = element_->previous_;
      return retval;
    }

    bool operator==(const Iterator &other) const {
      return element_ == other.element_;
    }

    bool operator==(const Element *element) const {
      return element_ == element;
    }

    bool operator!=(const Iterator &other) const {
      return element_ != other.element_;
    }

    bool operator!=(const Element *element) const {
      return element_ != element;
    }

    template<typename T>
    T *cast() const {
      return static_cast<T *>(element_);
    }

    explicit operator bool() const {
      return nullptr != element_;
    }

   private:

    Element *element_;

  };

  CountedDeque() = default;

  virtual ~CountedDeque();

  void PushFront(Element *item);

  void PushBack(Element *item);

  void Insert(Element *item, int index = 0);

  Element *Remove(Element *item);

  void Clear();

  Element *operator[](int index) const;

  Iterator begin() const {
    return Iterator(first_);
  }

  Iterator rbegin() const {
    return Iterator(last_);
  }

  Iterator end() const {
    return Iterator(last_->next_);
  }

  Iterator rend() const {
    return Iterator(first_->previous_);
  }

  int count() const { return count_; }

  Element *first() const { return first_; }

  Element *last() const { return last_; }

 private:

  Element *first_ = nullptr;
  Element *last_ = nullptr;
  int count_ = 0;

};

} // namespace base
} // namespace wiztk

#endif // WIZTK_BASE_COMPOUND_DEQUE_HPP_