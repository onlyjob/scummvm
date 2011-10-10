/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * Additional copyright for this file:
 * Copyright (C) 1995-1997 Presto Studios, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "pegasus/items/biochips/mapimage.h"

namespace Pegasus {

#define FLAG_TO_INDEX(flag) ((flag) >> 2)
#define INDEX_TO_FLAG(index) ((index) << 2)

#define ROOM_TO_INDEX(room) \
	(((room) >= kMars35 && (room) <= kMars39) ? ((room) - kMars35) : \
		(((room) == kMars60) ? (kMars39 - kMars35 + 1) : \
			((room) - kMarsMaze004 + kMars39 - kMars35 + 2)))

#define INDEX_TO_ROOM(index) \
	(((index) <= ROOM_TO_INDEX(kMars39)) ? \
	(((index) - ROOM_TO_INDEX(kMars35)) + kMars35) : \
		((index) <= ROOM_TO_INDEX(kMars60,)) ? kMars60 : \
			((((index) - ROOM_TO_INDEX(kMarsMaze004))) + kMarsMaze004))

#define ROOM_TO_FLAG(room, dir) (INDEX_TO_FLAG(ROOM_TO_INDEX(room)) | (dir))

#define FLAG_TO_ROOM(flag) (INDEX_TO_ROOM(FLAG_TO_INDEX(flag)))

#define FLAG_TO_DIRECTION(flag) ((flag) & 3)

static const long kGearRoomFlagLow = ROOM_TO_FLAG(kMars35, kNorth);
static const long kGearRoomFlagHigh = ROOM_TO_FLAG(kMars39, kWest);

static const long kMazeFlagLow = ROOM_TO_FLAG(kMars60, kNorth);
static const long kMazeFlagHigh = ROOM_TO_FLAG(kMarsMaze200, kWest);

static const tCoordType kGearRoomScreenOffsetX = 49;
static const tCoordType kGearRoomScreenOffsetY = 47;

static const tCoordType kGearRoomGridOriginX = 1;
static const tCoordType kGearRoomGridOriginY = 4;

static const tCoordType kMazeScreenOffsetX = 16;
static const tCoordType kMazeScreenOffsetY = 20;

static const tCoordType kMazeGridOriginX = 6;
static const tCoordType kMazeGridOriginY = 1;

static const tCoordType kGridWidth = 4;
static const tCoordType kGridHeight = 4;

static const int s_mapCoords[MapImage::kNumMappingRooms][2] = {
	/* kMars35 */      { 0, 0 },
	/* kMars36 */      { 1, 0 },
	/* kMars37 */      { 2, 0 },
	/* kMars38 */      { 3, 0 },
	/* kMars39 */      { 4, 0 },
	/* kMars60 */      { 19, 9 },
	/* kMarsMaze004 */ { 18, 9 },
	/* kMarsMaze005 */ { 18, 10 },
	/* kMarsMaze006 */ { 17, 10 },
	/* kMarsMaze007 */ { 16, 10 },
	/* kMarsMaze008 */ { 15, 10 },
	/* kMarsMaze009 */ { 14, 10 },
	/* kMarsMaze010 */ { 14, 9 },
	/* kMarsMaze011 */ { 14, 8 },
	/* kMarsMaze012 */ { 14, 7 },
	/* kMarsMaze015 */ { 16, 7 },
	/* kMarsMaze016 */ { 14, 11 },
	/* kMarsMaze017 */ { 14, 12 },
	/* kMarsMaze018 */ { 15, 12 },
	/* kMarsMaze019 */ { 16, 12 },
	/* kMarsMaze020 */ { 16, 13 },
	/* kMarsMaze021 */ { 16, 14 },
	/* kMarsMaze022 */ { 16, 15 },
	/* kMarsMaze023 */ { 17, 15 },
	/* kMarsMaze024 */ { 18, 15 },
	/* kMarsMaze025 */ { 18, 14 },
	/* kMarsMaze026 */ { 18, 13 },
	/* kMarsMaze027 */ { 18, 12 },
	/* kMarsMaze028 */ { 18, 11 },
	/* kMarsMaze031 */ { 19, 14 },
	/* kMarsMaze032 */ { 20, 14 },
	/* kMarsMaze033 */ { 20, 13 },
	/* kMarsMaze034 */ { 20, 12 },
	/* kMarsMaze035 */ { 20, 11 },
	/* kMarsMaze036 */ { 21, 11 },
	/* kMarsMaze037 */ { 15, 15 },
	/* kMarsMaze038 */ { 14, 15 },
	/* kMarsMaze039 */ { 13, 15 },
	/* kMarsMaze042 */ { 10, 15 },
	/* kMarsMaze043 */ { 9, 15 },
	/* kMarsMaze044 */ { 8, 15 },
	/* kMarsMaze045 */ { 7, 15 },
	/* kMarsMaze046 */ { 6, 15 },
	/* kMarsMaze047 */ { 5, 15 },
	/* kMarsMaze049 */ { 13, 14 },
	/* kMarsMaze050 */ { 12, 14 },
	/* kMarsMaze051 */ { 11, 14 },
	/* kMarsMaze052 */ { 10, 14 },
	/* kMarsMaze053 */ { 10, 13 },
	/* kMarsMaze054 */ { 9, 13 },
	/* kMarsMaze055 */ { 8, 13 },
	/* kMarsMaze056 */ { 8, 12 },
	/* kMarsMaze057 */ { 7, 12 },
	/* kMarsMaze058 */ { 12, 13 },
	/* kMarsMaze059 */ { 12, 12 },
	/* kMarsMaze060 */ { 12, 11 },
	/* kMarsMaze061 */ { 12, 10 },
	/* kMarsMaze063 */ { 12, 9 },
	/* kMarsMaze064 */ { 12, 8 },
	/* kMarsMaze065 */ { 12, 7 },
	/* kMarsMaze066 */ { 13, 7 },
	/* kMarsMaze067 */ { 15, 7 },
	/* kMarsMaze068 */ { 17, 7 },
	/* kMarsMaze069 */ { 18, 7 },
	/* kMarsMaze070 */ { 19, 7 },
	/* kMarsMaze071 */ { 20, 7 },
	/* kMarsMaze072 */ { 20, 6 },
	/* kMarsMaze074 */ { 20, 5 },
	/* kMarsMaze076 */ { 20, 4 },
	/* kMarsMaze078 */ { 20, 3 },
	/* kMarsMaze079 */ { 20, 2 },
	/* kMarsMaze081 */ { 20, 2 },
	/* kMarsMaze083 */ { 20, 0 },
	/* kMarsMaze084 */ { 19, 0 },
	/* kMarsMaze085 */ { 18, 0 },
	/* kMarsMaze086 */ { 17, 0 },
	/* kMarsMaze087 */ { 16, 0 },
	/* kMarsMaze088 */ { 15, 0 },
	/* kMarsMaze089 */ { 14, 0 },
	/* kMarsMaze090 */ { 13, 0 },
	/* kMarsMaze091 */ { 12, 0 },
	/* kMarsMaze092 */ { 11, 0 },
	/* kMarsMaze093 */ { 10, 0 },
	/* kMarsMaze098 */ { 10, 1 },
	/* kMarsMaze099 */ { 8, 2 },
	/* kMarsMaze100 */ { 9, 2 },
	/* kMarsMaze101 */ { 10, 2 },
	/* kMarsMaze104 */ { 13, 2 },
	/* kMarsMaze105 */ { 13, 3 },
	/* kMarsMaze106 */ { 13, 4 },
	/* kMarsMaze107 */ { 13, 5 },
	/* kMarsMaze108 */ { 14, 5 },
	/* kMarsMaze111 */ { 15, 5 },
	/* kMarsMaze113 */ { 16, 5 },
	/* kMarsMaze114 */ { 17, 5 },
	/* kMarsMaze115 */ { 18, 5 },
	/* kMarsMaze116 */ { 18, 4 },
	/* kMarsMaze117 */ { 18, 3 },
	/* kMarsMaze118 */ { 19, 3 },
	/* kMarsMaze119 */ { 18, 2 },
	/* kMarsMaze120 */ { 17, 2 },
	/* kMarsMaze121 */ { 16, 2 },
	/* kMarsMaze122 */ { 15, 2 },
	/* kMarsMaze123 */ { 15, 1 },
	/* kMarsMaze124 */ { 12, 4 },
	/* kMarsMaze125 */ { 11, 4 },
	/* kMarsMaze126 */ { 10, 4 },
	/* kMarsMaze127 */ { 10, 5 },
	/* kMarsMaze128 */ { 10, 6 },
	/* kMarsMaze129 */ { 9, 6 },
	/* kMarsMaze130 */ { 8, 6 },
	/* kMarsMaze131 */ { 7, 6 },
	/* kMarsMaze132 */ { 7, 7 },
	/* kMarsMaze133 */ { 7, 8 },
	/* kMarsMaze136 */ { 7, 11 },
	/* kMarsMaze137 */ { 6, 11 },
	/* kMarsMaze138 */ { 5, 11 },
	/* kMarsMaze139 */ { 5, 12 },
	/* kMarsMaze140 */ { 4, 12 },
	/* kMarsMaze141 */ { 5, 13 },
	/* kMarsMaze142 */ { 5, 14 },
	/* kMarsMaze143 */ { 4, 14 },
	/* kMarsMaze144 */ { 3, 14 },
	/* kMarsMaze145 */ { 3, 13 },
	/* kMarsMaze146 */ { 2, 13 },
	/* kMarsMaze147 */ { 1, 13 },
	/* kMarsMaze148 */ { 1, 14 },
	/* kMarsMaze149 */ { 1, 15 },
	/* kMarsMaze152 */ { 1, 12 },
	/* kMarsMaze153 */ { 1, 11 },
	/* kMarsMaze154 */ { 1, 10 },
	/* kMarsMaze155 */ { 1, 9 },
	/* kMarsMaze156 */ { 1, 8 },
	/* kMarsMaze157 */ { 2, 10 },
	/* kMarsMaze159 */ { 2, 8 },
	/* kMarsMaze160 */ { 2, 7 },
	/* kMarsMaze161 */ { 2, 6 },
	/* kMarsMaze162 */ { 3, 10 },
	/* kMarsMaze163 */ { 3, 9 },
	/* kMarsMaze164 */ { 3, 8 },
	/* kMarsMaze165 */ { 4, 8 },
	/* kMarsMaze166 */ { 5, 8 },
	/* kMarsMaze167 */ { 6, 8 },
	/* kMarsMaze168 */ { 3, 6 },
	/* kMarsMaze169 */ { 4, 6 },
	/* kMarsMaze170 */ { 5, 6 },
	/* kMarsMaze171 */ { 5, 5 },
	/* kMarsMaze172 */ { 5, 4 },
	/* kMarsMaze173 */ { 4, 4 },
	/* kMarsMaze174 */ { 3, 4 },
	/* kMarsMaze175 */ { 3, 5 },
	/* kMarsMaze177 */ { 8, 4 },
	/* kMarsMaze178 */ { 8, 3 },
	/* kMarsMaze179 */ { 7, 4 },
	/* kMarsMaze180 */ { 6, 4 },
	/* kMarsMaze181 */ { 6, 3 },
	/* kMarsMaze182 */ { 6, 2 },
	/* kMarsMaze183 */ { 6, 1 },
	/* kMarsMaze184 */ { 6, 0 },
	/* kMarsMaze187 */ { 3, 0 },
	/* kMarsMaze188 */ { 2, 0 },
	/* kMarsMaze189 */ { 1, 0 },
	/* kMarsMaze190 */ { 1, 1 },
	/* kMarsMaze191 */ { 1, 2 },
	/* kMarsMaze192 */ { 5, 2 },
	/* kMarsMaze193 */ { 4, 2 },
	/* kMarsMaze194 */ { 3, 2 },
	/* kMarsMaze195 */ { 3, 1 },
	/* kMarsMaze198 */ { 1, 3 },
	/* kMarsMaze199 */ { 1, 4 },
	/* kMarsMaze200 */ { 0, 4 }
};

MapImage::MapImage() : DisplayElement(kNoDisplayElement) {
	_whichArea = kMapNoArea;
	setBounds(kAIMiddleAreaLeft, kAIMiddleAreaTop, kAIMiddleAreaLeft + kAIMiddleAreaWidth, kAIMiddleAreaTop + kAIMiddleAreaHeight);
	setDisplayOrder(kAIMiddleAreaOrder + 10);
	startDisplaying();

	_darkGreen = g_system->getScreenFormat().RGBToColor(64, 150, 10);
	_lightGreen = g_system->getScreenFormat().RGBToColor(102, 239, 0);
}

void MapImage::writeToStream(Common::WriteStream *stream) {
	_mappedRooms.writeToStream(stream);
}

void MapImage::readFromStream(Common::ReadStream *stream) {
	_mappedRooms.readFromStream(stream);
}

void MapImage::loadGearRoomIfNecessary() {
	// TODO
}

void MapImage::loadMazeIfNecessary() {
	// TODO
}

void MapImage::unloadImage() {
	// TODO: Unload surfaces
	hide();
	_whichArea = kMapNoArea;
}

void MapImage::moveToMapLocation(const tNeighborhoodID, const tRoomID room, const tDirectionConstant dir) {
	// TODO

	if (isDisplaying())
		triggerRedraw();
}

void MapImage::addFlagToMask(const int flag) {
	// TODO
}

// This function can even be sensitive to open doors.
void MapImage::getRevealedRects(const uint32 flag, Common::Rect &r1) {	
	// TODO
}

void MapImage::drawPlayer() {
	// TODO
}

void MapImage::draw(const Common::Rect &) {
	// TODO
	drawPlayer();
}

} // End of namespace Pegasus
