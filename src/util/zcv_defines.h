#ifndef __ZCV_DEFINES_H__
#define __ZCV_DEFINES_H__

#ifdef WIN32

#define __ZCV_FUNCTION__ __FUNCTION__
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#else   //  *nix

#define __ZCV_FUNCTION__ __func__
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#endif  // WIN32

#endif
