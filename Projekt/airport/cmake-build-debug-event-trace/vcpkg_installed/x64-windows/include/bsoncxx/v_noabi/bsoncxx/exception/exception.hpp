// Copyright 2015 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <system_error>

#include <bsoncxx/exception/exception-fwd.hpp>

#include <bsoncxx/config/prelude.hpp>

namespace bsoncxx {
namespace v_noabi {

///
/// Class representing any exceptions emitted from the bsoncxx library or
/// its underlying implementation.
///
class exception : public std::system_error {
    using std::system_error::system_error;
};

}  // namespace v_noabi
}  // namespace bsoncxx

#include <bsoncxx/config/postlude.hpp>
