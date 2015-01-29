#ifndef ICICLE_CONFIG_H
#define ICICLE_CONFIG_H

//Version number
#define ICE_VERSION_MAJOR 1
#define ICE_VERSION_MINOR 0

//Platform detection
#ifdef _WIN32
#define ICE_WIN32
#endif

#ifdef __linux
#define ICE_LINUX
#endif

//Configuration detection
#ifdef _DEBUG
#define ICE_DEBUG
#endif

#endif
