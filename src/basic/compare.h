#ifndef COMPARE_H
#define COMPARE_H

/**
 * @brief compare_patch
 * @param img1
 * @param W1
 * @param W2
 * @param img2
 * @param W2
 * @param H2
 * @param x_off left up corner of img1 in img2
 * @param y_off
 * @return
 */
int compare_patch(uint8_t *img1, uint32_t W1, uint32_t H1, uint8_t *img2,
                  uint32_t W2, uint32_t H2, uint32_t x_off, uint32_t y_off,
                  float *cost);

#endif // COMPARE_H
