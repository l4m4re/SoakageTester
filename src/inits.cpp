//-----------------------------------------------------------------------------
// Inits.cpp
//-----------------------------------------------------------------------------
// Copyright 2015 Marvin Sinister, 2016 Arend Lammertink
//
// This file is part of CapBatteryTest.
//
//    CapBatteryTest is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    CapBatteryTest is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with CapBatteryTest.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "CapBatteryTest.h"

//-----------------------------------------------------------------------------
// initPins()
//-----------------------------------------------------------------------------
void initPins(void)
{
#if DEBUG == 1
    pinMode( 11, OUTPUT );    
    pinMode( 12, OUTPUT );    
    pinMode( 13, OUTPUT );    
#endif    
    pinMode( errorPin,     OUTPUT );
    pinMode( pwmOutPin,    OUTPUT );
    pinMode( dischargePin, OUTPUT );
}


