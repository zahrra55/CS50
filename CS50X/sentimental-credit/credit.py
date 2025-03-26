from cs50 import get_int


def Luhn_s_Algorithm(n):
    sum = pos = 0
    while n > 0:
        digit = n % 10
        if pos % 2 == 1:
            digit *= 2
            sum += (digit // 10) + (digit % 10)
        else:
            sum += digit
        n //= 10
        pos += 1
    return (sum % 10) == 0


Cnumber = 0
while Cnumber <= 0:
    Cnumber = get_int("Number: ")

if Luhn_s_Algorithm(Cnumber):
    s = Cnumber
    length = 0
    while s > 0:
        s //= 10
        length += 1

    fir_sec_dgts = Cnumber
    while fir_sec_dgts >= 100:
        fir_sec_dgts //= 10

    # the card type checing
    if length == 15 and (fir_sec_dgts == 34 or fir_sec_dgts == 37):
        print("AMEX")
    elif length == 16 and (51 <= fir_sec_dgts <= 55):
        print("MASTERCARD")
    elif (length == 13 or length == 16) and (fir_sec_dgts // 10 == 4):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
