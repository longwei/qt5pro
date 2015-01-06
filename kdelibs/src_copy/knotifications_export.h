
#ifndef KNOTIFICATIONS_EXPORT_H
#define KNOTIFICATIONS_EXPORT_H

#ifdef KNOTIFICATIONS_STATIC_DEFINE
#  define KNOTIFICATIONS_EXPORT
#  define KNOTIFICATIONS_NO_EXPORT
#else
#  ifndef KNOTIFICATIONS_EXPORT
#    ifdef KNotifications_EXPORTS
        /* We are building this library */
#      define KNOTIFICATIONS_EXPORT 
#    else
        /* We are using this library */
#      define KNOTIFICATIONS_EXPORT 
#    endif
#  endif

#  ifndef KNOTIFICATIONS_NO_EXPORT
#    define KNOTIFICATIONS_NO_EXPORT 
#  endif
#endif

#ifndef KNOTIFICATIONS_DEPRECATED
#  define KNOTIFICATIONS_DEPRECATED __attribute__ ((__deprecated__))
#  define KNOTIFICATIONS_DEPRECATED_EXPORT KNOTIFICATIONS_EXPORT __attribute__ ((__deprecated__))
#  define KNOTIFICATIONS_DEPRECATED_NO_EXPORT KNOTIFICATIONS_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define KNOTIFICATIONS_NO_DEPRECATED
#endif

#endif
