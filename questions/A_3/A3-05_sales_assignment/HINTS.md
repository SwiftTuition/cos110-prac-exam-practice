# A3-05 hints

Try the question first. Read one hint at a time. The hints go from gentle to specific. They do not give the full answer.

## Hint 1

Step 2 is the only new idea. A `Sales` object has a `Department` part, and that part has private attributes. Which function that is already written can copy them?

## Hint 2

Inside a member function of `Sales`, you can call a function of the base class by writing the class name and `::` in front of the function name. For example, `Department::getSize()` calls the `Department` version.

## Hint 3

A `Sales` object is a `Department`, so `other` (a `const Sales&`) can be passed where a `const Department&` is expected. The step-2 line is: `Department::operator=(other);`. Steps 1, 3 and 4 are the same as in any assignment operator.
