/**
 * Extract bits from a value between left and right positions (inclusive)
 * @param v The value to extract bits from
 * @param l The left position (0-indexed)
 * @param r The right position (0-indexed)
 * @return The extracted bits
 */
unsigned int extract_bit(unsigned int v, unsigned int l, unsigned int r) {
    // Create a mask with 1's in positions l to r
    unsigned int mask = ((1U << (r - l + 1)) - 1) << l;

    // Apply the mask to extract the bits
    unsigned int extractedBits = (v & mask) >> l;

    return extractedBits;
}

unsigned int pop_count(unsigned int v) {
    unsigned int count = 0;
    v = (v & 0x55555555) + ((v >> 1) & 0x55555555);
    v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
    v = (v & 0x0F0F0F0F) + ((v >> 4) & 0x0F0F0F0F);
    v = (v & 0x00FF00FF) + ((v >> 8) & 0x00FF00FF);
    v = (v & 0x0000FFFF) + ((v >> 16) & 0x0000FFFF);
    count = v;
    return count;
}

int main() {
    unsigned int v = 0b110110101011;  // Example value
    unsigned int l = 2;               // Left position
    unsigned int r = 5;               // Right position

    unsigned int result = extract_bit(v, l, r);
    printf("Extracted bits: %u\n", result);  // Output the result

    return 0;
}