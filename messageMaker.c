/*-------------------------------------------------------------------------------

                                    HEADER

-------------------------------------------------------------------------------
The header portion of a lifx header contins 3 components
 - Frame Header    (8 bytes)
    -- Contains the following
    + Size of the entire message
    + LIFX Protocol number: must be 1024 (decimal)
    + Use of the Frame Address target field
    + Source Identifier
    ------------------------------------------------------------
    |b7|b6|b5|b4|b3,6-7 |b3,5   |b3,4         |b3,3-0|b2 |b1|b0|
    |source     |origin |tagged |addressabale |protocol  |size |
    ------------------------------------------------------------
 - Frame Address   (16 bytes)
    -- Contains the following
    + Target device address
    + A flag to say if Ack(45) is required
    + A flag to say if a State response message is required
    + message sequence number
 - Protocol Header (12 bytes)
    +
-------------------------------------------------------------------------------
*/

#define unsigned char  uint_8
#define unsigned short uint_16
#define unsigned long  uint_64

struct frame_header {

} header;

/*-------------------------------------------------------------------------------

                                    PAYLOAD

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
*/
