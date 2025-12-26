#pragma once

#ifndef OXYGEN_VERSION_H
#define OXYGEN_VERSION_H

#include <stdio.h>

typedef unsigned char byte;
typedef char * string;

struct Version
{
	byte major;
	byte minor;
	byte patch;
};

typedef struct Version Version;

inline Version Version_Init(const byte major, const byte minor, const byte patch)
{
	const Version v = {major, minor, patch};
	return v;
}

inline string print_Version(const Version *v)
{
	if(!v)
	{
		return nullptr;
	}
	static char buffer[16];
	snprintf(buffer, sizeof(buffer), "%u.%u.%u", v->major, v->minor, v->patch);
	return buffer;
}

#endif //OXYGEN_VERSION_H