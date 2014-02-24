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

#include "audio/audiostream.h"
#include "audio/decoders/raw.h"
#include "common/memstream.h"
#include "mads/sound.h"
#include "mads/mads.h"
#include "mads/nebular/sound_nebular.h"

namespace MADS {

SoundManager::SoundManager(MADSEngine *vm, Audio::Mixer *mixer) {
	_vm = vm;
	_mixer = mixer;
	_driver = nullptr;
	_pollSoundEnabled = false;
	_soundPollFlag = false;
	_newSoundsPaused = false;
}

SoundManager::~SoundManager() {
	delete _driver;
}

void SoundManager::init(int sectionNumber) {
	assert(sectionNumber > 0 && sectionNumber < 10);

	switch (_vm->getGameID()) {
	case GType_RexNebular:
		// TODO: Other Rex Adlib section drivers
		assert(sectionNumber == 1);
		_driver = new Nebular::ASound1(_mixer);
		break;

	default:
		error("Unknown game");
	}
}

void SoundManager::closeDriver() {
	if (_driver) {
		command(0);
		setEnabled(false);
		stop();

		removeDriver();
	}
}

void SoundManager::removeDriver() {
	delete _driver;
	_driver = nullptr;
}

void SoundManager::setEnabled(bool flag) {
	_pollSoundEnabled = flag;
	_soundPollFlag = false;
}

void SoundManager::queueNewCommands() {
	_newSoundsPaused = true;
}

void SoundManager::startQueuedCommands() {
	_newSoundsPaused = false;

	while (!_queuedCommands.empty()) {
		int commandId = _queuedCommands.front();
		command(commandId);
	}
}

void SoundManager::command(int commandId, int param) {
	if (_newSoundsPaused) {
		if (_queuedCommands.size() < 8)
			_queuedCommands.push(commandId);
	} else if (_driver) {
		_driver->command(commandId, param);
	}
}

void SoundManager::stop() {
	if (_driver)
		_driver->stop();
}

void SoundManager::noise() {
	if (_driver)
		_driver->noise();
}

} // End of namespace MADS
