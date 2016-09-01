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

struct GArray {
	gchar *data;
	guint len;
};

typedef struct {
	gint32    drawable_id;   /* drawable ID */
	guint     width;         /* width of drawble */
	guint     height;        /* height of drawble */
	guint     bpp;           /* bytes per pixel of drawable */
	guint     ntile_rows;    /* # of tile rows */
	guint     ntile_cols;    /* # of tile columns */
	GimpTile *tiles;         /* the normal tiles */
	GimpTile *shadow_tiles;  /* the shadow tiles */
} GimpDrawable;

typedef struct {
	guint         ewidth;     /* the effective width of the tile */
	guint         eheight;    /* the effective height of the tile */
	guint         bpp;        /* the bytes per pixel (1, 2, 3 or 4 ) */
	guint         tile_num;   /* the number of this tile within the drawable */
	guint16       ref_count;  /* reference count for the tile */
	guint         dirty : 1;  /* is the tile dirty? has it been modified? */
	guint         shadow : 1;  /* is this a shadow tile */
	guchar       *data;       /* the pixel data for the tile */
	GimpDrawable *drawable;   /* the drawable this tile came from */
} GimpTile;

typedef struct {
	guchar       *data;          /* pointer to region data */
	GimpDrawable *drawable;      /* pointer to drawable */
	gint          bpp;           /* bytes per pixel */
	gint          rowstride;     /* bytes per pixel row */
	gint          x, y;          /* origin */
	gint          w, h;          /* width and height of region */
	guint         dirty : 1;     /* will this region be dirtied? */
	guint         shadow : 1;    /* will this region use the shadow or normal tiles */
	gint          process_count; /* used internally */
} GimpPixelRgn;

typedef enum
{
	GIMP_NORMAL_MODE,          /*< desc="Normal"               >*/
	GIMP_DISSOLVE_MODE,        /*< desc="Dissolve"             >*/
	GIMP_BEHIND_MODE,          /*< desc="Behind"               >*/
	GIMP_MULTIPLY_MODE,        /*< desc="Multiply"             >*/
	GIMP_SCREEN_MODE,          /*< desc="Screen"               >*/
	GIMP_OVERLAY_MODE,         /*< desc="Overlay"              >*/
	GIMP_DIFFERENCE_MODE,      /*< desc="Difference"           >*/
	GIMP_ADDITION_MODE,        /*< desc="Addition"             >*/
	GIMP_SUBTRACT_MODE,        /*< desc="Subtract"             >*/
	GIMP_DARKEN_ONLY_MODE,     /*< desc="Darken only"          >*/
	GIMP_LIGHTEN_ONLY_MODE,    /*< desc="Lighten only"         >*/
	GIMP_HUE_MODE,             /*< desc="Hue"                  >*/
	GIMP_SATURATION_MODE,      /*< desc="Saturation"           >*/
	GIMP_COLOR_MODE,           /*< desc="Color"                >*/
	GIMP_VALUE_MODE,           /*< desc="Value"                >*/
	GIMP_DIVIDE_MODE,          /*< desc="Divide"               >*/
	GIMP_DODGE_MODE,           /*< desc="Dodge"                >*/
	GIMP_BURN_MODE,            /*< desc="Burn"                 >*/
	GIMP_HARDLIGHT_MODE,       /*< desc="Hard light"           >*/
	GIMP_SOFTLIGHT_MODE,       /*< desc="Soft light"           >*/
	GIMP_GRAIN_EXTRACT_MODE,   /*< desc="Grain extract"        >*/
	GIMP_GRAIN_MERGE_MODE,     /*< desc="Grain merge"          >*/
	GIMP_COLOR_ERASE_MODE,     /*< desc="Color erase"          >*/
	GIMP_ERASE_MODE,           /*< pdb-skip, desc="Erase"      >*/
	GIMP_REPLACE_MODE,         /*< pdb-skip, desc="Replace"    >*/
	GIMP_ANTI_ERASE_MODE       /*< pdb-skip, desc="Anti erase" >*/
} GimpLayerModeEffects;

