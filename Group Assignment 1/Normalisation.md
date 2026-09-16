# Data Normalisation Concepts

This program demonstrates common ways of transforming one column of numerical
data. The input is stored as a `vector<double>`, and each transformation returns
a new vector so that the original values remain unchanged.

## The Task Requirements

The program must implement the requested data transformations as separate
functions and apply them to a numerical data column. The required operations
are:

- vector normalization with `normalize()`;
- min-max scaling with `min_max_scale()`;
- standardization with `standardize()`;
- z-score conversion with `z_score()`; and
- mean-centering with `center()`.

The application must also demonstrate the functions and display their results.

## Implementation Strategy

The solution uses one `vector<double>` as the input representation. Each
transformation accepts the input vector by constant reference and returns a new
`vector<double>`. This prevents the original data from being changed and keeps
each operation independently reusable.

Shared calculations are kept in helper functions. `require_values()` validates
the input, `mean()` calculates the average, and `standard_deviation()` supplies
the spread needed by z-scores. `print_column()` is responsible only for
formatting output, while `main()` is responsible for creating sample data and
calling the transformations.

## Key Decisions and Approaches

- Population standard deviation is used, so the variance is divided by `n`.
- `standardize()` delegates to `z_score()` because both operations use the
	same mathematical transformation in this task.
- Empty input is rejected with an exception rather than producing an invalid
	result.
- A zero vector cannot be normalized, so `normalize()` reports that case.
- A constant column produces zeros for min-max scaling and z-scores because
	its range or standard deviation is zero.
- Results are printed to three decimal places to make comparisons clear.

## Shared Helpers

`require_values()` checks that the input is not empty. The transformation
functions call this validation before doing calculations. `mean()` calculates
the arithmetic average using `std::accumulate()`.

`standard_deviation()` calculates the population standard deviation. It finds
the average squared distance from the mean and then takes the square root:

\[
\sigma = \sqrt{\frac{\sum (x_i - \mu)^2}{n}}
\]

The program uses the population formula, so it divides by `n` rather than
`n - 1`.

## Normalization

`normalize()` divides every value by the Euclidean length of the vector:

\[
\text{length} = \sqrt{\sum x_i^2}
\]

The resulting vector has a length of 1. A zero vector cannot be normalized,
because division by its length would require division by zero.

## Min-Max Scaling

`min_max_scale()` places values on a range from 0 to 1:

\[
x' = \frac{x - \min(x)}{\max(x) - \min(x)}
\]

The minimum becomes 0 and the maximum becomes 1. If every input value is the
same, the range is zero, so the function returns 0 for every item instead of
dividing by zero.

## Standardization and Z-Scores

`z_score()` converts each value into the number of standard deviations it is
away from the mean:

\[
z = \frac{x - \mu}{\sigma}
\]

`standardize()` calls `z_score()` because standardizing a column is the same
operation in this program. A column with no variation has a standard deviation
of zero; its standardized values are returned as 0.

## Centering

`center()` subtracts the mean from each value:

\[
x' = x - \mu
\]

The centered column has a mean of approximately 0, but it keeps the original
measurement scale. For example, marks measured in points remain point-sized
differences from the average.

## Application Flow

The `main()` function creates one sample column:

```cpp
{12.0, 18.0, 24.0, 30.0, 36.0}
```

It prints the original column and then calls `normalize()`, `min_max_scale()`,
`standardize()`, `z_score()`, and `center()`. `print_column()` formats each
result to three decimal places, making the outputs easy to compare.

Each function creates and returns a separate result vector. This is an example
of keeping the transformation functions independent from the application and
from the output formatting.

## How the Solution Was Tested

The source was checked with the C++ editor diagnostics, which reported no
errors. The implementation was also reviewed against the mathematical formulas
for each operation and the constant-value edge cases described above. The
sample run below provides a direct check of the expected function applications
and output formatting.

## Working Example

Input:

```text
{12.0, 18.0, 24.0, 30.0, 36.0}
```

Expected output, rounded to three decimal places:

```text
Original: 12.000 18.000 24.000 30.000 36.000
Normalized: 0.211 0.316 0.422 0.527 0.632
Min-max scaled: 0.000 0.250 0.500 0.750 1.000
Standardized: -1.414 -0.707 0.000 0.707 1.414
Z-score: -1.414 -0.707 0.000 0.707 1.414
Centered: -12.000 -6.000 0.000 6.000 12.000
```

The mean of the input is `24.0`. Therefore, centering subtracts `24.0` from
each value, while standardization and z-scores divide those differences by the
population standard deviation, approximately `8.485`.