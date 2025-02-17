/*
 * Copyright (c) 2022, stelar7 <dudedbz@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/ByteReader.h>
#include <AK/Endian.h>
#include <LibCrypto/Curves/X448.h>

namespace Crypto::Curves {

void X448::import_state(u32* state, ReadonlyBytes data)
{
    for (auto i = 0; i < X448::WORDS; i++) {
        u32 value = ByteReader::load32(data.offset_pointer(sizeof(u32) * i));
        state[i] = AK::convert_between_host_and_little_endian(value);
    }
}

ErrorOr<ByteBuffer> X448::export_state(u32* data)
{
    auto buffer = TRY(ByteBuffer::create_uninitialized(X448::BYTES));

    for (auto i = 0; i < X448::WORDS; i++) {
        u32 value = AK::convert_between_host_and_little_endian(data[i]);
        ByteReader::store(buffer.offset_pointer(sizeof(u32) * i), value);
    }

    return buffer;
}

void X448::select(u32* state, u32* a, u32* b, u32 condition)
{
    // If B < (2^448 - 2^224 + 1) then R = B, else R = A
    u32 mask = condition - 1;

    for (auto i = 0; i < X448::WORDS; i++) {
        state[i] = (a[i] & mask) | (b[i] & ~mask);
    }
}

void X448::set(u32* state, u32 value)
{
    state[0] = value;

    for (auto i = 1; i < X448::WORDS; i++) {
        state[i] = 0;
    }
}

void X448::copy(u32* state, u32* value)
{
    for (auto i = 0; i < X448::WORDS; i++) {
        state[i] = value[i];
    }
}

void X448::conditional_swap(u32* first, u32* second, u32 condition)
{
    u32 mask = ~condition + 1;
    for (auto i = 0; i < X448::WORDS; i++) {
        u32 temp = mask & (first[i] ^ second[i]);
        first[i] ^= temp;
        second[i] ^= temp;
    }
}

void X448::modular_multiply_single(u32* state, u32* first, u32 second)
{
    // Compute R = (A * B) mod p
    u64 temp = 0;
    u64 carry = 0;
    u32 output[X448::WORDS];

    for (auto i = 0; i < X448::WORDS; i++) {
        temp += (u64)first[i] * second;
        output[i] = temp & 0xFFFFFFFF;
        temp >>= 32;
    }

    // Fast modular reduction
    carry = temp;
    for (auto i = 0; i < X448::WORDS / 2; i++) {
        temp += output[i];
        output[i] = temp & 0xFFFFFFFF;
        temp >>= 32;
    }

    temp += carry;
    for (auto i = X448::WORDS / 2; i < X448::WORDS; i++) {
        temp += output[i];
        output[i] = temp & 0xFFFFFFFF;
        temp >>= 32;
    }

    modular_reduce(state, output, (u32)temp);
}

void X448::modular_square(u32* state, u32* value)
{
    // Compute R = (A ^ 2) mod p
    modular_multiply(state, value, value);
}

void X448::modular_multiply(u32* state, u32* first, u32* second)
{
    // Compute R = (A * B) mod p

    u64 temp = 0;
    u64 carry = 0;
    u32 output[X448::WORDS * 2];

    // Comba's method
    for (auto i = 0; i < X448::WORDS * 2; i++) {
        if (i < 14) {
            for (auto j = 0; j <= i; j++) {
                temp += (u64)first[j] * second[i - j];
                carry += temp >> 32;
                temp &= 0xFFFFFFFF;
            }
        } else {
            for (auto j = i - 13; j < X448::WORDS; j++) {
                temp += (u64)first[j] * second[i - j];
                carry += temp >> 32;
                temp &= 0xFFFFFFFF;
            }
        }

        output[i] = temp & 0xFFFFFFFF;
        temp = carry & 0xFFFFFFFF;
        carry >>= 32;
    }

    // Fast modular reduction (first pass)
    temp = 0;
    for (auto i = 0; i < X448::WORDS / 2; i++) {
        temp += output[i];
        temp += output[i + 14];
        temp += output[i + 21];
        output[i] = temp & 0xFFFFFFFF;
        temp >>= 32;
    }

    for (auto i = X448::WORDS / 2; i < X448::WORDS; i++) {
        temp += output[i];
        temp += output[i + 7];
        temp += output[i + 14];
        temp += output[i + 14];
        output[i] = temp & 0xFFFFFFFF;
        temp >>= 32;
    }

    // Fast modular reduction (second pass)
    carry = temp;
    for (auto i = 0; i < X448::WORDS / 2; i++) {
        temp += output[i];
        output[i] = temp & 0xFFFFFFFF;
        temp >>= 32;
    }

    temp += carry;
    for (auto i = X448::WORDS / 2; i < X448::WORDS; i++) {
        temp += output[i];
        output[i] = temp & 0xFFFFFFFF;
        temp >>= 32;
    }

    modular_reduce(state, output, (u32)temp);
}

void X448::modular_add(u32* state, u32* first, u32* second)
{
    u64 temp = 0;

    // Compute R = A + B
    for (auto i = 0; i < X448::WORDS; i++) {
        temp += first[i];
        temp += second[i];
        state[i] = temp & 0xFFFFFFFF;
        temp >>= 32;
    }

    modular_reduce(state, state, (u32)temp);
}

void X448::modular_subtract(u32* state, u32* first, u32* second)
{
    i64 temp = -1;

    // Compute R = A + (2^448 - 2^224 - 1) - B
    for (auto i = 0; i < 7; i++) {
        temp += first[i];
        temp -= second[i];
        state[i] = temp & 0xFFFFFFFF;
        temp >>= 32;
    }

    temp -= 1;

    for (auto i = 7; i < 14; i++) {
        temp += first[i];
        temp -= second[i];
        state[i] = temp & 0xFFFFFFFF;
        temp >>= 32;
    }

    temp += 1;

    modular_reduce(state, state, (u32)temp);
}

void X448::modular_reduce(u32* state, u32* data, u32 a_high)
{
    u64 temp = 1;
    u32 other[X448::WORDS];

    // Compute B = A - (2^448 - 2^224 - 1)
    for (auto i = 0; i < X448::WORDS / 2; i++) {
        temp += data[i];
        other[i] = temp & 0xFFFFFFFF;
        temp >>= 32;
    }

    temp += 1;

    for (auto i = 7; i < X448::WORDS; i++) {
        temp += data[i];
        other[i] = temp & 0xFFFFFFFF;
        temp >>= 32;
    }

    auto condition = (a_high + (u32)temp - 1) & 1;
    select(state, other, data, condition);
}

void X448::to_power_of_2n(u32* state, u32* value, u8 n)
{
    // Compute R = (A ^ (2^n)) mod p
    modular_square(state, value);
    for (auto i = 1; i < n; i++) {
        modular_square(state, state);
    }
}

void X448::modular_multiply_inverse(u32* state, u32* value)
{
    // Compute R = A^-1 mod p
    u32 u[X448::WORDS];
    u32 v[X448::WORDS];

    modular_square(u, value);
    modular_multiply(u, u, value);
    modular_square(u, u);
    modular_multiply(v, u, value);
    to_power_of_2n(u, v, 3);
    modular_multiply(v, u, v);
    to_power_of_2n(u, v, 6);
    modular_multiply(u, u, v);
    modular_square(u, u);
    modular_multiply(v, u, value);
    to_power_of_2n(u, v, 13);
    modular_multiply(u, u, v);
    modular_square(u, u);
    modular_multiply(v, u, value);
    to_power_of_2n(u, v, 27);
    modular_multiply(u, u, v);
    modular_square(u, u);
    modular_multiply(v, u, value);
    to_power_of_2n(u, v, 55);
    modular_multiply(u, u, v);
    modular_square(u, u);
    modular_multiply(v, u, value);
    to_power_of_2n(u, v, 111);
    modular_multiply(v, u, v);
    modular_square(u, v);
    modular_multiply(u, u, value);
    to_power_of_2n(u, u, 223);
    modular_multiply(u, u, v);
    modular_square(u, u);
    modular_square(u, u);
    modular_multiply(state, u, value);
}

// https://datatracker.ietf.org/doc/html/rfc7748#section-5
ErrorOr<ByteBuffer> X448::compute_coordinate(ReadonlyBytes input_k, ReadonlyBytes input_u)
{
    u32 k[X448::WORDS] {};
    u32 u[X448::WORDS] {};
    u32 x1[X448::WORDS] {};
    u32 x2[X448::WORDS] {};
    u32 z1[X448::WORDS] {};
    u32 z2[X448::WORDS] {};
    u32 t1[X448::WORDS] {};
    u32 t2[X448::WORDS] {};

    // Copy input to internal state
    import_state(k, input_k);

    // Set the two least significant bits of the first byte to 0, and the most significant bit of the last byte to 1
    k[0] &= 0xFFFFFFFC;
    k[13] |= 0x80000000;

    // Copy coordinate to internal state
    import_state(u, input_u);

    // Implementations MUST accept non-canonical values and process them as
    // if they had been reduced modulo the field prime.
    modular_reduce(u, u, 0);

    set(x1, 1);
    set(z1, 0);
    copy(x2, u);
    set(z2, 1);

    // Montgomery ladder
    u32 swap = 0;
    for (auto i = X448::BITS - 1; i >= 0; i--) {
        u32 b = (k[i / 32] >> (i % 32)) & 1;

        conditional_swap(x1, x2, swap ^ b);
        conditional_swap(z1, z2, swap ^ b);

        swap = b;

        modular_add(t1, x2, z2);
        modular_subtract(x2, x2, z2);
        modular_add(z2, x1, z1);
        modular_subtract(x1, x1, z1);
        modular_multiply(t1, t1, x1);
        modular_multiply(x2, x2, z2);
        modular_square(z2, z2);
        modular_square(x1, x1);
        modular_subtract(t2, z2, x1);
        modular_multiply_single(z1, t2, A24);
        modular_add(z1, z1, x1);
        modular_multiply(z1, z1, t2);
        modular_multiply(x1, x1, z2);
        modular_subtract(z2, t1, x2);
        modular_square(z2, z2);
        modular_multiply(z2, z2, u);
        modular_add(x2, x2, t1);
        modular_square(x2, x2);
    }

    conditional_swap(x1, x2, swap);
    conditional_swap(z1, z2, swap);

    // Retrieve affine representation
    modular_multiply_inverse(u, z1);
    modular_multiply(u, u, x1);

    // Encode state for export
    return export_state(u);
}
}
