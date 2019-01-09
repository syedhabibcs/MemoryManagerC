/*
 * ObjectManager.h
 * Object Manager header file
 */


//This is the interface for the object manager.
//Note: The terms object and block are used interchangably below.

#ifndef _OBJECT_MANAGER_H
#define _OBJECT_MANAGER_H

// The number of bytes of memory we have access to -- put here so
// everyone's consistent.
#ifndef MEMORY_SIZE
#define MEMORY_SIZE 1024*512
#endif

#define NULL_REF 0

typedef unsigned long Ref;
typedef unsigned long ulong;
typedef unsigned char uchar;


// initialize the object manager
void initPool();

// clean up the object manager (before exiting)
void destroyPool();

/*
 * This function trys to allocate a block of given size from our buffer.
 * It will fire the garbage collector as required.
 * We always assume that an insert always creates a new object...
 * On success it returns the reference number for the block of memory
 * allocated for the object.
 * On failure it returns NULL_REF (0)
 */
Ref insertObject( ulong size );

// returns a pointer to the object being requested given by the reference id
void *retrieveObject( Ref ref );

// update our index to indicate that we have another reference to the given object
void addReference( Ref ref );

// update our index to indicate that a reference is gone
void dropReference( Ref ref );

/*
 * This function traverses the index and prints the info in each entry
 * corresponding to a block of allocated memory. Prints every block's
 * reference id, starting address, and its size (in bytes).
 */
void dumpPool();

#endif
