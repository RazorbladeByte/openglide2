/*
** Copyright (c) 1995, 3Dfx Interactive, Inc.
** All Rights Reserved.
**
** This is UNPUBLISHED PROPRIETARY SOURCE CODE of 3Dfx Interactive, Inc.;
** the contents of this file may not be disclosed to third parties, copied or
** duplicated in any form, in whole or in part, without the prior written
** permission of 3Dfx Interactive, Inc.
**
** RESTRICTED RIGHTS LEGEND:
** Use, duplication or disclosure by the Government is subject to restrictions
** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
** and Computer Software clause at DFARS 252.227-7013, and/or in similar or
** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
** rights reserved under the Copyright Laws of the United States.
**
** $Header: /cvsroot-fuse/openglide/openglide/sdk2_sst1vid.h,v 1.1 2002/12/05 13:50:21 fbarros Exp $
** $Log: sdk2_sst1vid.h,v $
** Revision 1.1  2002/12/05 13:50:21  fbarros
** 3dfx sdk 2 header file
**
** Revision 1.1.1.1  2001/06/25 18:00:49  paul
** v006 from sourceforge
**
** Revision 1.1.1.1  2001/02/01 16:24:51  fbarros
** Version 0.06
**
*/
#ifndef __SST1VID_H__
#define __SST1VID_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Video defines */

typedef int GrScreenRefresh_t;
#define GR_REFRESH_60Hz   0x0
#define GR_REFRESH_70Hz   0x1
#define GR_REFRESH_72Hz   0x2
#define GR_REFRESH_75Hz   0x3
#define GR_REFRESH_80Hz   0x4
#define GR_REFRESH_90Hz   0x5
#define GR_REFRESH_100Hz  0x6
#define GR_REFRESH_85Hz   0x7
#define GR_REFRESH_120Hz  0x8
#define GR_REFRESH_NONE   0xff

typedef int GrScreenResolution_t;
#define GR_RESOLUTION_320x200   0x0
#define GR_RESOLUTION_320x240   0x1
#define GR_RESOLUTION_400x256   0x2
#define GR_RESOLUTION_512x384   0x3
#define GR_RESOLUTION_640x200   0x4
#define GR_RESOLUTION_640x350   0x5
#define GR_RESOLUTION_640x400   0x6
#define GR_RESOLUTION_640x480   0x7
#define GR_RESOLUTION_800x600   0x8
#define GR_RESOLUTION_960x720   0x9
#define GR_RESOLUTION_856x480   0xa
#define GR_RESOLUTION_512x256   0xb
#define GR_RESOLUTION_1024x768  0xC
#define GR_RESOLUTION_1280x1024 0xD
#define GR_RESOLUTION_1600x1200 0xE
#define GR_RESOLUTION_400x300   0xF
#define GR_RESOLUTION_NONE      0xff

#ifdef GR_RESOLUTION_MAX
#undef GR_RESOLUTION_MAX
#endif
#ifdef GR_RESOLUTION_MIN
#undef GR_RESOLUTION_MIN
#endif
#define GR_RESOLUTION_MIN       GR_RESOLUTION_320x200
#define GR_RESOLUTION_MAX       GR_RESOLUTION_1600x1200

#ifdef __cplusplus
}
#endif

#endif /* __SST1VID_H__ */
