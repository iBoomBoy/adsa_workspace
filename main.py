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

def school_sub(a, b, base):
    a, b = a[::-1], b[::-1]
    res, borrow = [], 0
    for i in range(len(a)):
        da = int(a[i])
        db = int(b[i]) if i < len(b) else 0
        d = da - db - borrow
        if d < 0:
            d += base
            borrow = 1
        else:
            borrow = 0
        res.append(str(d))
    return strip_leading_zeros(''.join(res[::-1]))

def school_mul(a, b, base):
    a, b = a[::-1], b[::-1]
    res = [0] * (len(a) + len(b))
    for i in range(len(a)):
        for j in range(len(b)):
            res[i+j] += int(a[i]) * int(b[j])
            res[i+j+1] += res[i+j] // base
            res[i+j] %= base
    return strip_leading_zeros(''.join(map(str, res[::-1])))

def pad_zero(s, n):
    return s + "0"*n

def karatsuba(x, y, base):
    x, y = strip_leading_zeros(x), strip_leading_zeros(y)
    if len(x) == 1 and len(y) == 1:
        return str(int(x) * int(y))

    n = max(len(x), len(y))
    if n % 2 == 1:
        n += 1
    x = x.zfill(n)
    y = y.zfill(n)
    m = n // 2

    x_high, x_low = x[:-m], x[-m:]
    y_high, y_low = y[:-m], y[-m:]

    z0 = karatsuba(x_low, y_low, base)
    z2 = karatsuba(x_high, y_high, base)
    sum_x = school_add(x_low, x_high, base)
    sum_y = school_add(y_low, y_high, base)
    z1 = karatsuba(sum_x, sum_y, base)

    temp = school_sub(z1, z2, base)
    mid = school_sub(temp, z0, base)

    res = school_add(
        school_add(pad_zero(z2, 2*m), pad_zero(mid, m), base),
        z0, base
    )
    return strip_leading_zeros(res)

def main():
    I1, I2, B = input().strip().split()
    B = int(B)

    add_res = school_add(I1, I2, B)

    mul_res = karatsuba(I1, I2, B)

    div_res = "0"

    print(add_res, mul_res, div_res)

if __name__ == "__main__":
    main()
