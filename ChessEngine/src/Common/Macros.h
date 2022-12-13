#ifndef MACROS_H
#define MACROS_H

#define FR2SQ(file,rank) ((21 + (file)) + ((rank) * 10))
#define SETBIT(bb,square) ((bb) |= SetMask[(square)])
#define CLEARBIT(bb,square) ((bb) &= ClearMask[(square)])

#endif
