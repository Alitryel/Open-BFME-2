#pragma once
// Opaque twelve-byte payload. Native585B1E copies three scalar floats before
// deque growth; native2CA82C constructs it by copying three words without
// reference counting. The previous owning-string member came from a donor
// guess. Neither the original class nor field names are established.
// The explicit member copy preserves the native temporary's SSE shape.
struct Gen_t_00595870_p12cd {
    float x, y, z;
    Gen_t_00595870_p12cd() {}
    Gen_t_00595870_p12cd(const Gen_t_00595870_p12cd &value)
        : x(value.x), y(value.y), z(value.z) {}
};
