/* 
 * File:   frames.h
 * Author: houtaro
 *
 * Created on August 7, 2016, 12:56 PM
 */

#ifndef FRAMES_H
#define	FRAMES_H

#include "list.h"

int alloc_frame(List *frames);

int free_frame(List *frames, int frame_number);

#endif	/* FRAMES_H */

