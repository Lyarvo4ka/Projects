#pragma once


/* Provide type definitions for commonly used types.
*  These are useful because a "gint8" can be adjusted
*  to be 1 byte (8 bits) on all platforms. Similarly and
*  more importantly, "gint32" can be adjusted to be
*  4 bytes (32 bits) on all platforms.
*/
typedef signed char gint8;
typedef unsigned char guint8;
typedef signed short gint16;
typedef unsigned short guint16;
#define G_GINT16_MODIFIER "h"
#define G_GINT16_FORMAT "hi"
#define G_GUINT16_FORMAT "hu"
typedef signed int gint32;
typedef unsigned int guint32;
#define G_GINT32_MODIFIER ""
#define G_GINT32_FORMAT "i"
#define G_GUINT32_FORMAT "u"
#define G_HAVE_GINT64 1          /* deprecated, always true */

typedef char   gchar;
typedef short  gshort;
typedef long   glong;
typedef int    gint;
typedef gint   gboolean;

typedef unsigned char   guchar;
typedef unsigned short  gushort;
typedef unsigned long   gulong;
typedef unsigned int    guint;

typedef float   gfloat;
typedef double  gdouble;


typedef enum {
	GIMP_RGB,     /*< desc="RGB color"     >*/
	GIMP_GRAY,    /*< desc="Grayscale"     >*/
	GIMP_INDEXED  /*< desc="Indexed color" >*/
} GimpImageBaseType;

typedef enum {
	GIMP_RGB_IMAGE,      /*< desc="RGB"             >*/
	GIMP_RGBA_IMAGE,     /*< desc="RGB-alpha"       >*/
	GIMP_GRAY_IMAGE,     /*< desc="Grayscale"       >*/
	GIMP_GRAYA_IMAGE,    /*< desc="Grayscale-alpha" >*/
	GIMP_INDEXED_IMAGE,  /*< desc="Indexed"         >*/
	GIMP_INDEXEDA_IMAGE  /*< desc="Indexed-alpha"   >*/
} GimpImageType;

typedef void* gpointer;

struct GPtrArray {
	gpointer *pdata;
	guint	    len;
};

struct GimpRGB {
	gdouble r, g, b, a;
};

typedef guint32 GQuark;

struct GError {
	GQuark       domain;
	gint         code;
	gchar       *message;
};
