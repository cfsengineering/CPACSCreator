/* 
* Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
*
* Created: 2013-12-10 Martin Siggel <Martin.Siggel@dlr.de>
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef CSHAREDPTR_H
#define CSHAREDPTR_H

#include "tigl_config.h"

#ifdef HAVE_STDSHARED_PTR
    #include <memory>
    #define CSharedPtr std::shared_ptr
#else
    #include <boost/smart_ptr/shared_ptr.hpp>
    #define CSharedPtr boost::shared_ptr
#endif

#endif // CSHAREDPTR_H
