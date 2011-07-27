
#define GD_DEFAULT_SIZE 8192

/**
 * Fast forward generic descriptor (no error checking).
 *
 * gd must be a pointer.
 */
#define LX_gdff(gd, amount)        \
	{                          \
		(gd)->buf += amount; \
		(gd)->p += amount;   \
		(gd)->n -= amount;   \
		(gd)->a -= amount;   \
	}

/**
 * Rewind generic descriptor.
 *
 * gd must be a pointer.
 */

#define LX_gdrw(gd) \
	if ((gd)->p) { \
	  (gd)->buf -= (gd)->p; \
	  (gd)->a += (gd)->p; \
	  (gd)->n = (gd)->p = 0; \
	} else { \
	  (gd)->n = 0; \
	}

/**
 * Add string to gd (gd must have available space).
 *
 * NOTE: memcpy must be defined before this can be used.
 */

#define LX_gdaddstr(GD, str, len) \
	{                                                       \
		(void) memcpy ((GD)->buf+(GD)->p+(GD)->n, str, len);  \
		(GD)->n += len;                                   \
	}

/**
 * The following is for use in getting segments.
 * These may be ORed together.  Use the checks below for testing.
 */
#define MATCH_OK 0x1
#define MATCH_TOOLONG 0x2

#define LX_match_ok(match) (MATCH_OK & match)           /// A delimiter was found.
#define LX_match_toolong(match) (MATCH_TOOLONG & match) /// Before finding a delimiter, maxlen was reached.

