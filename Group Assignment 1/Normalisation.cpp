#include "PPPheaders.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>

using std::vector;

namespace {

// Shared validation keeps all transformations consistent for empty input.
void require_values(const vector<double>& values)
{
    if (values.empty()) {
        throw std::invalid_argument("The data column cannot be empty.");
    }
}

double mean(const vector<double>& values)
{
    require_values(values);
    return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
}

// Population standard deviation measures the spread around the column mean.
double standard_deviation(const vector<double>& values)
{
    const double average = mean(values);
    double squared_deviations = 0.0;

    for (double value : values) {
        squared_deviations += (value - average) * (value - average);
    }

    return std::sqrt(squared_deviations / values.size());
}

// Vector normalization scales values so their Euclidean length becomes 1.
vector<double> normalize(const vector<double>& values)
{
    require_values(values);
    double length = 0.0;

    for (double value : values) {
        length += value * value;
    }

    length = std::sqrt(length);
    if (length == 0.0) {
        throw std::invalid_argument("A zero vector cannot be normalized.");
    }

    vector<double> result;
    for (double value : values) {
        result.push_back(value / length);
    }
    return result;
}

// Min-max scaling maps the smallest value to 0 and the largest to 1.
vector<double> min_max_scale(const vector<double>& values)
{
    require_values(values);
    const auto minimum = *std::min_element(values.begin(), values.end());
    const auto maximum = *std::max_element(values.begin(), values.end());
    vector<double> result;

    for (double value : values) {
        if (maximum == minimum) {
            result.push_back(0.0);
        } else {
            result.push_back((value - minimum) / (maximum - minimum));
        }
    }
    return result;
}

// A z-score expresses each value as its distance from the mean in deviations.
vector<double> z_score(const vector<double>& values)
{
    require_values(values);
    const double average = mean(values);
    const double deviation = standard_deviation(values);
    vector<double> result;

    for (double value : values) {
        if (deviation == 0.0) {
            result.push_back(0.0);
        } else {
            result.push_back((value - average) / deviation);
        }
    }
    return result;
}

// Standardization is provided as a named application of the z-score operation.
vector<double> standardize(const vector<double>& values)
{
    return z_score(values);
}

// Centering subtracts the mean while preserving the original unit of measure.
vector<double> center(const vector<double>& values)
{
    const double average = mean(values);
    vector<double> result;

    for (double value : values) {
        result.push_back(value - average);
    }
    return result;
}

// This output helper gives every transformation a comparable, readable display.
void print_column(const std::string& name, const vector<double>& values)
{
    std::cout << name << ": ";
    for (double value : values) {
        std::cout << std::fixed << std::setprecision(3) << value << ' ';
    }
    std::cout << '\n';
}

} // namespace

// The application runs every transformation on one sample data column.
int main()
{
    const vector<double> marks{12.0, 18.0, 24.0, 30.0, 36.0};

    print_column("Original", marks);
    print_column("Normalized", normalize(marks));
    print_column("Min-max scaled", min_max_scale(marks));
    print_column("Standardized", standardize(marks));
    print_column("Z-score", z_score(marks));
    print_column("Centered", center(marks));
}