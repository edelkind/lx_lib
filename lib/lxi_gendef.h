
#define GD_DEFAULT_SIZE 8192

#if 0
	*** LX_gdff ***
	fast forward generic descriptor (no error checking)
	gd must be a pointer
#endif
#define LX_gdff(gd, amount)        \
	{                          \
		(gd)->buf += amount; \
		(gd)->p += amount;   \
		(gd)->n -= amount;   \
		(gd)->a -= amount;   \
	}

#if 0
	*** LX_gdrw ***
	rewind generic descriptor
	gd must be a pointer
#endif

#define LX_gdrw(gd) \
	if ((gd)->p) { \
	  (gd)->buf -= (gd)->p; \
	  (gd)->a += (gd)->p; \
	  (gd)->n = (gd)->p = 0; \
	} else { \
	  (gd)->n = 0; \
	}

#if 0
	*** LX_gdaddstr ***
	add string to gd
	gd must have available space
	NOTE: memcpy must be defined before this can be used
#endif

#define LX_gdaddstr(GD, str, len) \
	{                                                       \
		(void) memcpy (GD->buf+GD->p+GD->n, str, len);  \
		GD->n += len;                                   \
	}

#if 0
	The following is for use in getting segments.
	These may be ORed together.  Use the checks below for testing.
#endif

#define MATCH_OK 0x1
#define MATCH_TOOLONG 0x2

#define LX_match_ok(match) (MATCH_OK & match)
#define LX_match_toolong(match) (MATCH_TOOLONG & match)

