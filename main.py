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

def school_add(a, b, base):
    a, b = a[::-1], b[::-1]  # reverse for easier processing
    carry, res = 0, []
    for i in range(max(len(a), len(b))):
        da = int(a[i]) if i < len(a) else 0
        db = int(b[i]) if i < len(b) else 0
        s = da + db + carry
        res.append(str(s % base))
        carry = s // base
    if carry:
        res.append(str(carry))
    return ''.join(res[::-1])

def karatsuba(x, y):
    if x < 10 or y < 10:
        return x * y
    n = max(len(str(x)), len(str(y)))
    m = n // 2
    high1, low1 = divmod(x, 10**m)
    high2, low2 = divmod(y, 10**m)
    z0 = karatsuba(low1, low2)
    z1 = karatsuba(low1 + high1, low2 + high2)
    z2 = karatsuba(high1, high2)
    return z2 * 10**(2*m) + (z1 - z2 - z0) * 10**m + z0

def main():
    I1, I2, B = input().strip().split()
    B = int(B)

    n1 = from_base(I1, B)
    n2 = from_base(I2, B)

    add_res = school_add(I1, I2, B)

    mul_res = to_base(karatsuba(n1, n2), B)

    div_res = "0"

    print(add_res, mul_res, div_res)
