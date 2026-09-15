# `credit_card.cpp`

## OOP Concepts Used

The solution is procedural and does not define a credit-card class. It does use several focused functions, which provide a small form of decomposition and information hiding; a `CreditCard` class could encapsulate the number and validation behavior in a fuller OOP design.

## Algorithm

1. Read the card number.
2. Count its digits and reject numbers outside the accepted length range.
3. Check whether the number begins with an accepted prefix.
4. Apply the Luhn checksum by doubling digits in alternating positions and summing the remaining digits.
5. Report whether the number is valid when the total is divisible by ten.

## Possible Error Points

- A card number should be treated as a number string when leading zeroes must be preserved.
- Position counting must start from the correct end of the number.
- Prefix and length checks must happen before the checksum is trusted.
- Input failure and values outside the range of `long long` need handling.