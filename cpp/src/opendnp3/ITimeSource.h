
//
// Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
// more contributor license agreements. See the NOTICE file distributed
// with this work for additional information regarding copyright ownership.
// Green Energy Corp licenses this file to you under the Apache License,
// Version 2.0 (the "License"); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// This file was forked on 01/01/2013 by Automatak, LLC and modifications
// have been made to this file. Automatak, LLC licenses these modifications to
// you under the terms of the License.
//

#ifndef __I_TIME_SOURCE_H_
#define __I_TIME_SOURCE_H_

#include <openpal/Types.h>
#include <openpal/Visibility.h>


namespace opendnp3
{

class DLL_LOCAL ITimeSource
{

public:
	virtual openpal::timer_clock::time_point GetUTC() = 0;
	openpal::millis_t GetMillisecondsSinceEpoch();

};

class DLL_LOCAL ITimeManager : public ITimeSource
{
public:
	virtual void SetTime(const openpal::timer_clock::time_point& arTime) = 0;
};



}

#endif

