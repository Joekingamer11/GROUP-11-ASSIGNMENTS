# `grading_multiple_choice_questions.cpp`

## OOP Concepts Used

This grading program is procedural and does not define student, question, or answer classes. It uses two-dimensional and one-dimensional arrays as data abstractions; a `Student` object could encapsulate answers and scores in an OOP redesign.

## Algorithm

1. Store each student's ten answers in a two-dimensional array.
2. Store the correct answers in a one-dimensional key.
3. For each student, compare every answer with the corresponding key entry.
4. Increment that student's correct-answer count and print the result.

## Possible Error Points

- Student and question loop bounds must match the declared array dimensions.
- The answer key must align with the same question indexes as the student answers.
- Comparing characters with strings or using the wrong case produces incorrect scores.
- The data is fixed in the source, so changing the number of students or questions requires updating the dimensions and loops.