def strip_leading_zeros(s):
    return s.lstrip("0") or "0"

def school_add(a, b, base):
    a, b = a[::-1], b[::-1]
    carry, res = 0, []
    for i in range(max(len(a), len(b))):
        da = int(a[i]) if i < len(a) else 0
        db = int(b[i]) if i < len(b) else 0
        s = da + db + carry
        res.append(str(s % base))
        carry = s // base
    if carry:
        res.append(str(carry))
    return strip_leading_zeros(''.join(res[::-1]))

def to_base(n, base):
    if n == 0:
        return "0"
    digits = []
    while n > 0:
        digits.append(str(n % base))
        n //= base
    return ''.join(reversed(digits))

def from_base(s, base):
    n = 0
    for ch in s:
        n = n * base + int(ch)
    return n

def karatsuba(x, y, base):
    xi, yi = from_base(x, base), from_base(y, base)
    return to_base(karatsuba_int(xi, yi), base)

def karatsuba_int(x, y):
    if x < 10 or y < 10:
        return x * y
    n = max(len(str(x)), len(str(y)))
    m = n // 2
    high1, low1 = divmod(x, 10**m)
    high2, low2 = divmod(y, 10**m)
    z0 = karatsuba_int(low1, low2)
    z1 = karatsuba_int(low1 + high1, low2 + high2)
    z2 = karatsuba_int(high1, high2)
    return z2 * 10**(2*m) + (z1 - z2 - z0) * 10**m + z0

def main():
    I1, I2, B = input().strip().split()
    B = int(B)

    add_res = school_add(I1, I2, B)

    mul_res = karatsuba(I1, I2, B)

    div_res = "0"

    print(add_res, mul_res, div_res)

if __name__ == "__main__":
    main()
