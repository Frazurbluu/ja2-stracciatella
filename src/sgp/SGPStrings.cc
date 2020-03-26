#include "SGPStrings.h"
#include "Debug.h"

#include <string_theory/format>
#include <string_theory/string>

#if defined(__linux__) || defined(_WIN32)

#include <sys/types.h>
/*	$OpenBSD: wcslcpy.c,v 1.4 2006/05/05 15:27:38 millert Exp $	*/
/*	$NetBSD: wcslcpy.c,v 1.2 2001/01/03 14:33:02 lukem Exp $	*/
/*	from OpenBSD: strlcpy.c,v 1.4 1999/05/01 18:56:41 millert Exp 	*/

/*
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns wcslen(src); if retval >= siz, truncation occurred.
 */
size_t
wcslcpy(wchar_t *dst, const wchar_t *src, size_t siz)
{
	wchar_t *d = dst;
	const wchar_t *s = src;
	size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0) {
		while (--n != 0) {
			if ((*d++ = *s++) == '\0')
				break;
		}
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}

	return(s - src - 1);	/* count does not include NUL */
}

/*	$OpenBSD: strlcpy.c,v 1.11 2006/05/05 15:27:38 millert Exp $	*/

/*
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 */
size_t
strlcpy(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0) {
		while (--n != 0) {
			if ((*d++ = *s++) == '\0')
				break;
		}
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}

	return(s - src - 1);	/* count does not include NUL */
}

#endif


#ifdef _WIN32
#ifndef __MINGW32__

int WINsnprintf(char* const s, size_t const n, const char* const fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	int const ret = _vsnprintf(s, n, fmt, arg);
	va_end(arg);
	if (n != 0) s[n - 1] = '\0'; // _vsnprintf() does not guarantee NUL termination
	return ret;
}


int WINswprintf(wchar_t* const s, size_t const n, const wchar_t* const fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	int const ret = WINvswprintf(s, n, fmt, arg);
	va_end(arg);
	return ret;
}


int WINvswprintf(wchar_t* const s, size_t const n, const wchar_t* const fmt, va_list const arg)
{
	int const ret = _vsnwprintf(s, n, fmt, arg);
	if (n != 0) s[n - 1] = L'\0'; // _vsnwprintf() does not guarantee NUL termination
	return ret;
}

#endif
#endif

void CopyTrimmedString(wchar_t* dst, const size_t maxLength, const wchar_t* src) {
	size_t sourceLength = wcslen(src);
	wchar_t const* start = src;
	wchar_t const* end = src + sourceLength - 1;

	while (start[0] == L' ' && start < src + sourceLength) {
		start++;
	}
	while (end[0] == L' ' && end > start) {
		end--;
	}

	wcsncpy(dst, start, end - start + 1);

	size_t len = end - start + 1;

	AssertMsg(len < maxLength, "Tried to copy a trimmed string but could not fit the terminating null character");

	dst[len] = 0;
}


ST::string st_fmt_printf_to_format(const ST::string& fmt_printf)
{
	ST::utf32_buffer codepoints = fmt_printf.to_utf32();
	ST::string fmt;
	ST::string err;
	ST::string param;
	enum class Parse {
		Literal,
		ParamFlags,
		ParamWidth,
		ParamPrecision,
		ParamPrecisionValue,
		ParamLengthModifier,
		ParamSpecifier,
	} state = Parse::Literal;
	for (char32_t c : codepoints)
	{
		if (state == Parse::Literal)
		{
			if (c == U'%')
			{
				param = "{"; // param start
				state = Parse::ParamFlags;
				continue;
			}
			if (c == U'{')
			{
				fmt += "{{"; // literal '{'
				continue;
			}
			fmt += c; // literal
			continue;
		}
		if (state == Parse::ParamFlags)
		{
			if (c == U'-')
			{
				param += '<';
				continue;
			}
			if (c == U'+' || c == U'0' || c == U'#')
			{
				param += c;
				continue;
			}
			if (c == U' ')
			{
				err = ST::format("param flag U+{04X} '{c}' is not supported", c, c);
				break;
			}
			state = Parse::ParamWidth; // with the same codepoint
		}
		if (state == Parse::ParamWidth)
		{
			if (c >= U'0' && c <= U'9')
			{
				param += c;
				continue;
			}
			if (c == U'*')
			{
				err = ST::format("param width U+{04X} '{c}' is not supported", c, c);
				break;
			}
			state = Parse::ParamPrecision; // with the same codepoint
		}
		if (state == Parse::ParamPrecision)
		{
			if (c == U'.')
			{
				param += c;
				state = Parse::ParamPrecisionValue;
				continue;
			}
			state = Parse::ParamLengthModifier; // with the same codepoint
		}
		if (state == Parse::ParamPrecisionValue)
		{
			if (c >= U'0' && c <= U'9')
			{
				param += c;
				continue;
			}
			state = Parse::ParamLengthModifier; // with the same codepoint
		}
		if (state == Parse::ParamLengthModifier)
		{
			if (c == U'h' || c == U'l' || c == U'j' || c == U'z' || c == U't' || c == U'L')
			{
				// ignore
				continue;
			}
			state = Parse::ParamSpecifier; // with the same codepoint
		}
		if (state == Parse::ParamSpecifier)
		{
			if (c == U'%' && param == "{")
			{
				fmt += c; // literal '%'
				state = Parse::Literal;
				continue;
			}
			if (c == U'c' || c == U'o' || c == U'x' || c == U'X' || c == U'e' || c == U'E')
			{
				param += c;
				param += '}';
				fmt += param;
				state = Parse::Literal;
				continue;
			}
			if (c == U'f' || c == U'F')
			{
				param += "f}";
				fmt += param;
				state = Parse::Literal;
				continue;
			}
			if (c == U'd' || c == U'i' || c == U'u')
			{
				param += "d}";
				fmt += param;
				state = Parse::Literal;
				continue;
			}
			if (c == U's')
			{
				param += "}";
				fmt += param;
				state = Parse::Literal;
				continue;
			}
			if (c == U'a' || c == U'A' || c == U'g' || c == U'G' || c == U'n' || c == U'p')
			{
				err = ST::format("param specifier U+{04X} '{c}' is not supported", c, c);
				break;
			}
		}
		err = ST::format("unexpected codepoint U+{04X} '{c}'", c, c);
		break;
	}
	if (err.empty() && state != Parse::Literal)
	{
		err = ST::format("format param is incomplete '{}'", param);
	}
	if (!err.empty())
	{
		ST::string what = ST::format("{}: '{}' -> '{}'", err, fmt_printf, fmt);
		throw ST::bad_format(what.c_str());
	}
	return fmt;
}


ST::string st_buffer_escape(const ST::char_buffer& buf)
{
	ST::string escaped;
	for (char c : buf)
	{
		escaped += ST::format("\\x{02X}", c);
	}
	return escaped;
}


ST::string st_buffer_escape(const ST::utf16_buffer& buf)
{
	ST::string escaped;
	for (char16_t c : buf)
	{
		escaped += ST::format("\\u{04X}", c);
	}
	return escaped;
}


ST::string st_buffer_escape(const ST::utf32_buffer& buf)
{
	ST::string escaped;
	for (char32_t c : buf)
	{
		escaped += ST::format("\\U{08X}", c);
	}
	return escaped;
}
