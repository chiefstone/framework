/*
 * Copyright 2017 The WizTK Authors.
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

#ifndef WIZTK_BASE_DEQUE_HPP_
#define WIZTK_BASE_DEQUE_HPP_

#include "wiztk/base/binode.hpp"

#include <cstddef>
#include <functional>

namespace wiztk {
namespace base {

/**
 * @ingroup base
 * @brief A simple double-ended queue container
 * @tparam T Must be a BiNode class or subclass
 */
template<typename T>
class Deque {

 public:

  WIZTK_DECLARE_NONCOPYABLE_AND_NONMOVALE(Deque);

  /**
   * @brief A nested iterator for deque
   */
  class Iterator {

   public:

    explicit Iterator(Binode *element = nullptr)
        : element_(element) {}

    Iterator(const Iterator &) = default;

    ~Iterator() = default;

    Iterator &operator=(const Iterator &) = default;

    Iterator &operator++() {
      element_ = element_->next_;
      return *this;
    }

    Iterator operator++(int) {
      return Iterator(element_->next_);
    }

    Iterator &operator--() {
      element_ = element_->previous_;
      return *this;
    }

    Iterator operator--(int) {
      return Iterator(element_->previous_);
    }

    void PushFront(T *element) {
      element_->PushFront(element);
    }

    void PushBack(T *element) {
      element_->PushBack(element);
    }

    /**
     * @brief Unlink the bi-node object and invalidate this iterator
     *
     * @note Once this method is called, this iterator is invalidated and
     * should not be used, but it can be assigned to another one.
     */
    void Remove() {
      element_->Unlink();
      element_ = nullptr;
    }

    bool operator==(const Iterator &other) const {
      return element_ == other.element_;
    }

    bool operator==(const T *element) const {
      return element_ == element;
    }

    bool operator!=(const Iterator &other) const {
      return element_ != other.element_;
    }

    bool operator!=(const T *element) const {
      return element_ != element;
    }

    T *element() const {
      return nullptr == element_->previous_ ?
             nullptr : (nullptr == element_->next_ ?
                        nullptr : (static_cast<T *>(element_)));

    }

    explicit operator bool() const {
      return nullptr == element_ ?
             false : (nullptr == element_->previous_ ?
                      false : (nullptr != element_->next_));
    }

   private:

    Binode *element_;

  };

  /**
   * @brief A nested const iterator class
   */
  class ConstIterator {

   public:

    ConstIterator() = delete;

    explicit ConstIterator(const Binode *element = nullptr)
        : element_(element) {}

    ConstIterator(const ConstIterator &) = default;

    ~ConstIterator() = default;

    ConstIterator &operator=(const ConstIterator &) = default;

    ConstIterator &operator++() {
      element_ = element_->next_;
      return *this;
    }

    ConstIterator operator++(int) {
      return ConstIterator(element_->next_);
    }

    ConstIterator &operator--() {
      element_ = element_->previous_;
      return *this;
    }

    ConstIterator operator--(int) {
      return ConstIterator(element_->previous_);
    }

    bool operator==(const ConstIterator &other) const {
      return element_ == other.element_;
    }

    bool operator==(const T *element) const {
      return element_ == element;
    }

    bool operator!=(const ConstIterator &other) const {
      return element_ != other.element_;
    }

    bool operator!=(const T *element) const {
      return element_ != element;
    }

    const T *element() const {
      return nullptr == element_->previous_ ?
             nullptr : (nullptr == element_->next_ ?
                        nullptr : (static_cast<const T *>(element_)));
    }

    explicit operator bool() const {
      return nullptr == element_ ?
             false : (nullptr == element_->previous_ ?
                      false : (nullptr != element_->next_));
    }

   private:

    const Binode *element_;

  };

  Deque();

  virtual ~Deque();

  void PushFront(T *item);

  void PushBack(T *item);

  void Insert(T *item, int index = 0);

  size_t GetSize() const;

  bool IsEmpty() const;

  void Clear(const std::function<void(Binode *)> &deleter);

  T *operator[](int index) const {
    return GetAt(index);
  }

  T *GetAt(int index) const;

  Iterator begin() const {
    return Iterator(first_.next_);
  }

  ConstIterator cbegin() const {
    return ConstIterator(first_.next_);
  }

  Iterator rbegin() const {
    return Iterator(last_.previous_);
  }

  ConstIterator crbegin() const {
    return ConstIterator(last_.previous_);
  }

  Iterator end() const {
    return Iterator(const_cast<Binode *>(&last_));
  }

  ConstIterator cend() const {
    return ConstIterator(&last_);
  }

  Iterator rend() const {
    return Iterator(const_cast<Binode *>(&first_));
  }

  ConstIterator crend() const {
    return ConstIterator(&first_);
  }

 protected:

  const Binode *first() const { return &first_; }

  const Binode *last() const { return &last_; }

 private:

  Binode first_;
  Binode last_;

};

template<typename T>
Deque<T>::Deque() {
  first_.next_ = &last_;
  last_.previous_ = &first_;
}

template<typename T>
Deque<T>::~Deque() {
  Clear([](Binode *obj) { delete obj; });
}

template<typename T>
void Deque<T>::PushFront(T *item) {
  item->Unlink();
  first_.PushBack(item);
}

template<typename T>
void Deque<T>::PushBack(T *item) {
  item->Unlink();
  last_.PushFront(item);
}

template<typename T>
void Deque<T>::Insert(T *item, int index) {
  if (index >= 0) {
    Binode *p = first_.next_;
    while ((&last_ != p) && (index > 0)) {
      p = p->next_;
      index--;
    }
    p->PushFront(item);
  } else {
    Binode *p = last_.previous_;
    while ((&first_ != p) && (index < -1)) {
      p = p->previous_;
      index++;
    }
    p->PushBack(item);
  }
}

template<typename T>
size_t Deque<T>::GetSize() const {
  size_t size = 0;

  Binode *element = first_.next_;
  while (element != &last_) {
    ++size;
    element = element->next_;
  }

  return size;
}

template<typename T>
bool Deque<T>::IsEmpty() const {
  return first_.next_ == &last_;
}

template<typename T>
void Deque<T>::Clear(const std::function<void(Binode *)> &deleter) {
  Binode *tmp = first_.next_;
  while (tmp != &last_) {
    tmp->Unlink();
    deleter(tmp);
    tmp = first_.next_;
  }
}

template<typename T>
T *Deque<T>::GetAt(int index) const {
  Binode *p = nullptr;

  if (index >= 0) {
    p = first_.next_;
    while ((&last_ != p) && (index > 0)) {
      p = p->next_;
      index--;
    }
  } else {
    p = last_.previous_;
    while ((&first_ != p) && (index < -1)) {
      p = p->previous_;
      index++;
    }
  }

  return static_cast<T *>(p);
}

} // namespace base
} // namespace wiztk

#endif // WIZTK_BASE_DEQUE_HPP_
