//
//  AsciiArtTool.h
//  ex1_wet
//
//  Created by Dvir Bartov on 19/04/2022.
//

#ifndef ASCII_ART_TOOL_H
#define ASCII_ART_TOOL_H

#include "RLEList.h"

/**
 * asciiArtEncoded: Compresses an image file to an RLEList.
 *
 * @param in_stream - the file containing the uncompressed image
 * @return
 *      RLE List that contains the compressed image
 */
RLEList asciiArtRead(FILE* in_stream);

/**
 * asciiArtPrint: Decompresses an image file contained in a RLE List to an output file.
 * @param list - The RLE list containing the compressed image.
 * @param out_stream - The output file containing the uncompressed image.
 * @return
 *    RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters to inner functions
 *    RLE_LIST_SUCCESS if the image has been decompressed successfully
 */
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/**
* asciiArtPrintEncoded: Writes a compressed version of the image to the file provided.
*
* @param list - The RLE list containing the image characters.
* @param out_stream - The file to write the compressed version to.
* @return
*     RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
*     RLE_LIST_SUCCESS if the character has been inserted successfully
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif // ASCII_ART_TOOL_H
