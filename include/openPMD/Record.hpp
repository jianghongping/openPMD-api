/* Copyright 2017-2019 Fabian Koller
 *
 * This file is part of openPMD-api.
 *
 * openPMD-api is free software: you can redistribute it and/or modify
 * it under the terms of of either the GNU General Public License or
 * the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * openPMD-api is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License and the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * and the GNU Lesser General Public License along with openPMD-api.
 * If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "openPMD/backend/BaseRecord.hpp"
#include "openPMD/RecordComponent.hpp"

#include <map>
#include <type_traits>
#include <string>


namespace openPMD
{
class Record : public BaseRecord< RecordComponent >
{
    friend class Container< Record >;
    friend class Iteration;
    friend class ParticleSpecies;

public:
    Record(Record const&) = default;
    Record& operator=(Record const&) = default;
    ~Record() override = default;

    Record& setUnitDimension(std::map< UnitDimension, double > const&);

    template< typename T >
    T timeOffset() const;
    template< typename T >
    Record& setTimeOffset(T);

private:
    Record();

    void flush_impl(std::string const&) override;
    void read() override;
};  //Record


template< typename T >
inline T
Record::timeOffset() const
{ return readFloatingpoint< T >("timeOffset"); }

template< typename T >
inline Record&
Record::setTimeOffset(T to)
{
    static_assert(std::is_floating_point< T >::value, "Type of attribute must be floating point");

    setAttribute("timeOffset", to);
    return *this;
}
} // openPMD
