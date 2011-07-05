/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
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

#ifndef NEVERHOOD_SCENE_H
#define NEVERHOOD_SCENE_H

#include "common/array.h"
#include "neverhood/neverhood.h"
#include "neverhood/background.h"
#include "neverhood/entity.h"
#include "neverhood/graphics.h"
#include "neverhood/module.h"
#include "neverhood/palette.h"
#include "neverhood/smackerplayer.h"
#include "neverhood/sprite.h"
#include "neverhood/staticdata.h"

namespace Neverhood {

class Scene : public Entity {
public:
	Scene(NeverhoodEngine *vm, Module *parentModule, bool clearHitRects);
	virtual ~Scene();
	virtual void draw();
	void addEntity(Entity *entity);
	bool removeEntity(Entity *entity);
	void addSurface(BaseSurface *surface);
	bool removeSurface(BaseSurface *surface);
	Sprite *addSprite(Sprite *sprite);
	void setSurfacePriority(BaseSurface *surface, int priority);
	void deleteSprite(Sprite **sprite);
	Background *addBackground(Background *background);
protected:
	Module *_parentModule;
	Common::Array<Entity*> _entities;
	Common::Array<BaseSurface*> _surfaces;
	bool _systemCallbackFlag;
	MessageList *_messageList;
	int _messageListIndex;
	int _messageListCount;
	bool _messageListFlag1;
	NPoint _mouseClickPos;
	bool _mouseClicked;
	// TODO RectResource _rectResource;
	// TODO 00000080 rectList		dd ?
	// TODO 00000084 rectType		dw ?
	// TODO 00000086 rectListCount   dw ?
	// TODO 00000088 someRects	   dd ?
	// TODO 0000008C someRectsCount  dw ?
	// TODO 0000008E field_8E		dw ?
	// TODO 00000090 playerSprite		dd ?
	// TODO 00000094 mouseSprite	 dd ?
	Palette *_palette;
	Background *_background;
	bool _surfaceFlag;
	bool _messageListFlag;
	MessageList *_messageList2;
	int _messageListStatus;
	SmackerPlayer *_smackerPlayer;
	void (Entity::*_savedUpdateHandlerCb)();
	uint32 (Entity::*_savedMessageHandlerCb)(int messageNum, const MessageParam &param, Entity *sender);
	bool _smackerDone;
	// TODO 000000BD field_BD		db ?
	// TODO 000000BE field_BE		db ?
	// TODO 000000BF field_BF		db ?
	uint32 _smkFileHash;
	// TODO 000000C4 hitArray		dd ?
	bool _messageListFlag2;
	bool _prevVisible;
	int _messageValue;
	// TODO 000000CF field_CF		db ?
	void update();
	uint32 handleMessage(int messageNum, const MessageParam &param, Entity *sender);
	void smackerUpdate();
	uint32 smackerHandleMessage(int messageNum, const MessageParam &param, Entity *sender);
};

} // End of namespace Neverhood

#endif /* NEVERHOOD_SCENE_H */
