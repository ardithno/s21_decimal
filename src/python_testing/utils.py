def get_bits_representation(value: int) -> str:
    as_bits = str(bin(value))[2:]

    num_leading_zeros_to_add = 32 - len(as_bits) % 32

    as_bits = ("0" * num_leading_zeros_to_add) + as_bits

    int_len = 32

    int32_values = [
        as_bits[position:position + int_len]
        for position in range(0, len(as_bits), int_len)
    ]

    bytes_representation = [
        f"{int_value[:8]} {int_value[8:16]} {int_value[16:24]} {int_value[24:32]}"
        for int_value in int32_values
    ]

    return (" | ").join(bytes_representation)


value = 79228162514264337593543950335
big_value = value * pow(10, 29)
