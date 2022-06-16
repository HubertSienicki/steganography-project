//
// Created by kneiv on 6/16/2022.
//

#ifndef STEGANOGRAPHY_PROJECT_BMPINFOHEADER_H
#define STEGANOGRAPHY_PROJECT_BMPINFOHEADER_H
#include <cstdint>

struct BMPInfoHeader {
    [[maybe_unused]] std::uint32_t header_size{0}; /* Size of info header*/
    std::int32_t width{0};                        /* Width of a bitmap */
    std::int32_t height{0};                       /* Height of a bitmap */
    [[maybe_unused]] std::uint32_t planes{0};     /* [UNUSED] planes of a bitmap */
    std::uint16_t bits_per_pixel{0};              /* Stores color palette informaiton ->
     *   1 - monochrome
     *   4 - max of 16 colors
     *   8 - 256 colors
     *   16 - 2^16 colors
     *   24 - 2^24 colors
     */
    [[maybe_unused]] std::uint32_t compression{4};/* [UNUSED] Stores compression data*/
    [[maybe_unused]] std::uint32_t image_size{4}; /* [UNUSED] compressed size of an image*/
};
#endif//STEGANOGRAPHY_PROJECT_BMPINFOHEADER_H
