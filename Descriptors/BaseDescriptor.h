/*
    open source routing machine
    Copyright (C) Dennis Luxen, 2010

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU AFFERO General Public License as published by
the Free Software Foundation; either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
or see http://www.gnu.org/licenses/agpl.txt.
 */

#ifndef BASE_DESCRIPTOR_H_
#define BASE_DESCRIPTOR_H_

#include <cassert>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>

#include "../typedefs.h"
#include "../DataStructures/ExtractorStructs.h"
#include "../DataStructures/HashTable.h"
#include "../Util/StringUtil.h"

#include "../Plugins/RawRouteData.h"

struct _RouteSummary {
    std::string lengthString;
    std::string durationString;
    std::string startName;
    std::string destName;
    _RouteSummary() : lengthString("0"), durationString("0"), startName("unknown street"), destName("unknown street") {}
    void BuildDurationAndLengthStrings(unsigned distance, unsigned time) {
        //compute distance/duration for route summary
        std::ostringstream s;
        s << 10*(round(distance/10.));
        lengthString = s.str();
        int travelTime = time/10 + 1;
        s.str("");
        s << travelTime;
        durationString = s.str();
    }
};

struct _DescriptorConfig {
    _DescriptorConfig() : instructions(true), geometry(true), encodeGeometry(false), z(18) {}
    bool instructions;
    bool geometry;
    bool encodeGeometry;
    unsigned short z;
};

template<class SearchEngineT>
class BaseDescriptor {
public:
    BaseDescriptor() { }
    //Maybe someone can explain the pure virtual destructor thing to me (dennis)
    virtual ~BaseDescriptor() { }
    virtual void Run(http::Reply & reply, RawRouteData &rawRoute, PhantomNodes &phantomNodes, SearchEngineT &sEngine, unsigned distance) = 0;
    virtual void SetConfig(const _DescriptorConfig & config) = 0;
};

#endif /* BASE_DESCRIPTOR_H_ */
