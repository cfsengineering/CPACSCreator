/*
* Copyright (C) 2018 CFS Engineering
*
* Created: 2018 Malo Drougard <malo.drougard@protonmail.com>
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
//
// Created by makem on 08/04/18.
//

#include "CreatorException.h"
#include "easylogging++.h"

CreatorException::CreatorException( const std::string& msg, int errNum) : std::exception() {
    message = msg;
    errNumber = errNum;
   // LOG(ERROR) << "CreatorException with message: \"" << msg << "\" was created.";

}

const char *CreatorException::what() const throw() {

    return message.c_str();

}

void CreatorException::addToMessage(const std::string& msg) {
    message = message + msg;
    LOG(ERROR) << "New message: " << message ;
}

