/*
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
 */
#ifndef OPENDNP3_LOGGINGHANDLER_H
#define OPENDNP3_LOGGINGHANDLER_H

#include <openpal/logging/Logger.h>
#include <openpal/logging/LogMacros.h>
#include <openpal/util/ToHex.h>

#include "opendnp3/app/parsing/IAPDUHandler.h"
#include "opendnp3/decoder/IDecoderCallbacks.h"
#include "opendnp3/decoder/Indent.h"
#include "opendnp3/LogLevels.h"

#include <cstdint>
#include <sstream>

namespace opendnp3
{	
	// stand-alone DNP3 decoder
	class LoggingHandler final : public IAPDUHandler
	{
	public:

		LoggingHandler(openpal::Logger logger, IDecoderCallbacks& callbacks);

	private:	

		openpal::Logger logger;
		IDecoderCallbacks* callbacks;

		static const char* GetStringValue(bool value)
		{
			return value ? "1" : "0";
		}	

		static std::string ToHex(uint8_t b)
		{
			std::ostringstream oss;
			oss << openpal::ToHexChar((b & 0xf0) >> 4) << openpal::ToHexChar(b & 0xf);
			return oss.str();
		}

		/// --- templated helpers ---

		IINField PrintUnsupported();

		template <class T>
		IINField PrintV(const ICollection<Indexed<T>>& items);

		template <class T>
		IINField PrintAO(const ICollection<Indexed<T>>& items);
		
		IINField PrintCrob(const ICollection<Indexed<ControlRelayOutputBlock>>& items);

		template <class T>
		IINField PrintVQT(const ICollection<Indexed<T>>& items);

		template <class T, class Stringify>
		IINField PrintVQTStringify(const ICollection<Indexed<T>>& items, const Stringify& stringify);

		/// --- Implement IAPDUHandler ---

		virtual bool IsAllowed(uint32_t, GroupVariation, QualifierCode) override { return true; }

		virtual IINField ProcessHeader(const FreeFormatHeader& header, const Group120Var1& value, const openpal::RSlice& object) override;
		virtual IINField ProcessHeader(const FreeFormatHeader& header, const Group120Var2& value, const openpal::RSlice& object) override;
		virtual IINField ProcessHeader(const FreeFormatHeader& header, const Group120Var5& value, const openpal::RSlice& object) override;
		virtual IINField ProcessHeader(const FreeFormatHeader& header, const Group120Var6& value, const openpal::RSlice& object) override;
		virtual IINField ProcessHeader(const FreeFormatHeader& header, const Group120Var7& value, const openpal::RSlice& object) override;
		virtual IINField ProcessHeader(const FreeFormatHeader& header, const Group120Var9& value, const openpal::RSlice& object) override;
		virtual IINField ProcessHeader(const FreeFormatHeader& header, const Group120Var10& value, const openpal::RSlice& object) override;
		virtual IINField ProcessHeader(const FreeFormatHeader& header, const Group120Var11& value, const openpal::RSlice& object) override;
		virtual IINField ProcessHeader(const FreeFormatHeader& header, const Group120Var12& value, const openpal::RSlice& object) override;
		virtual IINField ProcessHeader(const FreeFormatHeader& header, const Group120Var13& value, const openpal::RSlice& object) override;
		virtual IINField ProcessHeader(const FreeFormatHeader& header, const Group120Var14& value, const openpal::RSlice& object) override;
		virtual IINField ProcessHeader(const FreeFormatHeader& header, const Group120Var15& value, const openpal::RSlice& object) override;

		virtual IINField ProcessHeader(const CountHeader& header, const ICollection<Group50Var1>& values) override;
		virtual IINField ProcessHeader(const CountHeader& header, const ICollection<Group51Var1>& values) override;
		virtual IINField ProcessHeader(const CountHeader& header, const ICollection<Group51Var2>& values) override;
		virtual IINField ProcessHeader(const CountHeader& header, const ICollection<Group52Var1>& values) override;
		virtual IINField ProcessHeader(const CountHeader& header, const ICollection<Group52Var2>& values) override;
		virtual IINField ProcessHeader(const CountHeader& header, const ICollection<Group120Var3>& values) override;
		virtual IINField ProcessHeader(const CountHeader& header, const ICollection<Group120Var4>& values) override;

		virtual IINField ProcessHeader(const RangeHeader& header, const ICollection<Indexed<IINValue>>& values) override;
		virtual IINField ProcessHeader(const RangeHeader& header, const ICollection<Indexed<Binary>>& values) override;
		virtual IINField ProcessHeader(const RangeHeader& header, const ICollection<Indexed<DoubleBitBinary>>& values) override;
		virtual IINField ProcessHeader(const RangeHeader& header, const ICollection<Indexed<BinaryOutputStatus>>& values) override;
		virtual IINField ProcessHeader(const RangeHeader& header, const ICollection<Indexed<Counter>>& values) override;
		virtual IINField ProcessHeader(const RangeHeader& header, const ICollection<Indexed<FrozenCounter>>& values) override;
		virtual IINField ProcessHeader(const RangeHeader& header, const ICollection<Indexed<Analog>>& values) override;
		virtual IINField ProcessHeader(const RangeHeader& header, const ICollection<Indexed<AnalogOutputStatus>>& values) override;
		virtual IINField ProcessHeader(const RangeHeader& header, const ICollection<Indexed<OctetString>>& values) override;
		virtual IINField ProcessHeader(const RangeHeader& header, const ICollection<Indexed<TimeAndInterval>>& values) override;
		virtual IINField ProcessHeader(const RangeHeader& header, const ICollection<Indexed<Group121Var1>>& values) override;

		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<Binary>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<BinaryOutputStatus>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<DoubleBitBinary>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<Counter>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<FrozenCounter>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<Analog>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<AnalogOutputStatus>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<OctetString>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<TimeAndInterval>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<BinaryCommandEvent>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<AnalogCommandEvent>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<Group122Var1>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<Group122Var2>>& values) override;

		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<ControlRelayOutputBlock>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<AnalogOutputInt16>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<AnalogOutputInt32>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<AnalogOutputFloat32>>& values) override;
		virtual IINField ProcessHeader(const PrefixHeader& header, const ICollection<Indexed<AnalogOutputDouble64>>& values) override;				
	};
	
	template <class T>
	IINField LoggingHandler::PrintV(const ICollection<Indexed<T>>& items)
	{
		Indent i(*callbacks);
		auto logItem = [this](const Indexed<T>& item) 
		{
			FORMAT_LOG_BLOCK(logger, flags::APP_OBJECT_RX, "[%u] - value: %s", item.index, GetStringValue(item.value.value));
		};

		items.ForeachItem(logItem);

		return IINField::Empty();
	}

	template <class T>
	IINField LoggingHandler::PrintVQT(const ICollection<Indexed<T>>& items)
	{
		Indent i(*callbacks);
		auto logItem = [this](const Indexed<T>& item)
		{
			std::ostringstream oss;
			oss << "[" << item.index << "] - value: " << item.value.value;
			oss << " flags: 0x" << std::hex << ToHex(item.value.quality) << std::dec;
			oss << " time: " << item.value.time.Get();
			SIMPLE_LOG_BLOCK(logger, flags::APP_OBJECT_RX, oss.str().c_str());
		};

		items.ForeachItem(logItem);

		return IINField::Empty();
	}

	template <class T>
	IINField LoggingHandler::PrintAO(const ICollection<Indexed<T>>& items)
	{
		Indent i(*callbacks);
		auto logItem = [this](const Indexed<T>& item)
		{
			std::ostringstream oss;
			oss << "[" << item.index << "] - value: " << item.value.value;			
			oss << " status: " << CommandStatusToString(item.value.status);
			SIMPLE_LOG_BLOCK(logger, flags::APP_OBJECT_RX, oss.str().c_str());
		};

		items.ForeachItem(logItem);

		return IINField::Empty();
	}


	template <class T, class Stringify>
	IINField LoggingHandler::PrintVQTStringify(const ICollection<Indexed<T>>& items, const Stringify& stringify)
	{
		Indent i(*callbacks);
		auto logItem = [&](const Indexed<T>& item)
		{
			std::ostringstream oss;
			oss << "[" << item.index << "] - value: " << stringify(item.value.value);
			oss << " flags: 0x" << std::hex << ToHex(item.value.quality) << std::dec;
			oss << " time: " << item.value.time.Get();
			SIMPLE_LOG_BLOCK(logger, flags::APP_OBJECT_RX, oss.str().c_str());
		};

		items.ForeachItem(logItem);

		return IINField::Empty();
	}
}

#endif