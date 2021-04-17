#pragma once

namespace glass::keyboard
{
    enum class key
    {
        unknown = -1,

        // british qwerty disposition
        // clang-format off

		escape, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,
		backquote, one, two, three, four, five, six, seven, eight, nine, zero, hyphen_minus, equal, backspace,
		tab, q, w, e, r, t, y, u, i, o, p, left_bracket, right_bracket, enter,
		caps_lock, a, s, d, f, g, h, j, k, l, semicolon, apostrophe, sharp,
		left_shift, backslash, z, x, c, v, b, n, m, comma, period, slash, right_shift,
		left_control, left_super, left_alt, space, right_alt, right_super, menu, right_control,

		screen_capture, scroll_lock, pause,
		insert, start, page_up,
		del, end, page_down,

		       up,
		left, down, right,

		num_lock, divide, multiply, substract,
		key_pad_7, key_pad_8, key_pad_9, add,
		key_pad_4, key_pad_5, key_pad_6,
		key_pad_1, key_pad_2, key_pad_3, key_pad_enter,
		key_pad_0, key_pad_decimal,

		// number of keys
		count,

		// aliases
		grave_accent = backquote,
		number_sign = sharp, hashtag = sharp, octothorpe = sharp,
		dot = period,
		print_screen = screen_capture,
		home = start,
		suppr = del,
		key_pad_perdiod = key_pad_decimal, key_pad_dot = key_pad_decimal, key_pad_delete = key_pad_decimal,

        // clang-format on
    };
}  // namespace glass::keyboard