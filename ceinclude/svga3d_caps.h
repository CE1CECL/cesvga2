/*

    CEsvga2 - ChrisEric1 Super Video Graphics Array 2
    Copyright (C) 2023-2024, Christopher Eric Lentocha

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

/*
 * svga3d_caps.h --
 *
 *       Definitions for SVGA3D hardware capabilities.  Capabilities
 *       are used to query for optional rendering features during
 *       driver initialization. The capability data is stored as very
 *       basic key/value dictionary within the "FIFO register" memory
 *       area at the beginning of BAR2.
 *
 *       Note that these definitions are only for 3D capabilities.
 *       The SVGA device also has "device capabilities" and "FIFO
 *       capabilities", which are non-3D-specific and are stored as
 *       bitfields rather than key/value pairs.
 */

#ifndef _SVGA3D_CAPS_H_
#define _SVGA3D_CAPS_H_

#define SVGA_FIFO_3D_CAPS_SIZE   (SVGA_FIFO_3D_CAPS_LAST - \
                                  SVGA_FIFO_3D_CAPS + 1)


/*
 * SVGA3dCapsRecordType
 *
 *    Record types that can be found in the caps block.
 *    Related record types are grouped together numerically so that
 *    SVGA3dCaps_FindRecord() can be applied on a range of record
 *    types.
 */

typedef enum {
   SVGA3DCAPS_RECORD_UNKNOWN        = 0,
   SVGA3DCAPS_RECORD_DEVCAPS_MIN    = 0x100,
   SVGA3DCAPS_RECORD_DEVCAPS        = 0x100,
   SVGA3DCAPS_RECORD_DEVCAPS_MAX    = 0x1ff,
} SVGA3dCapsRecordType;


/*
 * SVGA3dCapsRecordHeader
 *
 *    Header field leading each caps block record. Contains the offset (in
 *    register words, NOT bytes) to the next caps block record (or the end
 *    of caps block records which will be a zero word) and the record type
 *    as defined above.
 */

typedef
struct SVGA3dCapsRecordHeader {
   uint32 length;
   SVGA3dCapsRecordType type;
}
SVGA3dCapsRecordHeader;


/*
 * SVGA3dCapsRecord
 *
 *    Caps block record; "data" is a placeholder for the actual data structure
 *    contained within the record; for example a record containing a FOOBAR
 *    structure would be of size "sizeof(SVGA3dCapsRecordHeader) +
 *    sizeof(FOOBAR)".
 */

typedef
struct SVGA3dCapsRecord {
   SVGA3dCapsRecordHeader header;
   uint32 data[1];
}
SVGA3dCapsRecord;


typedef uint32 SVGA3dCapPair[2];


/*
 *----------------------------------------------------------------------
 *
 * SVGA3dCaps_FindRecord
 *
 *    Finds the record with the highest-valued type within the given range
 *    in the caps block.
 *
 *    Result: pointer to found record, or NULL if not found.
 *
 *----------------------------------------------------------------------
 */

static INLINE SVGA3dCapsRecord *
SVGA3dCaps_FindRecord(const uint32 *capsBlock,
                      SVGA3dCapsRecordType recordTypeMin,
                      SVGA3dCapsRecordType recordTypeMax)
{
   SVGA3dCapsRecord *record, *found = NULL;
   uint32 offset;

   /*
    * Search linearly through the caps block records for the specified type.
    */
   for (offset = 0; capsBlock[offset] != 0; offset += capsBlock[offset]) {
      record = (SVGA3dCapsRecord *) (capsBlock + offset);
      if ((record->header.type >= recordTypeMin) &&
          (record->header.type <= recordTypeMax) &&
          (!found || (record->header.type > found->header.type))) {
         found = record;
      }
   }

   return found;
}


#endif // _SVGA3D_CAPS_H_
