#pragma once

#include "memory.hpp"
#include "common.hpp"

struct base_object
{
	uint64_t previousObjectLink; //0x0000
	uint64_t nextObjectLink; //0x0008
	uint64_t object; //0x0010
};

class GameObjectManager
{
public:
	uintptr_t get_fps_camera()
	{
		uintptr_t camera_objects[2];
		camera_objects[0] = driver.read<uintptr_t>((uintptr_t)this + 0x8); //lastMainCameraTagged
		camera_objects[1] = driver.read<uintptr_t>((uintptr_t)this + 0x10); //MainCameraTagged

		char name[256];
		uint64_t class_name_ptr = 0x00;

		base_object lastObject = driver.read<base_object>(camera_objects[0]);
		base_object activeObject = driver.read<base_object>(camera_objects[1]);
		

		if (activeObject.object)
		{
			while (activeObject.object != 0 && activeObject.object != lastObject.object)
			{
				class_name_ptr = driver.read<uint64_t>(activeObject.object + 0x60);
				driver.read(class_name_ptr + 0x0, &name, 256);
				if (strcmp(name, _("FPS Camera")) == 0)
				{
					auto unk1 = driver.read<uintptr_t>(activeObject.object + 0x30);
					return driver.read<uintptr_t>(unk1 + 0x18);
				}

				activeObject = driver.read<base_object>(activeObject.nextObjectLink);
			}
		}

		if (lastObject.object)
		{
			class_name_ptr = driver.read<uint64_t>(lastObject.object + 0x60);
			driver.read(class_name_ptr + 0x0, &name, 256);
			if (strcmp(name, _("FPS Camera")) == 0)
			{
				auto unk1 = driver.read<uintptr_t>(lastObject.object + 0x30);
				return driver.read<uintptr_t>(unk1 + 0x18);
			}
		}

		return NULL;
	}

	uintptr_t get_game_world() {
		uintptr_t objects[2];
		objects[0] = driver.read < uintptr_t >((uintptr_t)this + 0x20);
		objects[1] = driver.read < uintptr_t >((uintptr_t)this + 0x28);

		char name[256];
		uintptr_t class_name_ptr = 0x00;

		base_object activeObject = driver.read < base_object >(objects[1]);
		base_object lastObject = driver.read < base_object >(objects[0]);

		if (activeObject.object) {
			while (activeObject.object != 0 && activeObject.object != lastObject.object) {
				class_name_ptr = driver.read < uintptr_t >(activeObject.object + 0x60);
				driver.read(class_name_ptr + 0x0, &name, 256);
				if (strcmp(name, ("GameWorld")) == 0) {
					auto unk1 = driver.read < uintptr_t >(activeObject.object + 0x30);
					auto unk2 = driver.read < uintptr_t >(unk1 + 0x18);
					return driver.read < uintptr_t >(unk2 + 0x28);
				}

				activeObject = driver.read < base_object >(activeObject.nextObjectLink);
			}
		}

		if (lastObject.object) {
			class_name_ptr = driver.read < uint64_t >(lastObject.object + 0x60);
			driver.read(class_name_ptr + 0x0, &name, 256);
			if (strcmp(name, ("GameWorld")) == 0) {
				auto unk1 = driver.read < uintptr_t >(lastObject.object + 0x30);
				auto unk2 = driver.read < uintptr_t >(unk1 + 0x18);
				return driver.read < uintptr_t >(unk2 + 0x28);
			}
		}
		return NULL;
	}

private:
};