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

#ifndef WIZTK_GRAPHIC_ALIGNMENT_HPP_
#define WIZTK_GRAPHIC_ALIGNMENT_HPP_

#include "wiztk/base/macros.hpp"

namespace wiztk {
namespace graphics {

/**
 * @ingroup graphics
 * @brief Text Alignment
 *
 * Text alignment adjusts the text relative to the text position.
 */
class WIZTK_EXPORT Alignment {

 public:

  enum Type {
    kLeft,
    kTop,
    kRight,
    kBottom
  };

  explicit Alignment(int init = 0)
      : value_(init) {}

  int value() const { return value_; }

 private:

  int value_ = 0;

};

} // namespace graphics
} // namespace wiztk

#endif // WIZTK_GRAPHIC_TEXT_ALIGNMENT_HPP_
